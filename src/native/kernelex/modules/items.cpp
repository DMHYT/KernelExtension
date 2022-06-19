#include <stl/string>

#include <jni.h>
#include <math.h>
#include <unordered_map>

#include <hook.h>
#include <innercore_callbacks.h>
#include <logger.h>
#include <symbol.h>

#include <innercore/id_conversion_map.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>

#include <ActorUniqueID.hpp>
#include <Player.hpp>

#include "../utils/java_utils.hpp"
#include "items.hpp"


void ItemParamsModifier::applyTo(int id) {
    Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
    if(item == nullptr) return;
    item->setRequiresWorldBuilder(requiresWorldBuilder);
    item->setExplodable(explodable);
    item->setFireResistant(fireResistant);
    item->setShouldDespawn(shouldDespawn);
    if(mirroredArt) item->setIsMirroredArt(mirroredArt);
    if(furnaceBurnIntervalMultiplier > 0) item->setFurnaceBurnIntervalMultiplier(furnaceBurnIntervalMultiplier);
    if(furnaceXPMultiplier > 0) item->setFurnaceXPmultiplier(furnaceXPMultiplier);
    void** vtable = *(void***) item;
    if(cannotBeRepairedInAnvil) {
        VTABLE_FIND_OFFSET(Item_isValidRepairItem, _ZTV4Item, _ZNK5Item17isValidRepairItemERK13ItemStackBaseRK13ItemStackBase);
        vtable[Item_isValidRepairItem] = ADDRESS(_anvilRepairDisable);
    }
    if(cooldownTime > 0) {
        VTABLE_FIND_OFFSET(Item_getCooldownTime, _ZTV4Item, _ZNK4Item15getCooldownTimeEv);
        vtable[Item_getCooldownTime] = ADDRESS(_getCooldownTimePatch);
    }
    if(dynamicUseDuration) {
        VTABLE_FIND_OFFSET(Item_getMaxUseDuration__instance, _ZTV4Item, _ZNK4Item17getMaxUseDurationEPK12ItemInstance);
        VTABLE_FIND_OFFSET(Item_getMaxUseDuration__stack, _ZTV4Item, _ZNK4Item17getMaxUseDurationEPK9ItemStack);
        vtable[Item_getMaxUseDuration__instance] = ADDRESS(_getMaxUseDurationPatch);
        vtable[Item_getMaxUseDuration__stack] = ADDRESS(_getMaxUseDurationPatch);
    }
}


std::unordered_map<int, ItemParamsModifier*> KEXItemsModule::itemParamsModifiers;
std::unordered_map<std::string, float> KEXItemsModule::customFoodSaturationModifiers;
std::unordered_map<int, FoodItemComponentLegacy*> KEXItemsModule::dynamicFoodValues;
ItemStack* KEXItemsModule::cachedFoodStack = nullptr;


ItemParamsModifier* KEXItemsModule::getOrCreateModifier(int id) {
    auto found = itemParamsModifiers.find(id);
    if(found != itemParamsModifiers.end()) {
        return found->second;
    } else {
        itemParamsModifiers.emplace(id, new ItemParamsModifier());
        return itemParamsModifiers.at(id);
    }
}

FoodItemComponentLegacy* KEXItemsModule::getOrCreateDynamicFoodValues(int id, Item* item) {
    auto found = dynamicFoodValues.find(id);
    if(found != dynamicFoodValues.end()) {
        return found->second;
    } else {
        dynamicFoodValues.emplace(id, new FoodItemComponentLegacy(*item));
        return dynamicFoodValues.at(id);
    }
}

void KEXItemsModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_Z24FoodSaturationFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE"),
        LAMBDA((HookManager::CallbackController* controller, const std::__ndk1::string& str), {
            controller->replace();
            float defaultResult = controller->call<float>(str);
            if(roundf(defaultResult * 100) / 100 == 0.6f && str != "normal") {
                auto found = customFoodSaturationModifiers.find(std::string(str.c_str()));
                if(found != customFoodSaturationModifiers.end()) {
                    return found->second;
                }
            }
            return defaultResult;
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN6Player14startUsingItemERK9ItemStacki"),
        LAMBDA((HookManager::CallbackController* controller, Player* player, const ItemStack& stack, int time), {
            Item* item = stack.getItem();
            if(item != nullptr) {
                ItemParamsModifier* mod = getModifierOrNull(IdConversion::dynamicToStatic(item->id, IdConversion::ITEM));
                if(mod != nullptr && mod->dynamicUseDuration) {
                    return controller->callAndReplace<void*>(player, stack, ItemParamsModifier::_getMaxUseDurationPatch(item, &stack));
                }
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );
    
    // HookManager::addCallback(SYMBOL("mcpe", "_ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb"), LAMBDA((Item* item, const ItemStackBase& stack, Level& level, std::__ndk1::string& text, bool b), {
    //     JNIEnv* env = KEXJavaUtils::attach();
    //     jstring jText = KEXJavaBridge::ItemsModule::appendFormattedHovertext((jlong) &stack, (jlong) &level, text.c_str());
    //     const char* cText = env->GetStringUTFChars(jText, 0);
    //     text = cText;
    //     env->ReleaseStringUTFChars(jText, cText);
    //     env->DeleteLocalRef(jText);
    // }, ), HookManager::RETURN | HookManager::LISTENER);
    // HookManager::addCallback(SYMBOL("mcpe", "_ZN6Player3eatERK9ItemStack"), LAMBDA((Player* player, const ItemStack& stack), {
    //     Item* item = stack.getItem();
    //     if(item != nullptr) {
    //         int staticId = IdConversion::dynamicToStatic(item->id, IdConversion::ITEM);
    //         ItemParamsModifier* mod = getModifierOrNull(staticId);
    //         if(mod != nullptr && mod->dynamicFoodValues) {
    //             cachedFoodStack = (ItemStack*) &stack;
    //         }
    //     }
    // }, ), HookManager::CALL | HookManager::LISTENER);
    // HookManager::addCallback(SYMBOL("mcpe", "_ZNK4Item7getFoodEv"), LAMBDA((HookManager::CallbackController* controller, Item* item), {
    //     int staticId = IdConversion::dynamicToStatic(item->id, IdConversion::ITEM);
    //     ItemParamsModifier* mod = getModifierOrNull(staticId);
    //     if(mod != nullptr && mod->dynamicFoodValues) {
    //         FoodItemComponentLegacy* dynamicFood = getOrCreateDynamicFoodValues(staticId, item);
    //         KEXJavaBridge::ItemsModule::getDynamicFoodValues((jlong) cachedFoodStack, (jlong) dynamicFood);
    //         controller->replace();
    //         return dynamicFood;
    //     }
    // }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);

    Callbacks::addCallback("postModItemsInit", 
        CALLBACK([], (), {
            for(std::unordered_map<int, ItemParamsModifier*>::iterator iter = itemParamsModifiers.begin(); iter != itemParamsModifiers.end(); iter++) {
                iter->second->applyTo(iter->first);
            }
        })
    );

}


int ItemParamsModifier::_getCooldownTimePatch(Item* item) {
    return KEXItemsModule::itemParamsModifiers.at(IdConversion::dynamicToStatic(item->id, IdConversion::ITEM))->cooldownTime;
}

int ItemParamsModifier::_getMaxUseDurationPatch(Item* item, const ItemStackBase* stack) {
    return KEXJavaBridge::ItemsModule::getUseDurationDynamic((jlong) stack);
}


extern "C" {
    #define GET_MOD ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setRequiresWorldBuilder
    (JNIEnv*, jclass, jint id, jboolean requiresWorldBuilder) {
        GET_MOD mod->requiresWorldBuilder = requiresWorldBuilder;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setExplodable
    (JNIEnv*, jclass, jint id, jboolean explodable) {
        GET_MOD mod->explodable = explodable;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setFireResistant
    (JNIEnv*, jclass, jint id, jboolean fireResistant) {
        GET_MOD mod->fireResistant = fireResistant;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setShouldDespawn
    (JNIEnv*, jclass, jint id, jboolean shouldDespawn) {
        GET_MOD mod->shouldDespawn = shouldDespawn;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setIsMirroredArt
    (JNIEnv*, jclass, jint id, jboolean mirroredArt) {
        GET_MOD mod->mirroredArt = mirroredArt;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setFurnaceBurnIntervalMultiplier
    (JNIEnv*, jclass, jint id, jfloat multiplier) {
        GET_MOD mod->furnaceBurnIntervalMultiplier = multiplier;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setFurnaceXPMultiplier
    (JNIEnv*, jclass, jint id, jfloat multiplier) {
        GET_MOD mod->furnaceXPMultiplier = multiplier;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setCannotBeRepairedInAnvil
    (JNIEnv*, jclass, jint id) {
        GET_MOD mod->cannotBeRepairedInAnvil = true;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setCooldownTime
    (JNIEnv*, jclass, jint id, jint cooldownTime) {
        if(cooldownTime > 0) {
            GET_MOD mod->cooldownTime = cooldownTime;
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_nativeEnableDynamicUseDuration
    (JNIEnv*, jclass, jint id) {
        GET_MOD mod->dynamicUseDuration = true;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_nativeEnableDynamicFoodValues
    (JNIEnv*, jclass, jint id) {
        GET_MOD mod->dynamicFoodValues = true;
    }
    #undef GET_MOD
    JNIEXPORT jboolean JNICALL Java_vsdum_kex_modules_ItemsModule_isFood
    (JNIEnv*, jclass, jint id) {
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item == nullptr) return false;
        VTABLE_FIND_OFFSET(Item_isFood, _ZTV4Item, _ZNK4Item6isFoodEv);
        return VTABLE_CALL<bool>(Item_isFood, item);
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_ItemsModule_nativeGetFood
    (JNIEnv*, jclass, jint id) {
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item == nullptr) return 0;
        VTABLE_FIND_OFFSET(Item_isFood, _ZTV4Item, _ZNK4Item6isFoodEv);
        if(!VTABLE_CALL<bool>(Item_isFood, item)) return 0;
        VTABLE_FIND_OFFSET(Item_getFood, _ZTV4Item, _ZNK4Item7getFoodEv);
        return (jlong) VTABLE_CALL<FoodItemComponentLegacy*>(Item_getFood, item);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_nativeNewFoodSaturationModifier
    (JNIEnv* env, jclass, jstring name, jfloat value) {
        const char* cName = env->GetStringUTFChars(name, 0);
        if(KEXItemsModule::customFoodSaturationModifiers.find(std::string(cName)) != KEXItemsModule::customFoodSaturationModifiers.end()) {
            Logger::debug("KEX-WARNING", "Custom food saturation modifier %s has already been registered before!", cName);
        }
        KEXItemsModule::customFoodSaturationModifiers.emplace(std::string(cName), value);
        env->ReleaseStringUTFChars(name, cName);
    }
}