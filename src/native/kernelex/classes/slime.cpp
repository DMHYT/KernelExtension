#include <jni.h>
#include <innercore/vtable.h>
#include <Slime.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_Slime_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jfloat, DecreaseSquish) {
        VTABLE_FIND_OFFSET(Slime_decreaseSquish, _ZTV5Slime, _ZN5Slime14decreaseSquishEv);
        return VTABLE_CALL<float>(Slime_decreaseSquish, (Slime*) ptr);
    }
    __EXPORT__(jboolean, JustJumped) {
        return ((Slime*) ptr)->justJumped();
    }
    __EXPORT__(jboolean, JustLanded) {
        return ((Slime*) ptr)->justLanded();
    }
    __EXPORT__(jint, GetSquishValue) {
        return ((Slime*) ptr)->getSquishValue();
    }
    __EXPORT__(jint, GetOldSquishValue) {
        return ((Slime*) ptr)->getOldSquishValue();
    }
    __EXPORT__(jint, GetTargetSquish) {
        return ((Slime*) ptr)->getTargetSquish();
    }
    __EXPORT__(jint, GetSlimeSize) {
        return ((Slime*) ptr)->getSlimeSize();
    }
    __EXPORT__(void, SetSlimeSize, jint size) {
        VTABLE_FIND_OFFSET(Slime_setSlimeSize, _ZTV5Slime, _ZN5Slime12setSlimeSizeEi);
        VTABLE_CALL<void>(Slime_setSlimeSize, (Slime*) ptr, size);
    }
}


#undef __EXPORT__