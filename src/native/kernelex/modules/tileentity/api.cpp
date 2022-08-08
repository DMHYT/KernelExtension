#include <jni.h>

#include <BlockActor.hpp>

#include "module.hpp"


extern "C" {
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_tileentity_TileEntityNativeAPI_getType
    (JNIEnv*, jclass, jlong ptr) {
        return (int) ((BlockActor*) ptr)->type;
    }
    JNIEXPORT jintArray JNICALL Java_vsdum_kex_modules_tileentity_TileEntityNativeAPI_getPosition
    (JNIEnv* env, jclass, jlong ptr) {
        const auto& pos = ((BlockActor*) ptr)->getPosition();
        jintArray result = env->NewIntArray(3);
        jint fill[3];
        fill[0] = pos.x;
        fill[1] = pos.y;
        fill[2] = pos.z;
        env->SetIntArrayRegion(result, 0, 3, fill);
        return result;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_tileentity_TileEntityNativeAPI_newType
    (JNIEnv* env, jclass, jstring name, jint id) {
        const char* cName = env->GetStringUTFChars(name, 0);
        BlockActor::mIdClassMap.emplace(cName, id);
        BlockActor::mClassIdMap.emplace(id, cName);
        env->ReleaseStringUTFChars(name, cName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_TileEntityModule_registerForBlock
    (JNIEnv* env, jclass, jint blockID, jint type) {
        KEXTileEntityModule::customTileEntityBlocks.emplace(blockID, type);
    }
}