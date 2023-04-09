#include <unordered_map>

#include <mod.h>

#include <innercore/id_conversion_map.h>

#include <commontypes.hpp>

#include <Block.hpp>
#include <BlockLegacy.hpp>
#include <BlockSource.hpp>

#include "../../utils/java_utils.hpp"

#ifndef KEX_MODULES_BLOCKS_MODULE_HPP
#define KEX_MODULES_BLOCKS_MODULE_HPP


class KEXBlocksModule : public Module {
    public:
    class LightEmission {
        public:
        static std::unordered_map<int, unsigned long long> lightData;
        static unsigned char get(int id, int data);
        static void set(int id, int data, unsigned char lightLevel);
    };
    class BlockParamsModifier {
        public:
        bool dynamicLightEmission = false;
        bool emitsComparatorSignal = false;
        BlockParamsModifier() {}
        void applyTo(int id);
    };
    static std::unordered_map<int, BlockParamsModifier*> modifiers;
    static inline BlockParamsModifier* getOrCreateModifier(int id) {
        auto found = modifiers.find(id);
        if(found != modifiers.end()) return found->second;
        else {
            modifiers.emplace(id, new BlockParamsModifier());
            return modifiers.at(id);
        }
    }
    static inline BlockParamsModifier* getModifierOrNull(int id) {
        auto found = modifiers.find(id);
        return found != modifiers.end() ? found->second : nullptr;
    }
    static inline bool hasModifier(int id) {
        return modifiers.find(id) != modifiers.end();
    }
    static inline unsigned long long packBlockLong(int id, int data, int runtimeId) {
        return ((((unsigned long long) id << 16) | (unsigned long long) data) | ((unsigned long long) runtimeId << 32));
    }
    static inline bool _enableComparatorSignal(BlockLegacy* block) {
        return true;
    }
    static inline int _getComparatorSignalPatch(BlockLegacy* block, BlockSource& region, const BlockPos& pos, const Block& state, char side) {
        int id = IdConversion::dynamicToStatic(block->id, IdConversion::BLOCK);
        int data = state.getVariant();
        int runtimeId = (int) state.getRuntimeId();
        jlong blockLong = (jlong) packBlockLong(id, data, runtimeId);
        int result = KEXJavaBridge::BlocksModule::getComparatorSignal(blockLong, (jlong) &region, pos.x, pos.y, pos.z, side);
        return result < 0 ? 0 : result > 15 ? 15 : result;
    }
    static inline unsigned char* _getLightEmissionPatch(unsigned char* resultRVO, BlockLegacy*, const Block& state) {
        *resultRVO = (unsigned char) LightEmission::get(IdConversion::dynamicToStatic(state.legacy->id, IdConversion::BLOCK), state.getVariant());
    }
    KEXBlocksModule(Module* parent): Module(parent, "kex.blocks") {}
    virtual void initialize();
};


#endif //KEX_MODULES_BLOCKS_HPP