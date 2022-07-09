#include <jni.h>

#include <Dimension.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_Dimension_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jint, GetDimensionId) {
        return ((Dimension*) ptr)->getDimensionId().id;
    }
    __EXPORT__(jlong, GetLevel) {
        Level* level = ((Dimension*) ptr)->getLevel();
        if(level == nullptr) return 0;
        return (jlong) level;
    }
}


#undef __EXPORT__