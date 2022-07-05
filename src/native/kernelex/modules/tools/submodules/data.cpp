#include <innercore/id_conversion_map.h>

#include <BlockLegacy.hpp>

#include "../../../utils/java_utils.hpp"
#include "../module.hpp"


float KEXToolsModule::LastDestroyedBlock::getOrCalculateSpeed(const ItemStackBase& stack, const Block& block, WeaponItem* item) {
    if(x == calculatedForX && y == calculatedForY && z == calculatedForZ) {
        return destroySpeed;
    } else {
        calculatedForX = x;
        calculatedForY = y;
        calculatedForZ = z;
        float blockDestroyTime = block.legacy->getDestroySpeed();
        float result = blockDestroyTime / KEXJavaBridge::CustomToolEvents::calcDestroyTime(IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK), block.data, x, y, z, side, blockDestroyTime, 1.0f, 1.0f, blockDestroyTime);
        result = result == 0.0f ? 1.0f : result;
        destroySpeed = result;
        return result;
    }
}


float KEXToolsModule::LastDestroyedBlock::getOrCalculateSpeed(const ItemStackBase& stack, const Block& block, DiggerItem* item) {
    if(x == calculatedForX && y == calculatedForY && z == calculatedForZ) {
        return destroySpeed;
    } else {
        calculatedForX = x;
        calculatedForY = y;
        calculatedForZ = z;
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        float blockDestroyTime = block.legacy->getDestroySpeed();
        float materialDivider = item->speed;
        materialDivider = materialDivider == 0.0f ? 1.0f : materialDivider;
        float efficiencyModifier = item->destroySpeedBonus(stack);
        efficiencyModifier = efficiencyModifier == 0.0f ? 1.0f : efficiencyModifier;
        if(!item->hasBlock(block)) {
            materialDivider = 1.0f;
            efficiencyModifier = 1.0f;
        }
        float calc = KEXJavaBridge::CustomToolEvents::calcDestroyTime(staticId, block.data, x, y, z, side, blockDestroyTime, materialDivider, efficiencyModifier, blockDestroyTime / materialDivider / efficiencyModifier);
        float result = blockDestroyTime / calc;
        result = result == 0.0f ? 1.0f : result;
        destroySpeed = result;
        return result;
    }
}


KEXToolsModule::LastDestroyedBlock* KEXToolsModule::Data::lastClient = new KEXToolsModule::LastDestroyedBlock();
std::unordered_map<long long, KEXToolsModule::LastDestroyedBlock*> KEXToolsModule::Data::last;
std::unordered_map<int, KEXToolsModule::BlockDataInterface*> KEXToolsModule::Data::blockData;
std::unordered_map<int, int> KEXToolsModule::Data::toolsToBrokenIds;
std::unordered_set<int> KEXToolsModule::Data::customTools;