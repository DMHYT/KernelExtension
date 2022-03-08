#include <jni.h>
#include <innercore/id_conversion_map.h>
#include <FoodItemComponentLegacy.hpp>
#include <Item.hpp>
#include <logger.h>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_FoodItemComponent_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jint, GetItem) {
        return IdConversion::dynamicToStatic(((FoodItemComponentLegacy*) ptr)->item->id, IdConversion::ITEM);
    }
    __EXPORT__(jint, GetNutrition) {
        return ((FoodItemComponentLegacy*) ptr)->nutrition;
    }
    __EXPORT__(jfloat, GetSaturationModifier) {
        return ((FoodItemComponentLegacy*) ptr)->saturationModifier;
    }
    __EXPORT__(jstring, GetUsingConvertsTo) {
        FoodItemComponentLegacy* ficl = (FoodItemComponentLegacy*) ptr;
        if(ficl->usingConvertsTo.empty()) return NULL;
        return env->NewStringUTF(ficl->usingConvertsTo.c_str());
    }
    __EXPORT__(jint, GetOnUseAction) {
        return (int) ((FoodItemComponentLegacy*) ptr)->onUseAction;
    }
    __EXPORT__(jfloatArray, GetOnUseRange) {
        jfloatArray result = env->NewFloatArray(3);
        jfloat fill[3];
        FoodItemComponentLegacy* ficl = (FoodItemComponentLegacy*) ptr;
        fill[0] = ficl->onUseRangeX;
        fill[1] = ficl->onUseRangeY;
        fill[2] = ficl->onUseRangeZ;
        env->SetFloatArrayRegion(result, 0, 3, fill);
        return result;
    }
    __EXPORT__(jstring, GetCooldownType) {
        FoodItemComponentLegacy* ficl = (FoodItemComponentLegacy*) ptr;
        if(ficl->cooldownType.empty()) return NULL;
        return env->NewStringUTF(ficl->cooldownType.c_str());
    }
    __EXPORT__(jint, GetCooldownTime) {
        return ((FoodItemComponentLegacy*) ptr)->cooldownTime;
    }
    __EXPORT__(jboolean, CanAlwaysEat) {
        return ((FoodItemComponentLegacy*) ptr)->canAlwaysEat;
    }
    __EXPORT__(jint, GetEffectsCount) {
        return ((FoodItemComponentLegacy*) ptr)->effects.size();
    }
    __EXPORT__(jintArray, GetRemoveEffects) {
        FoodItemComponentLegacy* ficl = (FoodItemComponentLegacy*) ptr;
        int size = ficl->removeEffects.size();
        jintArray result = env->NewIntArray(size);
        if(size > 0) {
            jint fill[size];
            for(int i = 0; i < size; i++) {
                fill[i] = ficl->removeEffects[i];
            }
            env->SetIntArrayRegion(result, 0, size, fill);
        }
        return result;
    }
    __EXPORT__(jstring, EffectGetDescriptionId, jint index) {
        char* result = ((FoodItemComponentLegacy*) ptr)->effects[index].descriptionId;
        if(result == nullptr) return NULL;
        return env->NewStringUTF(result);
    }
    __EXPORT__(jint, EffectGetId, jint index) {
        return ((FoodItemComponentLegacy*) ptr)->effects[index].id;
    }
    __EXPORT__(jint, EffectGetDuration, jint index) {
        return ((FoodItemComponentLegacy*) ptr)->effects[index].duration;
    }
    __EXPORT__(jint, EffectGetAmplifier, jint index) {
        return ((FoodItemComponentLegacy*) ptr)->effects[index].amplifier;
    }
    __EXPORT__(jfloat, EffectGetChance, jint index) {
        return ((FoodItemComponentLegacy*) ptr)->effects[index].chance;
    }
}


#undef __EXPORT__