#include <jni.h>

#include <innercore/global_context.h>
#include <innercore/vtable.h>

#include <BlockActor.hpp>

#include "module.hpp"


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_modules_tileentity_TileEntityNativeAPI_##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jlong, get, jint x, jint y, jint z) {
        auto tile = ((BlockSource*) ptr)->getBlockEntity(BlockPos(x, y, z));
        if(tile == nullptr) return 0;
        return (jlong) tile;
    }
    __EXPORT__(jint, getType) {
        return (int) ((BlockActor*) ptr)->type;
    }
    __EXPORT__(jintArray, getPosition) {
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
    __EXPORT__(void, load, jlong tagPtr) {
        BlockActor* tile = (BlockActor*) ptr;
        VTABLE_FIND_OFFSET(BlockActor_load, _ZTV10BlockActor, _ZN10BlockActor4loadER5LevelRK11CompoundTagR14DataLoadHelper);
        VTABLE_CALL<void>(BlockActor_load, tile, GlobalContext::getLevel(), (CompoundTag*) tagPtr, nullptr);
    }
    __EXPORT__(jboolean, save, jlong tagPtr) {
        BlockActor* tile = (BlockActor*) ptr;
        VTABLE_FIND_OFFSET(BlockActor_save, _ZTV10BlockActor, _ZNK10BlockActor4saveER11CompoundTag);
        return VTABLE_CALL<bool>(BlockActor_save, tile, (CompoundTag*) tagPtr);
    }
    __EXPORT__(jint, getLife) {
        return ((BlockActor*) ptr)->life;
    }
}


#undef __EXPORT__