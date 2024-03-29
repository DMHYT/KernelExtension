#include <jni.h>

#include <innercore/global_context.h>


extern "C" {
    JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_GlobalContext_nativeGetLocalPlayer
    (JNIEnv*, jclass) {
        LocalPlayer* player = GlobalContext::getLocalPlayer();
        if(player == nullptr) return 0;
        return (jlong) player;
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_GlobalContext_nativeGetLevel
    (JNIEnv*, jclass) {
        Level* level = GlobalContext::getLevel();
        if(level == nullptr) return 0;
        return (jlong) level;
    }
}