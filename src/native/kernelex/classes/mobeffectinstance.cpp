#include <jni.h>

#include <MobEffectInstance.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_MobEffectInstance_native##NAME(JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jint, GetId) {
        return ((MobEffectInstance*) ptr)->getId();
    }
    __EXPORT__(jint, GetDuration) {
        return ((MobEffectInstance*) ptr)->getDuration();
    }
    __EXPORT__(jint, GetDifficultyDuration, jint difficulty) {
        switch(difficulty) {
            case 1: return ((MobEffectInstance*) ptr)->durationEasy;
            case 2: return ((MobEffectInstance*) ptr)->durationNormal;
            case 3: return ((MobEffectInstance*) ptr)->durationHard;
            default: return -1;
        }
    }
    __EXPORT__(jint, GetAmplifier) {
        return ((MobEffectInstance*) ptr)->getAmplifier();
    }
    __EXPORT__(jboolean, DisplaysOnScreenTextureAnimation) {
        return ((MobEffectInstance*) ptr)->displaysOnScreenTextureAnimation();
    }
    __EXPORT__(jboolean, IsAmbient) {
        return ((MobEffectInstance*) ptr)->isAmbient();
    }
    __EXPORT__(jboolean, IsNoCounter) {
        return ((MobEffectInstance*) ptr)->isNoCounter();
    }
    __EXPORT__(jboolean, IsEffectVisible) {
        return ((MobEffectInstance*) ptr)->isEffectVisible();
    }
    __EXPORT__(void, SetDuration, jint duration) {
        ((MobEffectInstance*) ptr)->setDuration(duration);
    }
    __EXPORT__(void, SetDifficultyDuration, jint difficulty, jint duration) {
        ((MobEffectInstance*) ptr)->setDifficulityDuration((Difficulty) difficulty, duration);
    }
    __EXPORT__(void, SetNoCounter, jboolean noCounter) {
        ((MobEffectInstance*) ptr)->setNoCounter(noCounter);
    }
}


#undef __EXPORT__