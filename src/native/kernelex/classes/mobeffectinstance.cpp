#include <jni.h>
#include <MobEffectInstance.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_MobEffectInstance_native##NAME(JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_MobEffectInstance_nativeConstruct__III
    (JNIEnv*, jclass, jint id, jint duration, jint amplifier) {
        MobEffectInstance* instance = new MobEffectInstance((unsigned int) id, duration, amplifier);
        return (jlong) instance;
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_MobEffectInstance_nativeConstruct__IIIZZZ
    (JNIEnv*, jclass, jint id, jint duration, jint amplifier, jboolean isAmbient, jboolean alwaysTrue, jboolean textureSomething) {
        MobEffectInstance* instance = new MobEffectInstance((unsigned int) id, duration, amplifier, isAmbient, alwaysTrue, textureSomething);
        return (jlong) instance;
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_MobEffectInstance_nativeConstruct__II
    (JNIEnv*, jclass, jint id, jint duration) {
        MobEffectInstance* instance = new MobEffectInstance((unsigned int) id, duration);
        return (jlong) instance;
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_MobEffectInstance_nativeConstruct__I
    (JNIEnv*, jclass, jint id) {
        MobEffectInstance* instance = new MobEffectInstance((unsigned int) id);
        return (jlong) instance;
    }
    __EXPORT__(jboolean, IsNoCounter) {
        return ((MobEffectInstance*) ptr)->isNoCounter();
    }
    __EXPORT__(jboolean, IsAmbient) {
        return ((MobEffectInstance*) ptr)->isAmbient();
    }
    __EXPORT__(jint, GetAmplifier) {
        return ((MobEffectInstance*) ptr)->getAmplifier();
    }
    __EXPORT__(jboolean, IsEffectVisible) {
        return ((MobEffectInstance*) ptr)->isEffectVisible();
    }
    __EXPORT__(jint, GetDuration) {
        return ((MobEffectInstance*) ptr)->getDuration();
    }
    __EXPORT__(jint, GetId) {
        return ((MobEffectInstance*) ptr)->getId();
    }
    __EXPORT__(jboolean, DisplaysOnScreenTextureAnimation) {
        return ((MobEffectInstance*) ptr)->displaysOnScreenTextureAnimation();
    }
}


#undef __EXPORT__