#include <jni.h>

#include <commontypes.hpp>

#include <Block.hpp>
#include <BlockLegacy.hpp>
#include <BlockSource.hpp>

#include "../modules/blocks/module.hpp"


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
    __EXPORT__(jlong, GetBlockState, jint x, jint y, jint z) {
        Block* block = ((BlockSource*) ptr)->getBlock(BlockPos(x, y, z));
        if(block == nullptr) return 0;
        return KEXBlocksModule::packBlockLong(IdConversion::dynamicToStatic(block->legacy->id, IdConversion::BLOCK), block->getVariant(), block->getRuntimeId());
    }
    __EXPORT__(jboolean, SetBlockState, jint x, jint y, jint z, jint runtimeID, jint flags) {
        Block* block = BlockStatesRegistry::getBlockByRuntimeId(runtimeID);
        return block == nullptr ? false : ((BlockSource*) ptr)->setBlock(x, y, z, *block, flags);
    }
    __EXPORT__(jboolean, SetBlockStateNoUpdate, jint x, jint y, jint z, jint runtimeID) {
        Block* block = BlockStatesRegistry::getBlockByRuntimeId(runtimeID);
        return block == nullptr ? false : ((BlockSource*) ptr)->setBlockNoUpdate(x, y, z, *block);
    }
}


#undef __EXPORT__