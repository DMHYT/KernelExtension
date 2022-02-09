#include <Actor.hpp>
#include <ActorUniqueID.hpp>
#include <Block.hpp>
#include <BlockLegacy.hpp>
#include <EnchantUtils.hpp>
#include <ItemStackBase.hpp>
#include <ItemInstance.hpp>
#include <ItemStack.hpp>
#include <I18n.hpp>
#include <Level.hpp>
#include <Mob.hpp>
#include <Item.hpp>
#include <items/DiggerItem.hpp>
#include <items/WeaponItem.hpp>
#include <static_symbol.hpp>
#include <innercore/id_conversion_map.h>
#include <innercore/item_extra.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>
#include "../../utils/java_utils.hpp"
#include "classes.hpp"
#include "module.hpp"
#include "patches.hpp"


void CustomToolPatches::_appendFormattedHovertext(Item* _this, ItemStackBase const& stack, Level& level, std::__ndk1::string& text, bool someBool) {
    STATIC_SYMBOL(Item_appendFormattedHovertext, "_ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb", (Item*, ItemStackBase const&, Level&, std::__ndk1::string&, bool));
    Item_appendFormattedHovertext(_this, stack, level, text, someBool);
    text.append("\n\n§9+");
    int staticId = IdConversion::dynamicToStatic(_this->id, IdConversion::ITEM);
    CustomToolFactory* factory = (CustomToolFactory*) LegacyItemRegistry::findFactoryById(staticId);
    if(factory != nullptr) {
        int damage = factory->baseAttackDamage;
        ItemInstanceExtra* extra = new ItemInstanceExtra((ItemStack*) &stack);
        damage += KEXJavaBridge::ToolsModule::getAttackDamageBonus(staticId, 1, stack.getDamageValue(), (jlong) extra, factory->tier->getAttackDamageBonus());
        delete extra;
        damage += (int)((float) EnchantUtils::getEnchantLevel((Enchant::Type) 9, stack) * 1.25);
        text.append(std::__ndk1::to_string(damage));
        text.append(" ");
        text.append(I18n::get("attribute.name.generic.attackDamage"));
        text.append("§r");
    }
}


float CustomToolPatches::Digger::getDestroySpeed(DiggerItem* _this, ItemStackBase const& stack, Block const& block) {
    return KEXToolsModule::lastDestroyedClient->getOrCalculateSpeed(stack, block, _this);
}
bool CustomToolPatches::Digger::hurtActor(DiggerItem* _this, ItemStack& stack, Actor& actor, Mob& mob) {
    bool result = true;
    if(!mob.getLevel()->isClientSide()) {
        long long uid = mob.getUniqueID()->id;
        KEXJavaBridge::ToolsModule::modifyEnchant(0, 0, 0, 0, 0, 0, uid);
        bool onAttack = KEXJavaBridge::ToolsModule::onAttack(actor.getUniqueID()->id, uid);
        if(!onAttack) {
            STATIC_SYMBOL(Item_hurtActor, "_ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob", (Item*, ItemStack&, Actor&, Mob&));
            result = Item_hurtActor((Item*) _this, stack, actor, mob);
        } else result = false;
        VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
        ItemStack* carried = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, &mob);
        stack = *carried;
    }
    return result;
}
bool CustomToolPatches::Digger::mineBlock__instance(DiggerItem* _this, ItemInstance& stack, Block const& block, int x, int y, int z, Actor* actor) {
    if(!actor->getLevel()->isClientSide()) {
        long long uid = actor->getUniqueID()->id;
        unsigned char side = KEXToolsModule::lastDestroyed.find(actor->getUniqueID()->id)->second->side;
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        KEXJavaBridge::ToolsModule::modifyEnchant(x, y, z, side, staticId, block.data, uid);
        KEXJavaBridge::ToolsModule::onMineBlock(x, y, z, side, staticId, block.data, uid);
        bool onDestroy = KEXJavaBridge::ToolsModule::onDestroy(x, y, z, side, staticId, block.data, uid);
        VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
        ItemStack* carried = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, actor);
        stack = ItemInstance(*carried);
        if(!onDestroy) {
            STATIC_SYMBOL(DiggerItem_mineBlock__instance, "_ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor", (Item*, ItemInstance&, Block const&, int, int, int, Actor*));
            DiggerItem_mineBlock__instance(_this, stack, block, x, y, z, actor);
        }
    }
    return true;
}
bool CustomToolPatches::Digger::mineBlock__stack(DiggerItem* _this, ItemStack& stack, Block const& block, int x, int y, int z, Actor* actor) {
    if(!actor->getLevel()->isClientSide()) {
        long long uid = actor->getUniqueID()->id;
        unsigned char side = KEXToolsModule::lastDestroyed.find(actor->getUniqueID()->id)->second->side;
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        KEXJavaBridge::ToolsModule::modifyEnchant(x, y, z, side, staticId, block.data, uid);
        KEXJavaBridge::ToolsModule::onMineBlock(x, y, z, side, staticId, block.data, uid);
        bool onDestroy = KEXJavaBridge::ToolsModule::onDestroy(x, y, z, side, staticId, block.data, uid);
        VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
        ItemStack* carried = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, actor);
        stack = *carried;
        if(!onDestroy) {
            STATIC_SYMBOL(DiggerItem_mineBlock__stack, "_ZNK10DiggerItem9mineBlockER9ItemStackRK5BlockiiiP5Actor", (DiggerItem*, ItemStack&, Block const&, int, int, int, Actor*));
            DiggerItem_mineBlock__stack(_this, stack, block, x, y, z, actor);
        }
    }
    return true;
}
void CustomToolPatches::Digger::appendFormattedHovertext(DiggerItem* _this, ItemStackBase const& stack, Level& level, std::__ndk1::string& text, bool someBool) {
    _appendFormattedHovertext((Item*) _this, stack, level, text, someBool);
}


float CustomToolPatches::Weapon::getDestroySpeed(WeaponItem* _this, ItemStackBase const& stack, Block const& block) {
    return KEXToolsModule::lastDestroyedClient->getOrCalculateSpeed(stack, block, _this);
}
bool CustomToolPatches::Weapon::hurtActor(WeaponItem* _this, ItemStack& stack, Actor& actor, Mob& mob) {
    bool result = true;
    if(!mob.getLevel()->isClientSide()) {
        long long uid = mob.getUniqueID()->id;
        KEXJavaBridge::ToolsModule::modifyEnchant(0, 0, 0, 0, 0, 0, uid);
        bool onAttack = KEXJavaBridge::ToolsModule::onAttack(actor.getUniqueID()->id, uid);
        if(!onAttack) {
            STATIC_SYMBOL(WeaponItem_hurtActor, "_ZNK10WeaponItem9hurtActorER9ItemStackR5ActorR3Mob", (WeaponItem*, ItemStack&, Actor&, Mob&));
            result = WeaponItem_hurtActor(_this, stack, actor, mob);
        } else result = false;
        VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
        ItemStack* carried = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, &mob);
        stack = *carried;
    }
    return result;
}
bool CustomToolPatches::Weapon::mineBlock__instance(WeaponItem* _this, ItemInstance& stack, Block const& block, int x, int y, int z, Actor* actor) {
    if(!actor->getLevel()->isClientSide()) {
        long long uid = actor->getUniqueID()->id;
        unsigned char side = KEXToolsModule::lastDestroyed.find(uid)->second->side;
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        KEXJavaBridge::ToolsModule::modifyEnchant(x, y, z, side, staticId, block.data, uid);
        KEXJavaBridge::ToolsModule::onMineBlock(x, y, z, side, staticId, block.data, uid);
        bool onDestroy = KEXJavaBridge::ToolsModule::onDestroy(x, y, z, side, staticId, block.data, uid);
        VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
        ItemStack* carried = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, actor);
        stack = ItemInstance(*carried);
        if(!onDestroy) {
            STATIC_SYMBOL(Item_mineBlock__instance, "_ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor", (Item*, ItemInstance&, Block const&, int, int, int, Actor*));
            Item_mineBlock__instance((Item*) _this, stack, block, x, y, z, actor);
        }
    }
    return true;
}
bool CustomToolPatches::Weapon::mineBlock__stack(WeaponItem* _this, ItemStack& stack, Block const& block, int x, int y, int z, Actor* actor) {
    if(!actor->getLevel()->isClientSide()) {
        long long uid = actor->getUniqueID()->id;
        unsigned char side = KEXToolsModule::lastDestroyed.find(uid)->second->side;
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        KEXJavaBridge::ToolsModule::modifyEnchant(x, y, z, side, staticId, block.data, uid);
        KEXJavaBridge::ToolsModule::onMineBlock(x, y, z, side, staticId, block.data, uid);
        bool onDestroy = KEXJavaBridge::ToolsModule::onDestroy(x, y, z, side, staticId, block.data, uid);
        VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
        ItemStack* carried = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, actor);
        stack = *carried;
        if(!onDestroy) {
            STATIC_SYMBOL(Item_mineBlock__stack, "_ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor", (Item*, ItemStack&, Block const&, int, int, int, Actor*));
            Item_mineBlock__stack((Item*) _this, stack, block, x, y, z, actor);
        }
    }
    return true;
}
void CustomToolPatches::Weapon::appendFormattedHovertext(WeaponItem* _this, ItemStackBase const& stack, Level& level, std::__ndk1::string& text, bool someBool) {
    _appendFormattedHovertext((Item*) _this, stack, level, text, someBool);
}