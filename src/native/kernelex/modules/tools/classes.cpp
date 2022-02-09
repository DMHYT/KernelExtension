#include <symbol.h>
#include <innercore/id_conversion_map.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>
#include <items/HatchetItem.hpp>
#include <items/HoeItem.hpp>
#include <items/PickaxeItem.hpp>
#include <items/ShovelItem.hpp>
#include <items/WeaponItem.hpp>
#include "module.hpp"
#include "patches.hpp"
#include "classes.hpp"


void ToolFactory::registerItem() {
    props.durability = tier->getUses();
    props.enchantValue = tier->getEnchantmentValue();
    props.enchantType = enchantType;
}
void DiggerProvider::setupVtable(void* table) {
    LegacyItemProviderBase::setupVtable(table);
    void** vtable = (void**) table;
    VTABLE_FIND_OFFSET(Item_hurtActor, _ZTV4Item, _ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob);
    VTABLE_FIND_OFFSET(Item_mineBlock__instance, _ZTV4Item, _ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor);
    VTABLE_FIND_OFFSET(Item_mineBlock__stack, _ZTV4Item, _ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor);
    vtable[Item_hurtActor] = SYMBOL("mcpe", "_ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob");
    vtable[Item_mineBlock__instance] = SYMBOL("mcpe", "_ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor");
    vtable[Item_mineBlock__stack] = SYMBOL("mcpe", "_ZNK10DiggerItem9mineBlockER9ItemStackRK5BlockiiiP5Actor");
}
void WeaponProvider::setupVtable(void* table) {
    LegacyItemProviderBase::setupVtable(table);
    void** vtable = (void**) table;
    VTABLE_FIND_OFFSET(Item_hurtActor, _ZTV4Item, _ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob);
    VTABLE_FIND_OFFSET(Item_mineBlock__instance, _ZTV4Item, _ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor);
    VTABLE_FIND_OFFSET(Item_mineBlock__stack, _ZTV4Item, _ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor);
    vtable[Item_hurtActor] = SYMBOL("mcpe", "_ZNK10WeaponItem9hurtActorER9ItemStackR5ActorR3Mob");
    vtable[Item_mineBlock__instance] = SYMBOL("mcpe", "_ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor");
    vtable[Item_mineBlock__stack] = SYMBOL("mcpe", "_ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor");
}


void SwordFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        ItemRegistry::registerItemFixed<WeaponItem>(new SwordProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier);
    }
}


void AxeFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        ItemRegistry::registerItemFixed<HatchetItem>(new AxeProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier);
    }
}


void PickaxeFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        ItemRegistry::registerItemFixed<PickaxeItem>(new PickaxeProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier);
    }
}


void ShovelFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        ItemRegistry::registerItemFixed<ShovelItem>(new ShovelProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier);
    }
}


void HoeFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        ItemRegistry::registerItemFixed<HoeItem>(new HoeProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier);
    }
}


void CustomToolFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        if(isWeapon) {
            WeaponItem* registeredItem = ItemRegistry::registerItemFixed<WeaponItem>(new CustomToolProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier);
            registeredItem->attackDamage = baseAttackDamage + tier->getAttackDamageBonus();
        } else {
            std::__ndk1::vector<Block const*> blocks;
            ItemRegistry::registerItemFixed<DiggerItem>(new CustomToolProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, baseAttackDamage, *tier, blocks);
        }
    }
}

void CustomToolProvider::setupVtable(void* table) {
    LegacyItemProviderBase::setupVtable(table);
    void** vtable = (void**) table;
    if(factory->isWeapon) {
        VTABLE_FIND_OFFSET(WeaponItem_getDestroySpeed, _ZTV10WeaponItem, _ZNK10WeaponItem15getDestroySpeedERK13ItemStackBaseRK5Block);
        VTABLE_FIND_OFFSET(WeaponItem_hurtActor, _ZTV10WeaponItem, _ZNK10WeaponItem9hurtActorER9ItemStackR5ActorR3Mob);
        VTABLE_FIND_OFFSET(Item_mineBlock__instance, _ZTV4Item, _ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor);
        VTABLE_FIND_OFFSET(Item_mineBlock__stack, _ZTV4Item, _ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor);
        vtable[WeaponItem_getDestroySpeed] = ADDRESS(CustomToolPatches::Weapon::getDestroySpeed);
        vtable[WeaponItem_hurtActor] = ADDRESS(CustomToolPatches::Weapon::hurtActor);
        vtable[Item_mineBlock__instance] = ADDRESS(CustomToolPatches::Weapon::mineBlock__instance);
        vtable[Item_mineBlock__stack] = ADDRESS(CustomToolPatches::Weapon::mineBlock__stack);
        if(factory->dynamicDamageEnabled) {
            VTABLE_FIND_OFFSET(Item_appendFormattedHovertext, _ZTV4Item, _ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb);
            vtable[Item_appendFormattedHovertext] = ADDRESS(CustomToolPatches::Weapon::appendFormattedHovertext);
        }
    } else {
        VTABLE_FIND_OFFSET(DiggerItem_getDestroySpeed, _ZTV10DiggerItem, _ZNK10DiggerItem15getDestroySpeedERK13ItemStackBaseRK5Block);
        VTABLE_FIND_OFFSET(Item_hurtActor, _ZTV4Item, _ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob);
        VTABLE_FIND_OFFSET(Item_mineBlock__instance, _ZTV4Item, _ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor);
        VTABLE_FIND_OFFSET(DiggerItem_mineBlock__stack, _ZTV10DiggerItem, _ZNK10DiggerItem9mineBlockER9ItemStackRK5BlockiiiP5Actor);
        VTABLE_FIND_OFFSET(Item_canDestroySpecial, _ZTV4Item, _ZNK4Item17canDestroySpecialERK5Block);
        vtable[DiggerItem_getDestroySpeed] = ADDRESS(CustomToolPatches::Digger::getDestroySpeed);
        vtable[Item_hurtActor] = ADDRESS(CustomToolPatches::Digger::hurtActor);
        vtable[Item_mineBlock__instance] = ADDRESS(CustomToolPatches::Digger::mineBlock__instance);
        vtable[DiggerItem_mineBlock__stack] = ADDRESS(CustomToolPatches::Digger::mineBlock__stack);
        vtable[Item_canDestroySpecial] = ADDRESS(KEXToolsModule::patchedCanDestroySpecial);
        if(factory->dynamicDamageEnabled) {
            VTABLE_FIND_OFFSET(Item_appendFormattedHovertext, _ZTV4Item, _ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb);
            vtable[Item_appendFormattedHovertext] = ADDRESS(CustomToolPatches::Digger::appendFormattedHovertext);
        }
    }
}