#include "module.hpp"


std::unordered_set<int> KEXBlocksModule::ComparatorSignal::forced;
std::unordered_map<unsigned int, unsigned char> KEXBlocksModule::ComparatorSignal::signalCache;
std::unordered_map<unsigned int, long long> KEXBlocksModule::ComparatorSignal::timestampCache;


unsigned char KEXBlocksModule::ComparatorSignal::callAndCache(int id, int data, unsigned int runtimeId, BlockSource& region, const BlockPos& pos, unsigned char side, bool callbackForced, long long timestamp) {
    jlong blockLong = (jlong) KEXBlocksModule::packBlockLong(id, data, runtimeId);
    int result = KEXJavaBridge::BlocksModule::getComparatorSignal(blockLong, (jlong) &region, pos.x, pos.y, pos.z, side);
    unsigned char clamped = result < 0 ? 0 : result > 15 ? 15 : (unsigned char) result;
    if(!callbackForced) {
        signalCache[runtimeId] = clamped;
        timestampCache[runtimeId] = timestamp;
    }
    return clamped;
}

unsigned char KEXBlocksModule::ComparatorSignal::get(BlockLegacy* block, BlockSource& region, const BlockPos& pos, const Block& state, unsigned char side) {
    int id = IdConversion::dynamicToStatic(block->id, IdConversion::BLOCK);
    int data = state.getVariant();
    unsigned int runtimeId = state.getRuntimeId();
    if(isCallbackForced(id)) return callAndCache(id, data, runtimeId, region, pos, side, true, 0ll);
    long long current = getTimeMilliseconds();
    if(signalCache.find(runtimeId) == signalCache.end() || current - timestampCache[runtimeId] >= 500ll)
        return callAndCache(id, data, runtimeId, region, pos, side, false, current);
    return signalCache[runtimeId];
}