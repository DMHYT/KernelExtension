#include <cmath>

#include <innercore/id_conversion_map.h>

#include <BlockLegacy.hpp>
#include <Enchant.hpp>
#include <EnchantUtils.hpp>

#include "../../../utils/java_utils.hpp"
#include "../module.hpp"


float KEXToolsModule::LastDestroyedBlock::getOrCalculateSpeed(const ItemStackBase& stack, const Block& block, WeaponItem* item, const BlockPos& pos, unsigned char side) {
    if(
        !(pos.x == 0 && pos.y == 0 && pos.z == 0 && side == 0) &&
        pos.x == calculatedForX && pos.y == calculatedForY && pos.z == calculatedForZ && side == calculatedForSide &&
        block.legacy->id == calculatedForId && block.data == calculatedForData &&
        item == calculatedForItem &&
        getTimeMilliseconds() < lastTimestamp + 500ll
    ) {
        return destroySpeed;
    } else {
        calculatedForX = pos.x;
        calculatedForY = pos.y;
        calculatedForZ = pos.z;
        calculatedForSide = side;
        calculatedForId = block.legacy->id;
        calculatedForData = block.data;
        calculatedForItem = item;
        lastTimestamp = getTimeMilliseconds();
        float blockDestroyTime = block.legacy->getDestroySpeed();
        float result = blockDestroyTime / KEXJavaBridge::CustomToolEvents::calcDestroyTime(IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK), block.data, pos.x, pos.y, pos.z, side, blockDestroyTime, 1.0f, 1.0f, blockDestroyTime);
        result = result == 0.0f ? 1.0f : result;
        destroySpeed = result;
        return result;
    }
}


float KEXToolsModule::LastDestroyedBlock::getOrCalculateSpeed(const ItemStackBase& stack, const Block& block, DiggerItem* item, const BlockPos& pos, unsigned char side) {
    if(
        !(pos.x == 0 && pos.y == 0 && pos.z == 0 && side == 0) &&
        pos.x == calculatedForX && pos.y == calculatedForY && pos.z == calculatedForZ && side == calculatedForSide &&
        block.legacy->id == calculatedForId && block.data == calculatedForData &&
        item == calculatedForItem &&
        getTimeMilliseconds() < lastTimestamp + 500ll
    ) {
        return destroySpeed;
    } else {
        calculatedForX = pos.x;
        calculatedForY = pos.y;
        calculatedForZ = pos.z;
        calculatedForSide = side;
        calculatedForId = block.legacy->id;
        calculatedForData = block.data;
        calculatedForItem = item;
        lastTimestamp = getTimeMilliseconds();
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        float blockDestroyTime = block.legacy->getDestroySpeed();
        float materialDivider = 1.0f;
        float efficiencyModifier = 1.0f;
        bool isBlockNative = ToolAPI::getBlockIsNative(staticId);
        float blockMultiplier = ToolAPI::getBlockMaterialMultiplier(ToolAPI::getBlockMaterialName(staticId));
        int efficiencyLevel = EnchantUtils::getEnchantLevel((Enchant::Type) 15, stack);
        float baseDestroyTime = blockDestroyTime;
        if(item->hasBlock(block)) {
            materialDivider = item->speed;
            if(isBlockNative) materialDivider *= blockMultiplier;
            efficiencyModifier = pow(1.3f, pow(2, efficiencyLevel) - 1);
        } else if(!isBlockNative) {
            baseDestroyTime *= blockMultiplier;
        }
        blockDestroyTime /= blockMultiplier;
        // float materialDivider = item->speed;
        // materialDivider = materialDivider == 0.0f ? 1.0f : materialDivider;
        // float efficiencyModifier = item->destroySpeedBonus(stack);
        // efficiencyModifier = efficiencyModifier == 0.0f ? 1.0f : efficiencyModifier;
        // if(!item->hasBlock(block)) {
        //     materialDivider = 1.0f;
        //     efficiencyModifier = 1.0f;
        // }
        float calc = KEXJavaBridge::CustomToolEvents::calcDestroyTime(staticId, block.data, pos.x, pos.y, pos.z, side, baseDestroyTime, materialDivider, efficiencyModifier, baseDestroyTime / materialDivider / efficiencyModifier);
        float result = blockDestroyTime / calc;
        result = result == 0.0f ? 1.0f : result;
        destroySpeed = result;
        return result;
    }
}


KEXToolsModule::LastDestroyedBlock* KEXToolsModule::Data::lastDestroyedBlock = new KEXToolsModule::LastDestroyedBlock();
std::unordered_map<int, KEXToolsModule::BlockDataInterface*> KEXToolsModule::Data::blockData;
std::unordered_map<int, int> KEXToolsModule::Data::toolsToBrokenIds;
std::unordered_set<int> KEXToolsModule::Data::customTools;
std::unordered_map<std::string, float> KEXToolsModule::Data::blockMaterialMultipliers {
    { "stone", 10.0f / 3.0f },
    { "wood", 1.0f },
    { "dirt", 1.0f },
    { "plant", 1.0f },
    { "fibre", 1.0f },
    { "cobweb", 10.0f / 3.0f },
    { "unbreaking", 999999999.0f }
};