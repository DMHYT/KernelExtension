#include <string>
#include <unordered_map>
#include <unordered_set>
#include <hook.h>
#include <innercore/id_conversion_map.h>
#include <innercore/item_registry.h>
#include <Actor.hpp>
#include <Block.hpp>
#include <BlockLegacy.hpp>
#include <commontypes.hpp>
#include <GameMode.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>
#include <items/DiggerItem.hpp>
#include <items/PickaxeItem.hpp>
#include <items/WeaponItem.hpp>
#include <Level.hpp>
#include <Mob.hpp>
#include <Player.hpp>
#include <SurvivalMode.hpp>
#include <static_symbol.hpp>
#include "../../utils/java_utils.hpp"
#include "classes.hpp"
#include "module.hpp"


LastDestroyedBlock* KEXToolsModule::lastDestroyed = new LastDestroyedBlock();
std::unordered_map<int, BlockDataInterface*> KEXToolsModule::blockData;
std::unordered_map<int, int> KEXToolsModule::toolsToBrokenIds;
std::unordered_set<int> KEXToolsModule::customTools;


bool KEXToolsModule::isCustomTool(int id) {
    return customTools.find(id) != customTools.end();
}


const char* KEXToolsModule::getBlockMaterialName(int id) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        std::string materialName = found->second->materialName;
        if(!materialName.empty()) {
            return materialName.c_str();
        }
    } else {
        blockData.emplace(id, new BlockDataInterface());
    }
    return nullptr;
}


int KEXToolsModule::getBlockDestroyLevel(int id) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        return found->second->destroyLevel;
    } else {
        blockData.emplace(id, new BlockDataInterface());
        return 0;
    }
}


bool KEXToolsModule::getBlockIsNative(int id) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        return found->second->isNative;
    } else {
        blockData.emplace(id, new BlockDataInterface());
        return false;
    }
}


void KEXToolsModule::setBlockMaterialName(int id, const char* materialName) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        found->second->materialName = std::string(materialName);
    } else {
        BlockDataInterface* iface = new BlockDataInterface();
        iface->materialName = std::string(materialName);
        blockData.emplace(id, iface);
    }
}


void KEXToolsModule::setBlockDestroyLevel(int id, int destroyLevel) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        found->second->destroyLevel = destroyLevel;
    } else {
        BlockDataInterface* iface = new BlockDataInterface();
        iface->destroyLevel = destroyLevel;
        blockData.emplace(id, iface);
    }
}


void KEXToolsModule::setBlockIsNative(int id, bool isNative) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        found->second->isNative = isNative;
    } else {
        BlockDataInterface* iface = new BlockDataInterface();
        iface->isNative = isNative;
        blockData.emplace(id, iface);
    }
}


bool KEXToolsModule::patchedCanDestroySpecial(DiggerItem* _this, Block const& block) {
    int blockLevel = KEXToolsModule::getBlockDestroyLevel(IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK));
    return _this->hasBlock(block) && _this->tier->getLevel() >= blockLevel;
}


// 0 - nothing, 1 - prevent item from breaking, 2 - replace the item with brokenId
unsigned char KEXToolsModule::modifiedItemStackHurtAndBreak(ItemStackBase* stack, int damageValue) {
    int id = IdConversion::dynamicToStatic(stack->getId(), stack->isBlock() ? IdConversion::BLOCK : IdConversion::ITEM);
    auto found = KEXToolsModule::toolsToBrokenIds.find(id);
    int brokenId;
    if(found != KEXToolsModule::toolsToBrokenIds.end()) brokenId = found->second;
    else brokenId = 0;
    bool replace = !( KEXJavaBridge::ToolsModule::onBroke((jlong) stack) );
    if(!replace) return 1;
    else {
        if(brokenId == 0) return 0;
        else return 2;
    }
    return 0;
}


void KEXToolsModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK11PickaxeItem17canDestroySpecialERK5Block"), LAMBDA((HookManager::CallbackController* controller, PickaxeItem* item, Block const& block), {
        controller->replace();
        return patchedCanDestroySpecial(item, block);
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    // HookManager::addCallback(SYMBOL("mcpe", "_ZN10DiggerItem9setBlocksERKNSt6__ndk16vectorIPK5BlockNS0_9allocatorIS4_EEEE"), LAMBDA((DiggerItem* item), {
        
    // }, ), HookManager::RETURN | HookManager::LISTENER);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN13ItemStackBase12hurtAndBreakEiP5Actor"), LAMBDA((HookManager::CallbackController* controller, ItemStackBase* stack, int damageValue, Actor* actor), {
        unsigned char result = modifiedItemStackHurtAndBreak(stack, damageValue);
        if(result == 1) {
            controller->replace();
            return false;
        } else if(result == 2) {
            auto found = toolsToBrokenIds.find(IdConversion::dynamicToStatic(stack->getId(), IdConversion::ITEM));
            controller->replace();
            ItemStack* newStack = new ItemStack(*(ItemRegistry::getItemById(IdConversion::staticToDynamic(found->second, IdConversion::ITEM))), 1, 0);
            *stack = *newStack;
            return true;
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN12SurvivalMode17startDestroyBlockERK8BlockPoshRb"), LAMBDA((SurvivalMode* mode, BlockPos const& pos, unsigned char side, bool& someBoolRef), {
        if(mode->player->getLevel()->isClientSide()) {
            lastDestroyed->onEvent(pos.x, pos.y, pos.z, side);
        }
    }, ), HookManager::CALL | HookManager::LISTENER);
    // the hook of SurvivalMode::startDestroyBlock is the main one,
    // and the hook of GameMode::destroyBlock is made to look how they will behave,
    // when the player will be in creative mode, because I'm not sure that
    // startDestroyBlock is called in creative mode
    HookManager::addCallback(SYMBOL("mcpe", "_ZN8GameMode12destroyBlockERK8BlockPosh"), LAMBDA((GameMode* mode, BlockPos const& pos, unsigned char side), {
        if(mode->player->getLevel()->isClientSide()) {
            lastDestroyed->onEvent(pos.x, pos.y, pos.z, side);
        }
    }, ), HookManager::CALL | HookManager::LISTENER);
}


float LastDestroyedBlock::getOrCalculateSpeed(ItemStackBase const& stack, Block const& block, WeaponItem* item) {
    if(x == calculatedForX && y == calculatedForY && z == calculatedForZ) {
        return destroyTime;
    } else {
        calculatedForX = x;
        calculatedForY = y;
        calculatedForZ = z;
        STATIC_SYMBOL(WeaponItem_getDestroySpeed, "_ZNK10WeaponItem15getDestroySpeedERK13ItemStackBaseRK5Block", (WeaponItem*, ItemStackBase const&, Block const&));
        void* output = WeaponItem_getDestroySpeed(item, stack, block);
        float result = *(float*)&output;
        result = KEXJavaBridge::ToolsModule::calcDestroyTime(((jlong) &stack), IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK), block.data, x, y, z, side, block.legacy->destroyTime, 1.0f, 1.0f, block.legacy->destroyTime) / block.legacy->destroyTime;
        destroyTime = result;
        return result;
    }
}


float LastDestroyedBlock::getOrCalculateSpeed(ItemStackBase const& stack, Block const& block, DiggerItem* item) {
    if(x == calculatedForX && y == calculatedForY && z == calculatedForZ) {
        return destroyTime;
    } else {
        calculatedForX = x;
        calculatedForY = y;
        calculatedForZ = z;
        STATIC_SYMBOL(DiggerItem_getDestroySpeed, "_ZNK10DiggerItem15getDestroySpeedERK13ItemStackBaseRK5Block", (DiggerItem*, ItemStackBase const&, Block const&));
        void* output = DiggerItem_getDestroySpeed(item, stack, block);
        float result = *(float*)&output;
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        KEXJavaBridge::ToolsModule::modifyEnchant(((jlong) &stack), x, y, z, side, staticId, block.data);
        float materialDivider = item->tier->getSpeed();
        float efficiencyModifier = item->destroySpeedBonus(stack);
        result = KEXJavaBridge::ToolsModule::calcDestroyTime(((jlong) &stack), staticId, block.data, x, y, z, side, block.legacy->destroyTime, materialDivider, efficiencyModifier, block.legacy->destroyTime / materialDivider / efficiencyModifier) / block.legacy->destroyTime;
        destroyTime = result;
        return result;
    }
}


void LastDestroyedBlock::onEvent(int xIn, int yIn, int zIn, unsigned char sideIn) {
    x = xIn, y = yIn, z = zIn, side = sideIn;
}