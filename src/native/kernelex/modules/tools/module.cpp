#include <string>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <hook.h>
#include <innercore/global_context.h>
#include <innercore/id_conversion_map.h>
#include <innercore/item_extra.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>
#include <Actor.hpp>
#include <ActorTests.hpp>
#include <ActorUniqueID.hpp>
#include <Block.hpp>
#include <BlockLegacy.hpp>
#include <commontypes.hpp>
#include <GameMode.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>
#include <Item.hpp>
#include <items/DiggerItem.hpp>
#include <items/PickaxeItem.hpp>
#include <items/HatchetItem.hpp>
#include <items/ShovelItem.hpp>
#include <items/WeaponItem.hpp>
#include <Level.hpp>
#include <Mob.hpp>
#include <Player.hpp>
#include <SurvivalMode.hpp>
#include <static_symbol.hpp>
#include "../../utils/java_utils.hpp"
#include "classes.hpp"
#include "module.hpp"


LastDestroyedBlock* KEXToolsModule::lastDestroyedClient = new LastDestroyedBlock();
std::unordered_map<long long, LastDestroyedBlock*> KEXToolsModule::lastDestroyed;
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


Item::Tier* KEXToolsModule::getItemTier(DiggerItem* item) {
    void** vtable = *(void***) item;
    STATIC_VTABLE_SYMBOL(HatchetItem_table, "_ZTV11HatchetItem");
    STATIC_VTABLE_SYMBOL(PickaxeItem_table, "_ZTV11PickaxeItem");
    STATIC_VTABLE_SYMBOL(ShovelItem_table, "_ZTV10ShovelItem");
    if(vtable == HatchetItem_table || vtable == PickaxeItem_table || vtable == ShovelItem_table) {
        return item->tier;
    } else {
        LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(IdConversion::dynamicToStatic(item->id, IdConversion::ITEM));
        if(factory == nullptr) return nullptr;
        if(factory->getType() == ToolFactory::_factoryTypeId) {
            return ((ToolFactory*) factory)->tier;
        }
        return nullptr;
    }
}


bool KEXToolsModule::patchedCanDestroySpecial(DiggerItem* _this, Block const& block) {
    int blockLevel = KEXToolsModule::getBlockDestroyLevel(IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK));
    return _this->hasBlock(block) && getItemTier(_this)->getLevel() + 1 >= blockLevel;
}


bool KEXToolsModule::patchedHasBlock(DiggerItem* _this, Block const& block) {
    const char* materialName = getBlockMaterialName(IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK));
    if(materialName == nullptr) return false;
    void** vtable = *(void***) _this;
    STATIC_VTABLE_SYMBOL(HatchetItem_table, "_ZTV11HatchetItem");
    STATIC_VTABLE_SYMBOL(PickaxeItem_table, "_ZTV11PickaxeItem");
    STATIC_VTABLE_SYMBOL(ShovelItem_table, "_ZTV10ShovelItem");
    if(vtable == HatchetItem_table) {
        return strcmp(materialName, "wood") == 0;
    } else if(vtable == PickaxeItem_table) {
        return strcmp(materialName, "stone") == 0;
    } else if(vtable == ShovelItem_table) {
        return strcmp(materialName, "dirt") == 0;
    } else {
        LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(IdConversion::dynamicToStatic(_this->id, IdConversion::ITEM));
        if(factory == nullptr) return false;
        if(factory->getType() == ToolFactory::_factoryTypeId) {
            ToolFactory* toolFactory = (ToolFactory*) factory;
            switch(toolFactory->getToolType()) {
                case ToolFactory::AXE:
                    return strcmp(materialName, "wood") == 0;
                case ToolFactory::PICKAXE:
                    return strcmp(materialName, "stone") == 0;
                case ToolFactory::SHOVEL:
                    return strcmp(materialName, "dirt") == 0;
                case ToolFactory::CUSTOM_DIGGER:
                    CustomToolFactory* customToolFactory = (CustomToolFactory*) toolFactory;
                    return customToolFactory->blockMaterials.find(materialName) != customToolFactory->blockMaterials.end();
            }
        }
        return false;
    }
}


// 0 - nothing, 1 - prevent item from breaking, 2 - replace the item with brokenId
unsigned char KEXToolsModule::modifiedItemStackHurtAndBreak(ItemStackBase* stack, int damageValue) {
    int id = IdConversion::dynamicToStatic(stack->getId(), stack->isBlock() ? IdConversion::BLOCK : IdConversion::ITEM);
    auto found = KEXToolsModule::toolsToBrokenIds.find(id);
    int brokenId;
    if(found != KEXToolsModule::toolsToBrokenIds.end()) brokenId = found->second;
    else brokenId = 0;
    bool replace = !( KEXJavaBridge::ToolsModule::onBroke() );
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
        return patchedCanDestroySpecial((DiggerItem*) item, block);
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK10DiggerItem8hasBlockERK5Block"), LAMBDA((HookManager::CallbackController* controller, DiggerItem* item, Block const& block), {
        controller->replace();
        return patchedHasBlock(item, block);
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN10DiggerItem9setBlocksERKNSt6__ndk16vectorIPK5BlockNS0_9allocatorIS4_EEEE"), LAMBDA((HookManager::CallbackController* controller, DiggerItem* item), {
        controller->prevent();
    }, ), HookManager::RETURN | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN13ItemStackBase12hurtAndBreakEiP5Actor"), LAMBDA((HookManager::CallbackController* controller, ItemStackBase* stack, int damageValue, Actor* actor), {
        unsigned char result = modifiedItemStackHurtAndBreak(stack, damageValue);
        if(result == 1) {
            controller->replace();
            return false;
        } else if(result == 2) {
            auto found = toolsToBrokenIds.find(IdConversion::dynamicToStatic(stack->getId(), IdConversion::ITEM));
            controller->replace();
            *stack = ItemStack(*(ItemRegistry::getItemById(IdConversion::staticToDynamic(found->second, IdConversion::ITEM))), 1, 0);
            return true;
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN8GameMode17startDestroyBlockERK8BlockPoshRb"), LAMBDA((GameMode* mode, BlockPos const& pos, unsigned char side, bool& someBoolRef), {
        if(!mode->player->getLevel()->isClientSide()) {
            long long player = mode->player->getUniqueID()->id;
            auto found = lastDestroyed.find(player);
            if(found == lastDestroyed.end()) {
                lastDestroyed.emplace(player, new LastDestroyedBlock());
                found = lastDestroyed.find(player);
            }
            found->second->onEvent(pos.x, pos.y, pos.z, side);
        } else {
            lastDestroyedClient->onEvent(pos.x, pos.y, pos.z, side);
        }
    }, ), HookManager::CALL | HookManager::LISTENER);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN8GameMode12destroyBlockERK8BlockPosh"), LAMBDA((GameMode* mode, BlockPos const& pos, unsigned char side), {
        if(!mode->player->getLevel()->isClientSide()) {
            long long player = mode->player->getUniqueID()->id;
            auto found = lastDestroyed.find(player);
            if(found == lastDestroyed.end()) {
                lastDestroyed.emplace(player, new LastDestroyedBlock());
                found = lastDestroyed.find(player);
            }
            found->second->onEvent(pos.x, pos.y, pos.z, side);
        } else {
            lastDestroyedClient->onEvent(pos.x, pos.y, pos.z, side);
        }
    }, ), HookManager::CALL | HookManager::LISTENER);
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK13ItemStackBase15getAttackDamageEv"), LAMBDA((HookManager::CallbackController* controller, ItemStackBase* stack), {
        Item* item = stack->getItem();
        if(item != nullptr) {
            int id = IdConversion::dynamicToStatic(item->id, IdConversion::ITEM);
            if(isCustomTool(id)) {
                CustomToolFactory* factory = (CustomToolFactory*) LegacyItemRegistry::findFactoryById(id);
                if(factory != nullptr && factory->dynamicDamageEnabled) {
                    controller->replace();
                    ItemInstanceExtra* extra = new ItemInstanceExtra((ItemStack*) stack);
                    int result = factory->baseAttackDamage + KEXJavaBridge::ToolsModule::getAttackDamageBonus(id, 1, stack->getDamageValue(), (jlong) extra, factory->tier->getAttackDamageBonus());
                    delete extra;
                    return result;
                }
            }
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK21ActorHasEquipmentTest8evaluateERK13FilterContext"), LAMBDA((HookManager::CallbackController* controller, ActorHasEquipmentTest* test, FilterContext const& ctx), {
        int dynamicTestId = test->id;
        int testId = IdConversion::dynamicToStatic(dynamicTestId, IdConversion::ITEM);
        if(testId == 359) {
            VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
            ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, ctx.actor);
            if(stack != nullptr) {
                int dynamicStackId = stack->getId();
                int stackId = IdConversion::dynamicToStatic(dynamicStackId, IdConversion::ITEM);
                if(stackId != 359) {
                    LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(stackId);
                    if(factory != nullptr && factory->getType() == ToolFactory::_factoryTypeId) {
                        ToolFactory* toolFactory = (ToolFactory*) factory;
                        if(toolFactory->getToolType() == ToolFactory::SHEARS) {
                            test->id = dynamicStackId;
                            bool result = controller->callAndReplace<bool>(test, &ctx);
                            test->id = dynamicTestId;
                            return result;
                        }
                    }
                }
            }
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
}


float LastDestroyedBlock::getOrCalculateSpeed(ItemStackBase const& stack, Block const& block, WeaponItem* item) {
    if(x == calculatedForX && y == calculatedForY && z == calculatedForZ) {
        return destroySpeed;
    } else {
        calculatedForX = x;
        calculatedForY = y;
        calculatedForZ = z;
        STATIC_SYMBOL(WeaponItem_getDestroySpeed, "_ZNK10WeaponItem15getDestroySpeedERK13ItemStackBaseRK5Block", (WeaponItem*, ItemStackBase const&, Block const&));
        void* output = WeaponItem_getDestroySpeed(item, stack, block);
        float result = *(float*)&output;
        float blockDestroyTime = block.legacy->getDestroySpeed();
        result = blockDestroyTime / KEXJavaBridge::ToolsModule::calcDestroyTime(IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK), block.data, x, y, z, side, blockDestroyTime, 1.0f, 1.0f, blockDestroyTime);
        result = result == 0.0f ? 1.0f : result;
        destroySpeed = result;
        return result;
    }
}


float LastDestroyedBlock::getOrCalculateSpeed(ItemStackBase const& stack, Block const& block, DiggerItem* item) {
    if(x == calculatedForX && y == calculatedForY && z == calculatedForZ) {
        return destroySpeed;
    } else {
        calculatedForX = x;
        calculatedForY = y;
        calculatedForZ = z;
        STATIC_SYMBOL(DiggerItem_getDestroySpeed, "_ZNK10DiggerItem15getDestroySpeedERK13ItemStackBaseRK5Block", (DiggerItem*, ItemStackBase const&, Block const&));
        void* output = DiggerItem_getDestroySpeed(item, stack, block);
        float result = *(float*)&output;
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        float blockDestroyTime = block.legacy->getDestroySpeed();
        float materialDivider = item->speed;
        materialDivider = materialDivider == 0.0f ? 1.0f : materialDivider;
        float efficiencyModifier = item->destroySpeedBonus(stack);
        efficiencyModifier = efficiencyModifier == 0.0f ? 1.0f : result;
        float calc = KEXJavaBridge::ToolsModule::calcDestroyTime(staticId, block.data, x, y, z, side, blockDestroyTime, materialDivider, efficiencyModifier, blockDestroyTime / materialDivider / efficiencyModifier);
        result = blockDestroyTime / calc;
        result = result == 0.0f ? 1.0f : result;
        destroySpeed = result;
        return result;
    }
}


void LastDestroyedBlock::onEvent(int xIn, int yIn, int zIn, unsigned char sideIn) {
    x = xIn, y = yIn, z = zIn, side = sideIn;
}