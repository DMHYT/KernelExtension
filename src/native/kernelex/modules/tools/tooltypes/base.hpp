#include <symbol.h>

#include <innercore/legacy_item_registry.h>
#include <innercore/vtable.h>

#include <Item.hpp>

#ifndef KEX_MODULES_TOOLS_TYPES_BASE_HPP
#define KEX_MODULES_TOOLS_TYPES_BASE_HPP


class ToolFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
    public:
    enum ToolType {
        UNSPECIFIED,
        SWORD,
        AXE,
        PICKAXE,
        SHOVEL,
        HOE,
        CUSTOM_DIGGER,
        CUSTOM_WEAPON,
        SHEARS,
        FLINT_AND_STEEL
    };
    static const int _factoryTypeId = 200;
    Item::Tier* tier = nullptr;
    int enchantType;
    virtual void registerItem() {
        if(tier != nullptr) {
            props.durability = tier->getUses();
            props.enchantValue = tier->getEnchantmentValue();
            props.enchantType = enchantType;
        }
    }
    virtual int getType() {
        return _factoryTypeId;
    }
    virtual ToolType getToolType() {
        return UNSPECIFIED;
    }
};


class DiggerProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    virtual void setupVtable(void* table) {
        LegacyItemProviderBase::setupVtable(table);
        void** vtable = (void**) table;
        VTABLE_FIND_OFFSET(Item_hurtActor, _ZTV4Item, _ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob);
        VTABLE_FIND_OFFSET(Item_mineBlock__instance, _ZTV4Item, _ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor);
        VTABLE_FIND_OFFSET(Item_mineBlock__stack, _ZTV4Item, _ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor);
        vtable[Item_hurtActor] = SYMBOL("mcpe", "_ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob");
        vtable[Item_mineBlock__instance] = SYMBOL("mcpe", "_ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor");
        vtable[Item_mineBlock__stack] = SYMBOL("mcpe", "_ZNK10DiggerItem9mineBlockER9ItemStackRK5BlockiiiP5Actor");
    }
};


class WeaponProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    virtual void setupVtable(void* table) {
        LegacyItemProviderBase::setupVtable(table);
        void** vtable = (void**) table;
        VTABLE_FIND_OFFSET(Item_hurtActor, _ZTV4Item, _ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob);
        VTABLE_FIND_OFFSET(Item_mineBlock__instance, _ZTV4Item, _ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor);
        VTABLE_FIND_OFFSET(Item_mineBlock__stack, _ZTV4Item, _ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor);
        vtable[Item_hurtActor] = SYMBOL("mcpe", "_ZNK10WeaponItem9hurtActorER9ItemStackR5ActorR3Mob");
        vtable[Item_mineBlock__instance] = SYMBOL("mcpe", "_ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor");
        vtable[Item_mineBlock__stack] = SYMBOL("mcpe", "_ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor");
    }
};


#endif //KEX_MODULES_TOOLS_TYPES_BASE_HPP