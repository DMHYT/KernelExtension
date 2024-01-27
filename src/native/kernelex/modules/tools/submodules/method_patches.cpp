#include <hook.h>
#include <symbol.h>

#include <innercore/vtable.h>
#include <innercore/id_conversion_map.h>

#include <commontypes.hpp>

#include <Actor.hpp>
#include <ActorUniqueID.hpp>
#include <Attribute.hpp>
#include <BlockLegacy.hpp>
#include <Enchant.hpp>
#include <ItemEnchants.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>
#include <MobEffect.hpp>
#include <MobEffectInstance.hpp>
#include <Player.hpp>
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


bool KEXToolPatchesModule::hasBlockMaterial(DiggerItem* _this, const std::string& materialName) {
    if(_this->hasTag(*isAxeTag)) {
        return materialName == "wood";
    } else if(_this->hasTag(*isPickaxeTag)) {
        return materialName == "stone";
    } else if(_this->hasTag(*isShovelTag)) {
        return materialName == "dirt";
    } else {
        int staticId = IdConversion::dynamicToStatic(_this->id, IdConversion::ITEM);
        auto factory = LegacyItemRegistry::findFactoryById(staticId);
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


bool KEXToolPatchesModule::hasBlock(DiggerItem* _this, const Block& block) {
    int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
    std::string materialName = KEXToolsModule::ToolAPI::getBlockMaterialName(staticId);
    if(materialName.empty()) return false;
    return hasBlockMaterial(_this, materialName);
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


int KEXToolPatchesModule::calculateAttackDamage(Actor* actor, Actor* victim) {
    VTABLE_FIND_OFFSET(Actor_getAttribute, _ZTV5Actor, _ZNK5Actor12getAttributeERK9Attribute);
    auto attackDamage = VTABLE_CALL<AttributeInstance*>(Actor_getAttribute, actor, &SharedAttributes::ATTACK_DAMAGE);
    int result = (int) attackDamage->getCurrentValue();
    VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
    ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, actor);
    if(stack != nullptr) result += stack->getAttackDamageKEX(actor, victim);
    VTABLE_FIND_OFFSET(Actor_adjustDamageAmount, _ZTV5Actor, _ZNK5Actor18adjustDamageAmountERi);
    VTABLE_CALL<void>(Actor_adjustDamageAmount, actor, &result);
    auto damageBoost = MobEffect::getById(5);
    auto weakness = MobEffect::getById(18);
    if(damageBoost != nullptr && actor->hasEffect(*damageBoost)) {
        int amplifier = actor->getEffect(*damageBoost)->getAmplifier() + 1;
        for(int i = 0; i < amplifier; i++) result = (int) (((float) result * 1.3f) + 1.0f);
    }
    if(weakness != nullptr && actor->hasEffect(*weakness)) {
        int amplifier = actor->getEffect(*weakness)->getAmplifier() + 1;
        for(int i = 0; i < amplifier; i++) result = (int) (((float) result * 0.8f) - 0.5f);
    }
    if(victim != nullptr) {
        bool someCheck = *((bool*) victim + 292); // idk what's this
        if(!someCheck && stack != nullptr && stack && stack->isEnchanted()) {
            auto enchants = stack->constructItemEnchantsFromUserData();
            auto enchantsVector = enchants.getAllEnchants();
            VTABLE_FIND_OFFSET(Enchant_getDamageBonus, _ZTV7Enchant, _ZNK7Enchant14getDamageBonusEiRK5Actor);
            VTABLE_FIND_OFFSET(Enchant_doPostAttack, _ZTV7Enchant, _ZNK7Enchant12doPostAttackER5ActorS1_i);
            for(const auto& instance : enchantsVector) {
                Enchant* enchant = Enchant::mEnchants.at((unsigned char) instance.type).get();
                result += (int) VTABLE_CALL<float>(Enchant_getDamageBonus, enchant, instance.level, victim);
                VTABLE_CALL<void>(Enchant_doPostAttack, enchant, actor, victim, instance.level);
            }
        }
    }
    return result;
}


void KEXToolPatchesModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK11PickaxeItem17canDestroySpecialERK5Block"),
        LAMBDA((HookManager::CallbackController* controller, PickaxeItem* item, const Block& block), {
            controller->replace();
            return canDestroySpecial((DiggerItem*) item, block);
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK10DiggerItem8hasBlockERK5Block"),
        LAMBDA((HookManager::CallbackController* controller, DiggerItem* item, const Block& block), {
            controller->replace();
            return hasBlock(item, block);
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN10DiggerItem9setBlocksERKNSt6__ndk16vectorIPK5BlockNS0_9allocatorIS4_EEEE"),
        LAMBDA((HookManager::CallbackController* controller, DiggerItem* item), {
            controller->prevent();
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN13ItemStackBase12hurtAndBreakEiP5Actor"),
        LAMBDA((HookManager::CallbackController* controller, ItemStackBase* stack, int damageValue, Actor* actor), {
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
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN5Actor21calculateAttackDamageERS_"),
        LAMBDA((HookManager::CallbackController* controller, Actor* actor, Actor* victim), {
            controller->replace();
            return calculateAttackDamage(actor, victim);
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

}