#include <jni.h>

#include <innercore/vtable.h>

#include <LocalPlayer.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_LocalPlayer_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jlong, GetMoveInputHandler) {
        LocalPlayer* player = (LocalPlayer*) ptr;
        VTABLE_FIND_OFFSET(LocalPlayer_getMoveInputHandler, _ZTV11LocalPlayer, _ZN11LocalPlayer19getMoveInputHandlerEv);
        MoveInputHandler& handler = VTABLE_CALL<MoveInputHandler&>(LocalPlayer_getMoveInputHandler, player);
        return (jlong) &handler;
    }
    __EXPORT__(jboolean, IsFlying) {
        return ((LocalPlayer*) ptr)->isFlying();
    }
}


#undef __EXPORT__