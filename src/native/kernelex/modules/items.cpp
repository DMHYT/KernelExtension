#include <unordered_map>
#include <math.h>
#include <jni.h>
#include <hook.h>
#include <logger.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <innercore/id_conversion_map.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>
#include <Item.hpp>
#include <FoodItemComponentLegacy.hpp>
#include "items.hpp"


void ItemParamsModifier::applyTo(int id) {
    Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
    VTABLE_FIND_OFFSET(Item_setRequiresWorldBuilder, _ZTV4Item, _ZN4Item23setRequiresWorldBuilderEb);
    VTABLE_CALL<void>(Item_setRequiresWorldBuilder, item, requiresWorldBuilder);
    VTABLE_FIND_OFFSET(Item_setExplodable, _ZTV4Item, _ZN4Item13setExplodableEb);
    VTABLE_CALL<void>(Item_setExplodable, item, explodable);
    VTABLE_FIND_OFFSET(Item_setFireResistant, _ZTV4Item, _ZN4Item16setFireResistantEb);
    VTABLE_CALL<void>(Item_setFireResistant, item, fireResistant);
    VTABLE_FIND_OFFSET(Item_setShouldDespawn, _ZTV4Item, _ZN4Item16setShouldDespawnEb);
    VTABLE_CALL<void>(Item_setShouldDespawn, item, shouldDespawn);
    if(mirroredArt) item->setIsMirroredArt(mirroredArt);
    if(furnaceBurnIntervalMultiplier > 0) item->setFurnaceBurnIntervalMultiplier(furnaceBurnIntervalMultiplier);
    if(furnaceXPMultiplier > 0) item->setFurnaceXPmultiplier(furnaceXPMultiplier);
    if(cannotBeRepairedInAnvil) {
        void** vtable = *(void***) item;
        VTABLE_FIND_OFFSET(Item_isValidRepairItem, _ZTV4Item, _ZNK5Item17isValidRepairItemERK13ItemStackBaseRK13ItemStackBase);
        vtable[Item_isValidRepairItem] = ADDRESS(_anvilRepairDisable);
    }
    if(cooldownTime > 0) {
        void** vtable = *(void***) item;
        VTABLE_FIND_OFFSET(Item_getCooldownTime, _ZTV4Item, _ZNK4Item15getCooldownTimeEv);
        vtable[Item_getCooldownTime] = ADDRESS(_getCooldownTimePatch);
    }
}


std::unordered_map<int, ItemParamsModifier*> KEXItemsModule::itemParamsModifiers;
std::unordered_map<std::string, float> KEXItemsModule::customFoodSaturationModifiers;


ItemParamsModifier* KEXItemsModule::getOrCreateModifier(int id) {
    auto found = itemParamsModifiers.find(id);
    if(found != itemParamsModifiers.end()) {
        return found->second;
    } else {
        itemParamsModifiers.emplace(id, new ItemParamsModifier());
        return itemParamsModifiers.at(id);
    }
}

void KEXItemsModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    HookManager::addCallback(SYMBOL("mcpe", "_Z24FoodSaturationFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE"), LAMBDA((HookManager::CallbackController* controller, std::__ndk1::string const& str), {
        controller->replace();
        float defaultResult = controller->call<float>(str);
        if(roundf(defaultResult * 100) / 100 == 0.6f && str != "normal") {
            auto found = customFoodSaturationModifiers.find(std::string(str.c_str()));
            if(found != customFoodSaturationModifiers.end()) {
                return found->second;
            }
        }
        return defaultResult;
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    Callbacks::addCallback("postModItemsInit", CALLBACK([], (), {
        for(std::unordered_map<int, ItemParamsModifier*>::iterator iter = itemParamsModifiers.begin(); iter != itemParamsModifiers.end(); iter++) {
            iter->second->applyTo(iter->first);
        }
    }));
}


int ItemParamsModifier::_getCooldownTimePatch(Item* item) {
    return KEXItemsModule::itemParamsModifiers.at(IdConversion::dynamicToStatic(item->id, IdConversion::ITEM))->cooldownTime;
}


extern "C" {
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setRequiresWorldBuilder
    (JNIEnv*, jclass, jint id, jboolean requiresWorldBuilder) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->requiresWorldBuilder = requiresWorldBuilder;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setExplodable
    (JNIEnv*, jclass, jint id, jboolean explodable) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->explodable = explodable;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setFireResistant
    (JNIEnv*, jclass, jint id, jboolean fireResistant) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->fireResistant = fireResistant;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setShouldDespawn
    (JNIEnv*, jclass, jint id, jboolean shouldDespawn) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->shouldDespawn = shouldDespawn;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setIsMirroredArt
    (JNIEnv*, jclass, jint id, jboolean mirroredArt) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->mirroredArt = mirroredArt;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setFurnaceBurnIntervalMultiplier
    (JNIEnv*, jclass, jint id, jfloat multiplier) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->furnaceBurnIntervalMultiplier = multiplier;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setFurnaceXPMultiplier
    (JNIEnv*, jclass, jint id, jfloat multiplier) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->furnaceXPMultiplier = multiplier;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setCannotBeRepairedInAnvil
    (JNIEnv*, jclass, jint id) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->cannotBeRepairedInAnvil = true;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setCooldownTime
    (JNIEnv*, jclass, jint id, jint cooldownTime) {
        if(cooldownTime > 0) {
            ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
            mod->cooldownTime = cooldownTime;
        }
    }
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