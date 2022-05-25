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

#include "../../../../../../DMH/cppheaders/json/value.h"
#include "../../../../../../DMH/cppheaders/json/reader.h"

#include <commontypes.hpp>

#include <BlockActor.hpp>
#include <BlockSource.hpp>
#include <Level.hpp>
#include <LootTableContext.hpp>
#include <LootTable.hpp>

#include "../utils/java_utils.hpp"
#include "loot.hpp"


Json::Reader* KEXLootModule::jsonReader = new Json::Reader();
std::unordered_map<std::string, std::string> KEXLootModule::cachedModifiedTables;
std::unordered_set<std::string> KEXLootModule::tablesWithDropCallbacks;

std::string KEXLootModule::getLootTableName(LootTable* table) {
    std::__ndk1::string tableDir = table->getDir();
    std::string tableName = std::regex_replace(std::string(tableDir.c_str()), std::regex("loot_tables/"), "");
    tableName = std::regex_replace(tableName, std::regex(".json"), "");
    return tableName;
}

void KEXLootModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    HookManager::addCallback(SYMBOL("mcpe", "_ZN9LootTable11deserializeEN4Json5ValueE"), LAMBDA((HookManager::CallbackController* controller, LootTable* table, Json::Value* json), {
        std::string tableName = getLootTableName(table);
        auto search = cachedModifiedTables.find(tableName);
        if(search != cachedModifiedTables.end()) {
            Json::Value newJson(0);
            jsonReader->parse(std::__ndk1::string(search->second.c_str()), newJson, true);
            void* result = controller->callAndReplace<void*>(table, &newJson);
            return result;
        } else {
            JNIEnv* env = KEXJavaUtils::attach();
            Json::Value newJson = nullptr;
            jstring modified = KEXJavaBridge::LootModule::modify(tableName.c_str(), json->toStyledString().c_str());
            if(modified != NULL) {
                const char* cModified = env->GetStringUTFChars(modified, 0);
                cachedModifiedTables.emplace(tableName, std::string(cModified));
                newJson = Json::Value(0);
                jsonReader->parse(std::__ndk1::string(cModified), newJson, true);
                env->ReleaseStringUTFChars(modified, cModified);
            }
            if(newJson != nullptr) {
                void* result = controller->callAndReplace<void*>(table, &newJson);
                return result;
            }
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK9LootTable14getRandomItemsER6RandomR16LootTableContext"), LAMBDA((std::__ndk1::vector<ItemStack>* items, LootTable* table, Random& rnd, LootTableContext& ctx), {
        std::string tableName = getLootTableName(table);
        if(KEXLootModule::tablesWithDropCallbacks.find(tableName) != KEXLootModule::tablesWithDropCallbacks.end()) {
            KEXJavaBridge::LootModule::onDrop(tableName.c_str(), (jlong) items, items->size(), (jlong) &ctx);
        }
    }, ), HookManager::RETURN | HookManager::LISTENER);
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
        std::__ndk1::vector<ItemStack>* vec = (std::__ndk1::vector<ItemStack>*) vectorPtr;
        ItemStack& stack = vec->operator[](index);
        return (jlong) &stack;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_loot_RandomItemsList_nativeAdd
    (JNIEnv*, jclass, jlong vectorPtr, jint id, jint count, jint data, jlong extra) {
        std::__ndk1::vector<ItemStack>* vec = (std::__ndk1::vector<ItemStack>*) vectorPtr;
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
        std::__ndk1::vector<ItemStack>* vec = (std::__ndk1::vector<ItemStack>*) vectorPtr;
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
                Util::LootTableUtils::fillContainer(*level, *tileContainer, *random, std::__ndk1::string(cTableName), actorPtr != 0 ? ((Actor*) actorPtr) : nullptr);
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
                LootTable* lootTable = lootTables->lookupByName(std::__ndk1::string(cTableName), *rpManager);
                env->ReleaseStringUTFChars(tableName, cTableName);
                if(lootTable != nullptr) {
                    std::__ndk1::vector<ItemStack>* items = new std::__ndk1::vector<ItemStack>();
                    *items = lootTable->getRandomItems(*random, *context);
                    return (jlong) items;
                }
            }
        }
        return 0;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_LootModule_nativeGetVectorSize
    (JNIEnv*, jclass, jlong vectorPtr) {
        return ((std::__ndk1::vector<ItemStack>*) vectorPtr)->size();
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_LootModule_nativeDeleteVector
    (JNIEnv*, jclass, jlong vectorPtr) {
        delete ((std::__ndk1::vector<ItemStack>*) vectorPtr);
    }
}