#include <logger.h>
#include <Actor.hpp>
#include <ActorUniqueID.hpp>
#include <Block.hpp>
#include <BlockLegacy.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>
#include <Mob.hpp>
#include <Item.hpp>
#include <items/DiggerItem.hpp>
#include <items/WeaponItem.hpp>
#include <static_symbol.hpp>
#include <innercore/id_conversion_map.h>
#include "../../utils/java_utils.hpp"
#include "module.hpp"
#include "patches.hpp"


void ____l(const char* m) {
    Logger::debug("KEX", m);
    Logger::flush();
}


float CustomToolPatches::Digger::getDestroySpeed(DiggerItem* _this, ItemStackBase const& stack, Block const& block) {
    return KEXToolsModule::lastDestroyed->getOrCalculateSpeed(stack, block, _this);
}
bool CustomToolPatches::Digger::hurtActor(DiggerItem* _this, ItemStack& stack, Actor& actor, Mob& mob) {
    ____l("Digger hurtActor BEGIN");
    bool result = true;
    ____l("Before modifyEnchant");
    KEXJavaBridge::ToolsModule::modifyEnchant((jlong) &stack, KEXToolsModule::lastDestroyed->x, KEXToolsModule::lastDestroyed->y, KEXToolsModule::lastDestroyed->z, KEXToolsModule::lastDestroyed->side, 0, 0);
    ____l("After modifyEnchant");
    ____l("Before onAttack");
    bool onAttack = KEXJavaBridge::ToolsModule::onAttack((jlong) &stack, actor.getUniqueID()->id, mob.getUniqueID()->id);
    ____l("After onAttack");
    if(!onAttack) {
        ____l("Before static symbol");
        STATIC_SYMBOL(Item_hurtActor, "_ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob", (Item*, ItemStack&, Actor&, Mob&));
        result = Item_hurtActor((Item*) _this, stack, actor, mob);
        ____l("After static symbol");
    } else result = false;
    ____l("Digger hurtActor END");
    return result;
}
bool CustomToolPatches::Digger::mineBlock(DiggerItem* _this, ItemStack& stack, Block const& block, int x, int y, int z, Actor* actor) {
    int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
    KEXJavaBridge::ToolsModule::modifyEnchant((jlong) &stack, x, y, z, KEXToolsModule::lastDestroyed->side, staticId, block.data);
    KEXJavaBridge::ToolsModule::onMineBlock((jlong) &stack, x, y, z, KEXToolsModule::lastDestroyed->side, staticId, block.data);
    bool onDestroy = KEXJavaBridge::ToolsModule::onDestroy((jlong) &stack, x, y, z, KEXToolsModule::lastDestroyed->side, staticId, block.data, actor->getUniqueID()->id);
    if(!onDestroy) {
        STATIC_SYMBOL(DiggerItem_mineBlock, "_ZNK10DiggerItem9mineBlockER9ItemStackRK5BlockiiiP5Actor", (DiggerItem*, ItemStack&, Block const&, int, int, int, Actor*));
        DiggerItem_mineBlock(_this, stack, block, x, y, z, actor);
    }
    return true;
}


float CustomToolPatches::Weapon::getDestroySpeed(WeaponItem* _this, ItemStackBase const& stack, Block const& block) {
    return KEXToolsModule::lastDestroyed->getOrCalculateSpeed(stack, block, _this);
}
bool CustomToolPatches::Weapon::hurtActor(WeaponItem* _this, ItemStack& stack, Actor& actor, Mob& mob) {
    bool result = true;
    KEXJavaBridge::ToolsModule::modifyEnchant((jlong) &stack, KEXToolsModule::lastDestroyed->x, KEXToolsModule::lastDestroyed->y, KEXToolsModule::lastDestroyed->z, KEXToolsModule::lastDestroyed->side, 0, 0);
    bool onAttack = KEXJavaBridge::ToolsModule::onAttack((jlong) &stack, actor.getUniqueID()->id, mob.getUniqueID()->id);
    if(!onAttack) {
        STATIC_SYMBOL(WeaponItem_hurtActor, "_ZNK10WeaponItem9hurtActorER9ItemStackR5ActorR3Mob", (WeaponItem*, ItemStack&, Actor&, Mob&));
        result = WeaponItem_hurtActor(_this, stack, actor, mob);
    } else result = false;
    return result;
}
bool CustomToolPatches::Weapon::mineBlock(WeaponItem* _this, ItemStack& stack, Block const& block, int x, int y, int z, Actor* actor) {
    int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
    KEXJavaBridge::ToolsModule::modifyEnchant((jlong) &stack, x, y, z, KEXToolsModule::lastDestroyed->side, staticId, block.data);
    KEXJavaBridge::ToolsModule::onMineBlock((jlong) &stack, x, y, z, KEXToolsModule::lastDestroyed->side, staticId, block.data);
    bool onDestroy = KEXJavaBridge::ToolsModule::onDestroy((jlong) &stack, x, y, z, KEXToolsModule::lastDestroyed->side, staticId, block.data, (jlong) actor);
    if(!onDestroy) {
        STATIC_SYMBOL(Item_mineBlock, "_ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor", (Item*, ItemStack&, Block const&, int, int, int, Actor*));
        Item_mineBlock((Item*) _this, stack, block, x, y, z, actor);
    }
    return true;
}