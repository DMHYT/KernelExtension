#include <jni.h>

#include <BlockSource.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_ExtendedBlockSource_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jlong, GetLevel) {
        Level* level = ((BlockSource*) ptr)->getLevel();
        if(level == nullptr) return 0;
        return (jlong) level;
    }
    __EXPORT__(jlong, GetDimension) {
        Dimension* dim = ((BlockSource*) ptr)->getDimension();
        if(dim == nullptr) return 0;
        return (jlong) dim;
    }
}


#undef __EXPORT__