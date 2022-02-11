#include <jni.h>
#include <MobEffect.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_MobEffect_native##NAME(JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_MobEffect_nativeGetById
    (JNIEnv*, jclass, jint id) {
        MobEffect* effect = MobEffect::getById(id);
        if(effect == nullptr) return 0;
        return (jlong) effect;
    }
    __EXPORT__(jboolean, IsVisible) {
        return ((MobEffect*) ptr)->isVisible();
    }
    __EXPORT__(jint, GetId) {
        return ((MobEffect*) ptr)->getId();
    }
    __EXPORT__(jboolean, IsHarmful) {
        return ((MobEffect*) ptr)->isHarmful();
    }
}


#undef __EXPORT__