#include <jni.h>

#include <innercore/id_conversion_map.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>

#include "module.hpp"
#include "submodules/food.hpp"


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_modules_ItemsModule_##NAME (JNIEnv* env, jclass clazz, jint id, ##__VA_ARGS__)


extern "C" {

    #define MOD KEXItemsModule::getOrCreateModifier(id)

    __EXPORT__(void, setRequiresWorldBuilder, jboolean requiresWorldBuilder) {
        MOD->requiresWorldBuilder = requiresWorldBuilder;
    }
    __EXPORT__(void, setExplodable, jboolean explodable) {
        MOD->explodable = explodable;
    }
    __EXPORT__(void, setFireResistant, jboolean fireResistant) {
        MOD->fireResistant = fireResistant;
    }
    __EXPORT__(void, setShouldDespawn, jboolean shouldDespawn) {
        MOD->shouldDespawn = shouldDespawn;
    }
    __EXPORT__(void, setIsMirroredArt, jboolean mirroredArt) {
        MOD->mirroredArt = mirroredArt;
    }
    __EXPORT__(void, setFurnaceBurnIntervalMultiplier, jfloat multiplier) {
        MOD->furnaceBurnIntervalMultiplier = multiplier;
    }
    __EXPORT__(void, setFurnaceXPMultiplier, jfloat multiplier) {
        MOD->furnaceXPMultiplier = multiplier;
    }
    __EXPORT__(void, setCannotBeRepairedInAnvil) {
        MOD->cannotBeRepairedInAnvil = true;
    }
    __EXPORT__(void, setCooldownTime, jint cooldownTime) {
        if(cooldownTime > 0) MOD->cooldownTime = cooldownTime;
    }
    __EXPORT__(void, nativeEnableDynamicUseDuration) {
        MOD->dynamicUseDuration = true;
    }
    __EXPORT__(void, nativeEnableDynamicFoodValues) {
        MOD->dynamicFoodValues = true;
    }

    #undef MOD

    __EXPORT__(jboolean, isFood) {
        auto item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item == nullptr) return false;
        VTABLE_FIND_OFFSET(Item_isFood, _ZTV4Item, _ZNK4Item6isFoodEv);
        return VTABLE_CALL<bool>(Item_isFood, item);
    }
    __EXPORT__(jlong, nativeGetFood) {
        auto item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item == nullptr) return 0;
        VTABLE_FIND_OFFSET(Item_isFood, _ZTV4Item, _ZNK4Item6isFoodEv);
        if(!VTABLE_CALL<bool>(Item_isFood, item)) return 0;
        VTABLE_FIND_OFFSET(Item_getFood, _ZTV4Item, _ZNK4Item7getFoodEv);
        return (jlong) VTABLE_CALL<void*>(Item_getFood, item);
    }

    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_nativeNewFoodSaturationModifier
    (JNIEnv* env, jclass, jstring name, jfloat value) {
        const char* cName = env->GetStringUTFChars(name, 0);
        if(KEXItemsFoodModule::customFoodSaturationModifiers.find(cName) != KEXItemsFoodModule::customFoodSaturationModifiers.end()) {
            Logger::message("WARNING", "[KEX-ItemsModule] Custom food saturation modifier %s has already been registered before!", cName);
        } else KEXItemsFoodModule::customFoodSaturationModifiers.emplace(cName, value);
        env->ReleaseStringUTFChars(name, cName);
    }

}


#undef __EXPORT__