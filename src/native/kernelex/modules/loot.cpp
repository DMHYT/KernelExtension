#include <jni.h>
#include <regex>

#include <hook.h>
#include <innercore_callbacks.h>
#include <symbol.h>

#include <innercore/global_context.h>
#include <innercore/id_conversion_map.h>
#include <innercore/item_extra.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>

#include <json/value.h>
#include <json/reader.h>

#include <commontypes.hpp>

#include <BlockActor.hpp>
#include <BlockSource.hpp>
#include <Level.hpp>
#include <loot/LootTableContext.hpp>
#include <loot/LootTable.hpp>

#include "../utils/java_utils.hpp"
#include "loot.hpp"


bool KEXLootModule::CustomLootCondition::applies(Random&, LootTableContext& ctx) {
    return KEXJavaBridge::LootModule::customLootConditionApplies(conditionName.c_str(), json.toStyledString().c_str(), (jlong) &ctx);
}

void KEXLootModule::CustomLootFunction::apply(ItemStack& stack, Random&, LootTableContext& ctx) {
    KEXJavaBridge::LootModule::applyCustomLootFunction(functionName.c_str(), json.toStyledString().c_str(), (jlong) &stack, (jlong) &ctx);
}

void KEXLootModule::CustomLootFunction::apply(ItemInstance& instance, Random&, LootTableContext& ctx) {
    ItemStack stack(instance);
    KEXJavaBridge::LootModule::applyCustomLootFunction(functionName.c_str(), json.toStyledString().c_str(), (jlong) &stack, (jlong) &ctx);
    instance = ItemInstance(stack);
}


Json::Reader* KEXLootModule::jsonReader = new Json::Reader();
std::unordered_map<std::string, std::string> KEXLootModule::cachedModifiedTables;
std::unordered_set<std::string> KEXLootModule::tablesWithDropCallbacks;
std::unordered_set<std::string> KEXLootModule::vanillaLootConditions {
    "killed_by_player", "killed_by_player_or_pets", "killed_by_entity",
    "random_chance", "random_difficulty_chance", "random_chance_with_looting",
    "random_regional_difficulty_chance", "has_mark_variant"
};
std::unordered_set<std::string> KEXLootModule::customLootConditions;
std::unordered_set<std::string> KEXLootModule::vanillaLootFunctions {
    "set_count", "set_data", "set_damage", "looting_enchant",
    "enchant_with_levels", "enchant_book_for_trading", "enchant_randomly",
    "furnace_smelt", "set_data_from_color_index", "enchant_random_gear",
    "random_aux_value", "random_block_state", "random_dye", "exploration_map",
    "explosion_decay", "set_name", "set_lore", "specific_enchants", "fill_container",
    "set_actor_id", "set_book_contents", "trader_material_type"
};
std::unordered_set<std::string> KEXLootModule::customLootFunctions;


// Deprecated since 3.1
std::string KEXLootModule::getLootTableName(LootTable* table) {
    auto tableDir = table->getDir();
    auto tableName = std::regex_replace(tableDir.c_str(), std::regex("loot_tables/"), "");
    tableName = std::regex_replace(tableName, std::regex(".json"), "");
    return tableName;
}


void KEXLootModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN9LootTable11deserializeEN4Json5ValueE"),
        LAMBDA((HookManager::CallbackController* controller, LootTable* table, Json::Value* json), {
            std::string tableName = table->getDir().c_str();
            auto search = cachedModifiedTables.find(tableName);
            if(search != cachedModifiedTables.end()) {
                Json::Value newJson(0);
                jsonReader->parse(search->second.c_str(), newJson, true);
                void* result = controller->callAndReplace<void*>(table, &newJson);
                return result;
            } else {
                JNIEnv* env = KEXJavaUtils::attach();
                Json::Value newJson = nullptr;
                jstring modified = KEXJavaBridge::LootModule::modify(tableName.c_str(), json->toStyledString().c_str());
                if(modified != NULL) {
                    const char* cModified = env->GetStringUTFChars(modified, 0);
                    cachedModifiedTables.emplace(tableName, cModified);
                    newJson = Json::Value(0);
                    jsonReader->parse(cModified, newJson, true);
                    env->ReleaseStringUTFChars(modified, cModified);
                }
                if(newJson != nullptr) {
                    void* result = controller->callAndReplace<void*>(table, &newJson);
                    return result;
                }
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK9LootTable14getRandomItemsER6RandomR16LootTableContext"),
        LAMBDA((stl::vector<ItemStack>* items, LootTable* table, Random& rnd, LootTableContext& ctx), {
            std::string tableName = table->getDir().c_str();
            if(KEXLootModule::tablesWithDropCallbacks.find(tableName) != KEXLootModule::tablesWithDropCallbacks.end()) {
                KEXJavaBridge::LootModule::onDrop(tableName.c_str(), (jlong) items, items->size(), (jlong) &ctx);
            }
        }, ),
        HookManager::RETURN | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17LootItemCondition11deserializeEN4Json5ValueE"),
        LAMBDA((HookManager::CallbackController* controller, LootItemCondition** result, Json::Value* json), {
            const char* conditionName = json->operator[]("condition").asCString();
            if(KEXLootModule::customLootConditions.find(conditionName) != KEXLootModule::customLootConditions.end()) {
                controller->prevent();
                *result = new KEXLootModule::CustomLootCondition(conditionName, Json::Value(*json));
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN16LootItemFunction11deserializeEN4Json5ValueE"),
        LAMBDA((HookManager::CallbackController* controller, LootItemFunction** result, Json::Value* json), {
            const char* functionName = json->operator[]("function").asCString();
            if(KEXLootModule::customLootFunctions.find(functionName) != KEXLootModule::customLootFunctions.end()) {
                controller->prevent();
                *result = new KEXLootModule::CustomLootFunction({}, functionName, Json::Value(*json));
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

}


extern "C" {
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_LootModule_enableOnDropCallbackFor
    (JNIEnv* env, jclass, jstring table) {
        const char* cTable = env->GetStringUTFChars(table, 0);
        std::string cppTable(cTable);
        env->ReleaseStringUTFChars(table, cTable);
        if(KEXLootModule::tablesWithDropCallbacks.find(cppTable) == KEXLootModule::tablesWithDropCallbacks.end()) {
            KEXLootModule::tablesWithDropCallbacks.emplace(cppTable);
        }
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_loot_RandomItemsList_nativeGet
    (JNIEnv*, jclass, jlong vectorPtr, jint index) {
        auto vec = (stl::vector<ItemStack>*) vectorPtr;
        ItemStack& stack = vec->operator[](index);
        return (jlong) &stack;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_loot_RandomItemsList_nativeAdd
    (JNIEnv*, jclass, jlong vectorPtr, jint id, jint count, jint data, jlong extra) {
        auto vec = (stl::vector<ItemStack>*) vectorPtr;
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item != nullptr && count > 0) {
            ItemStack newStack(*item, count, data);
            if(extra != 0) {
                ((ItemInstanceExtra*) extra)->apply(&newStack);
            }
            vec->push_back(newStack);
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_loot_RandomItemsList_nativeRefill
    (JNIEnv* env, jclass, jlong vectorPtr, jobjectArray stackArray) {
        auto vec = (stl::vector<ItemStack>*) vectorPtr;
        vec->clear();
        int length = env->GetArrayLength(stackArray);
        if(length > 0) {
            jclass stackClass = env->FindClass("com/zhekasmirnov/apparatus/adapter/innercore/game/item/ItemStack");
            jclass extraClass = env->FindClass("com/zhekasmirnov/innercore/api/NativeItemInstanceExtra");
            jfieldID idField = env->GetFieldID(stackClass, "id", "I");
            jfieldID countField = env->GetFieldID(stackClass, "count", "I");
            jfieldID dataField = env->GetFieldID(stackClass, "data", "I");
            jfieldID extraField = env->GetFieldID(stackClass, "extra", "Lcom/zhekasmirnov/innercore/api/NativeItemInstanceExtra;");
            jmethodID getValue = env->GetMethodID(extraClass, "getValue", "()J");
            for(int i = 0; i < length; i++) {
                jobject obj = env->GetObjectArrayElement(stackArray, i);
                jint id = env->GetIntField(obj, idField);
                jint count = env->GetIntField(obj, countField);
                jint data = env->GetIntField(obj, dataField);
                jobject extra = env->GetObjectField(obj, extraField);
                Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
                if(item != nullptr && count > 0) {
                    ItemStack newStack(*item, count, data);
                    if(extra != nullptr) {
                        jlong extraPtr = env->CallLongMethod(extra, getValue);
                        if(extraPtr != 0) {
                            ((ItemInstanceExtra*) extraPtr)->apply(&newStack);
                        }
                    }
                    vec->push_back(newStack);
                }
            }
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_LootModule_nativeFillContainer
    (JNIEnv* env, jclass, jlong bsPtr, jint x, jint y, jint z, jstring tableName, jlong actorPtr) {
        const char* cTableName = env->GetStringUTFChars(tableName, 0);
        BlockSource* blockSource = (BlockSource*) bsPtr;
        Level* level = blockSource->getLevel();
        BlockActor* blockActor = blockSource->getBlockEntity(BlockPos(x, y, z));
        if(level != nullptr && blockActor != nullptr) {
            Random* random = level->getRandom();
            VTABLE_FIND_OFFSET(BlockActor_getContainer, _ZTV10BlockActor, _ZNK10BlockActor12getContainerEv);
            Container* tileContainer = VTABLE_CALL<Container*>(BlockActor_getContainer, blockActor);
            if(random != nullptr && tileContainer != nullptr) {
                Util::LootTableUtils::fillContainer(*level, *tileContainer, *random, cTableName, actorPtr != 0 ? ((Actor*) actorPtr) : nullptr);
            }
        }
        env->ReleaseStringUTFChars(tableName, cTableName);
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_LootModule_nativeGetRandomItems
    (JNIEnv* env, jclass, jstring tableName, jlong contextPtr) {
        LootTableContext* context = (LootTableContext*) contextPtr;
        ServerLevel* level = GlobalContext::getServerLevel();
        if(level != nullptr) {
            Random* random = level->getRandom();
            LootTables* lootTables = level->getLootTables();
            VTABLE_FIND_OFFSET(Level_getResourcePackManager, _ZTV5Level, _ZNK5Level28getServerResourcePackManagerEv);
            ResourcePackManager* rpManager = VTABLE_CALL<ResourcePackManager*>(Level_getResourcePackManager, level);
            if(random != nullptr && lootTables != nullptr && rpManager != nullptr) {
                const char* cTableName = env->GetStringUTFChars(tableName, 0);
                LootTable* lootTable = lootTables->lookupByName(cTableName, *rpManager);
                env->ReleaseStringUTFChars(tableName, cTableName);
                if(lootTable != nullptr) {
                    auto items = new stl::vector<ItemStack>();
                    *items = lootTable->getRandomItems(*random, *context);
                    return (jlong) items;
                }
            }
        }
        return 0;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_LootModule_nativeGetVectorSize
    (JNIEnv*, jclass, jlong vectorPtr) {
        return ((stl::vector<ItemStack>*) vectorPtr)->size();
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_LootModule_nativeDeleteVector
    (JNIEnv*, jclass, jlong vectorPtr) {
        delete ((stl::vector<ItemStack>*) vectorPtr);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_LootModule_nativeForceLoad
    (JNIEnv* env, jclass, jstring tableName) {
        ServerLevel* level = GlobalContext::getServerLevel();
        if(level != nullptr) {
            LootTables* lootTables = level->getLootTables();
            VTABLE_FIND_OFFSET(Level_getResourcePackManager, _ZTV5Level, _ZNK5Level28getServerResourcePackManagerEv);
            ResourcePackManager* rpManager = VTABLE_CALL<ResourcePackManager*>(Level_getResourcePackManager, level);
            if(lootTables != nullptr && rpManager != nullptr) {
                const char* cTableName = env->GetStringUTFChars(tableName, 0);
                lootTables->lookupByName(cTableName, *rpManager);
                env->ReleaseStringUTFChars(tableName, cTableName);
            }
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_LootModule_nativeNewCustomLootCondition
    (JNIEnv* env, jclass, jstring conditionName) {
        const char* cConditionName = env->GetStringUTFChars(conditionName, 0);
        if(KEXLootModule::vanillaLootConditions.find(cConditionName) == KEXLootModule::vanillaLootConditions.end()) {
            if(KEXLootModule::customLootConditions.find(cConditionName) == KEXLootModule::customLootConditions.end()) {
                KEXLootModule::customLootConditions.emplace(cConditionName);
            }
        } else {
            Logger::message("WARNING", "[KEX-LootModule] Loot condition %s already exists in vanilla, cannot register custom loot condition with this name, skipping...", cConditionName);
        }
        env->ReleaseStringUTFChars(conditionName, cConditionName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_LootModule_nativeNewCustomLootFunction
    (JNIEnv* env, jclass, jstring functionName) {
        const char* cFunctionName = env->GetStringUTFChars(functionName, 0);
        if(KEXLootModule::vanillaLootFunctions.find(cFunctionName) == KEXLootModule::vanillaLootFunctions.end()) {
            if(KEXLootModule::customLootFunctions.find(cFunctionName) == KEXLootModule::customLootFunctions.end()) {
                KEXLootModule::customLootFunctions.emplace(cFunctionName);
            }
        } else {
            Logger::message("WARNING", "[KEX-LootModule] Loot function %s already exists in vanilla, cannot register custom loot function with this name, skipping...", cFunctionName);
        }
        env->ReleaseStringUTFChars(functionName, cFunctionName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_LootModule_nativeModifyStack
    (JNIEnv* env, jclass, jlong stackPtr, jint id, jint count, jint data, jlong extraPtr) {
        ItemStack* stack = (ItemStack*) stackPtr;
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item != nullptr && count > 0) {
            *stack = ItemStack(*item, count, data);
            if(extraPtr != 0) {
                ((ItemInstanceExtra*) extraPtr)->apply(stack);
            }
        }
    }
    JNIEXPORT jboolean JNICALL Java_vsdum_kex_modules_LootModule_nativeRunLootCondition
    (JNIEnv* env, jclass, jstring jsonString, jlong contextPtr) {
        const char* cJsonString = env->GetStringUTFChars(jsonString, 0);
        Json::Value json(0);
        KEXLootModule::jsonReader->parse(cJsonString, json, true);
        auto compiledCondition = LootItemCondition::deserialize(json);
        bool result = false;
        if(compiledCondition) {
            auto customCondition = (KEXLootModule::CustomLootCondition*) compiledCondition.get();
            Random* random = GlobalContext::getLevel()->getRandom();
            auto ctx = (LootTableContext*) contextPtr;
            result = customCondition->applies(*random, *ctx);
        } else {
            Logger::message("WARNING", "[KEX-LootModule] Failed to deserialize loot condition JSON object in LootModule.runLootCondition. Printing the JSON string...");
            Logger::debug("KEX-LootModule", "%s", cJsonString);
        }
        env->ReleaseStringUTFChars(jsonString, cJsonString);
        return result;
    }
}