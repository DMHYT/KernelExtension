#include <jni.h>

#include <Level.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_Level_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jlong, GetTickingAreasManager) {
        auto result = ((Level*) ptr)->getTickingAreasMgr();
        if(result == nullptr) return 0;
        return (jlong) result;
    }
}


#undef __EXPORT__