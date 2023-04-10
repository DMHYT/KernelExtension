#include <unordered_map>
#include <unordered_set>

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
    class ComparatorSignal {
        public:
        static std::unordered_set<int> forced;
        static std::unordered_map<unsigned int, unsigned char> signalCache;
        static std::unordered_map<unsigned int, long long> timestampCache;
        static inline bool isCallbackForced(int id) {
            return forced.find(id) != forced.end();
        }
        static unsigned char callAndCache(int id, int data, unsigned int runtimeId, BlockSource& region, const BlockPos& pos, unsigned char side, bool callbackForced, long long timestamp);
        static unsigned char get(BlockLegacy* block, BlockSource& region, const BlockPos& pos, const Block& state, unsigned char side);
        static inline bool _enableComparatorSignal(BlockLegacy* block) {
            return true;
        }
    };
    class LightEmission {
        public:
        static std::unordered_map<int, unsigned long long> lightData;
        static unsigned char get(int id, int data);
        static void set(int id, int data, unsigned char lightLevel);
        static inline void _getLightEmissionPatch(unsigned char* resultRVO, BlockLegacy*, const Block& state) {
            *resultRVO = (unsigned char) get(IdConversion::dynamicToStatic(state.legacy->id, IdConversion::BLOCK), state.getVariant());
        }
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
    KEXBlocksModule(Module* parent): Module(parent, "kex.blocks") {}
    virtual void initialize();
};


#endif //KEX_MODULES_BLOCKS_HPP