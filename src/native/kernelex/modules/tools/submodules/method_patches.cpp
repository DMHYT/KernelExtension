#include <string.h>

#include <hook.h>
#include <symbol.h>

#include <innercore/id_conversion_map.h>

#include <BlockLegacy.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>
#include <items/PickaxeItem.hpp>

#include "../../../utils/java_utils.hpp"
#include "../module.hpp"
#include "../tooltypes/custom.hpp"
#include "method_patches.hpp"


HashedString* KEXToolPatchesModule::isAxeTag = new HashedString("minecraft:is_axe");
HashedString* KEXToolPatchesModule::isPickaxeTag = new HashedString("minecraft:is_pickaxe");
HashedString* KEXToolPatchesModule::isShovelTag = new HashedString("minecraft:is_shovel");


bool KEXToolPatchesModule::canDestroySpecial(DiggerItem* _this, const Block& block) {
    int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
    int blockLevel = KEXToolsModule::ToolAPI::getBlockDestroyLevel(staticId);
    Item::Tier* tier = KEXToolsModule::ToolAPI::getItemTier(_this);
    int toolLevel = tier->getLevel() + 1;
    return hasBlock(_this, block) && toolLevel >= blockLevel;
}


bool KEXToolPatchesModule::hasBlock(DiggerItem* _this, const Block& block) {
    int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
    const char* materialName = KEXToolsModule::ToolAPI::getBlockMaterialName(staticId);
    if(materialName == nullptr) return false;
    if(_this->hasTag(*isAxeTag)) {
        return strcmp(materialName, "wood") == 0;
    } else if(_this->hasTag(*isPickaxeTag)) {
        return strcmp(materialName, "stone") == 0;
    } else if(_this->hasTag(*isShovelTag)) {
        return strcmp(materialName, "dirt") == 0;
    } else {
        staticId = IdConversion::dynamicToStatic(_this->id, IdConversion::ITEM);
        LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(staticId);
        if(factory == nullptr) return false;
        if(factory->getType() == ToolFactory::_factoryTypeId) {
            ToolFactory* toolFactory = (ToolFactory*) factory;
            if(toolFactory->getToolType() == ToolFactory::CUSTOM_DIGGER) {
                CustomToolFactory* customToolFactory = (CustomToolFactory*) toolFactory;
                return customToolFactory->blockMaterials.find(materialName) != customToolFactory->blockMaterials.end();
            }
        }
        return false;
    }
}


// 0 - nothing
// 1 - prevent item from breaking
// 2 - replace the item with brokenId
unsigned char KEXToolPatchesModule::hurtAndBreak(ItemStackBase* stack, int damageValue) {
    int id = IdConversion::dynamicToStatic(stack->getId(), stack->isBlock() ? IdConversion::BLOCK : IdConversion::ITEM);
    auto found = KEXToolsModule::Data::toolsToBrokenIds.find(id);
    int brokenId = found != KEXToolsModule::Data::toolsToBrokenIds.end() ? found->second : 0;
    bool replace = !( KEXJavaBridge::CustomToolEvents::onBroke() );
    if(!replace) return 1;
    else {
        if(brokenId == 0) return 0;
        else return 2;
    }
    return 0;
}


void KEXToolPatchesModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK11PickaxeItem17canDestroySpecialERK5Block"), LAMBDA((HookManager::CallbackController* controller, PickaxeItem* item, const Block& block), {
        controller->replace();
        return canDestroySpecial((DiggerItem*) item, block);
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK10DiggerItem8hasBlockERK5Block"), LAMBDA((HookManager::CallbackController* controller, DiggerItem* item, const Block& block), {
        controller->replace();
        return hasBlock(item, block);
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN10DiggerItem9setBlocksERKNSt6__ndk16vectorIPK5BlockNS0_9allocatorIS4_EEEE"), LAMBDA((HookManager::CallbackController* controller, DiggerItem* item), {
        controller->prevent();
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN13ItemStackBase12hurtAndBreakEiP5Actor"), LAMBDA((HookManager::CallbackController* controller, ItemStackBase* stack, int damageValue, Actor* actor), {
        unsigned char result = hurtAndBreak(stack, damageValue);
        if(result == 1) {
            controller->replace();
            return false;
        } else if(result == 2) {
            int convertedId = IdConversion::dynamicToStatic(stack->getId(), IdConversion::ITEM);
            auto found = KEXToolsModule::Data::toolsToBrokenIds.find(convertedId);
            controller->replace();
            if(found == KEXToolsModule::Data::toolsToBrokenIds.end()) return true;
            convertedId = IdConversion::staticToDynamic(found->second, IdConversion::ITEM);
            Item* brokenItem = ItemRegistry::getItemById(convertedId);
            if(brokenItem == nullptr) return true;
            *stack = ItemStack(*brokenItem, 1, 0);
            return true;
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
}