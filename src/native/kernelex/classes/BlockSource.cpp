#include <jni.h>

#include <innercore/biomes.h>
#include <innercore/vtable.h>

#include <commontypes.hpp>

#include <Biome.hpp>
#include <Block.hpp>
#include <BlockLegacy.hpp>
#include <BlockSource.hpp>
#include <Dimension.hpp>
#include <Level.hpp>
#include <LevelChunk.hpp>

#include "../modules/blocks/module.hpp"


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_ExtendedBlockSource_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)
#define WORLD_GENERATOR_OFFSET 28


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
    __EXPORT__(jint, GetBiome, jint x, jint z) {
        VTABLE_FIND_OFFSET(BiomeSource_fillBiomes, _ZTV16FixedBiomeSource, _ZNK16FixedBiomeSource10fillBiomesER10LevelChunk);
        auto dimension = ((BlockSource*) ptr)->getDimension();
        if(dimension == nullptr) return -1;
        BlockPos blockPos(x, 0, z);
        LevelChunk chunk(*dimension, ChunkPos(blockPos), false);
        int dimensionID = dimension->getDimensionId().id;
        if(dimensionID == 2) {
            return CustomBiomeRegistry::toVirtualId(VanillaBiomes::mSky->id);
        } else {
            auto generator = ((char*) dimension->getWorldGenerator() - WORLD_GENERATOR_OFFSET);
            if(dimensionID == 1) {
                auto ngenerator = (NetherGenerator*) generator;
                VanillaOverworldBiomeSource biomeSource(ngenerator->layer1, ngenerator->layer2);
                VTABLE_CALL<void>(BiomeSource_fillBiomes, &biomeSource, &chunk);
            } else if(dimensionID == 0 && dimension->getLevel()->getLevelData()->getGenerator() == GeneratorType::SUPERFLAT) {
                FixedBiomeSource biomeSource(*((FlatWorldGenerator*) generator)->biome);
                VTABLE_CALL<void>(BiomeSource_fillBiomes, &biomeSource, &chunk);
            } else {
                OverworldGenerator::OverridableBiomeSourceHelper helper(*(OverworldGenerator*) generator);
                VTABLE_CALL<void>(BiomeSource_fillBiomes, helper.biomeSource, &chunk);
            }
        }
        Biome* biome = chunk.getBiome(ChunkBlockPos(blockPos));
        return CustomBiomeRegistry::toVirtualId(biome->id);
    }
    __EXPORT__(jint, GetBiomeFast, jint x, jint z) {
        VTABLE_FIND_OFFSET(BiomeSource_getBiome, _ZTV16FixedBiomeSource, _ZNK16FixedBiomeSource8getBiomeEii);
        auto dimension = ((BlockSource*) ptr)->getDimension();
        if(dimension == nullptr) return -1;
        int dimensionID = dimension->getDimensionId().id;
        if(dimensionID > 2) return -1;
        Biome* biome = nullptr;
        if(dimensionID == 2) {
            biome = VanillaBiomes::mSky;
        } else {
            auto generator = ((char*) dimension->getWorldGenerator() - WORLD_GENERATOR_OFFSET);
            if(dimensionID == 1) {
                auto ngenerator = (NetherGenerator*) generator;
                VanillaOverworldBiomeSource biomeSource(ngenerator->layer1, ngenerator->layer2);
                biome = VTABLE_CALL<Biome*>(BiomeSource_getBiome, &biomeSource, x, z);
            } else if(dimensionID == 0 && dimension->getLevel()->getLevelData()->getGenerator() == GeneratorType::SUPERFLAT) {
                FixedBiomeSource biomeSource(*((FlatWorldGenerator*) generator)->biome);
                biome = VTABLE_CALL<Biome*>(BiomeSource_getBiome, &biomeSource, x, z);
            } else {
                OverworldGenerator::OverridableBiomeSourceHelper helper(*(OverworldGenerator*) generator);
                biome = VTABLE_CALL<Biome*>(BiomeSource_getBiome, helper.biomeSource, x, z);
            }
        }
        return biome == nullptr ? -1 : CustomBiomeRegistry::toVirtualId(biome->id);
    }
}


#undef __EXPORT__