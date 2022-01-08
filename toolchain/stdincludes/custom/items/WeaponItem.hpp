#include <Item.hpp>

#ifndef KEX_ITEMS_WEAPONITEM_HPP
#define KEX_ITEMS_WEAPONITEM_HPP


class WeaponItem : public Item {
    public:
    char filler1[300];
    int attackDamage;
    virtual bool canDestroySpecial(Block const&) const;
    virtual int getAttackDamage() const;
    virtual bool isHandEquipped() const;
    virtual bool canDestroyInCreative() const;
    virtual void* appendFormattedHovertext(ItemStackBase const&, Level&, std::__ndk1::string&, bool) const;
    virtual bool isValidRepairItem(ItemStackBase const&, ItemStackBase const&) const;
    virtual void* getEnchantSlot() const;
    virtual int getEnchantValue() const;
    virtual void* use(ItemStack&, Player&) const;
    virtual float getDestroySpeed(ItemStackBase const&, Block const&) const;
    virtual bool hurtActor(ItemStack&, Actor&, Mob&) const;
    WeaponItem(std::__ndk1::string const&, int, Item::Tier const&);
};


#endif //KEX_ITEMS_WEAPONITEM_HPP