#include <Item.hpp>

#ifndef KEX_ITEMS_WEAPONITEM_HPP
#define KEX_ITEMS_WEAPONITEM_HPP


class WeaponItem : public Item {
    public:
    int attackDamage; // 304
    char extraFiller[208]; // 512
    // virtual bool canDestroySpecial(const Block&) const;
    // virtual int getAttackDamage() const;
    // virtual bool isHandEquipped() const;
    // virtual bool canDestroyInCreative() const;
    // virtual void* appendFormattedHovertext(const ItemStackBase&, Level&, std::__ndk1::string&, bool) const;
    // virtual bool isValidRepairItem(const ItemStackBase&, const ItemStackBase&) const;
    // virtual void* getEnchantSlot() const;
    // virtual int getEnchantValue() const;
    // virtual void* use(ItemStack&, Player&) const;
    // virtual float getDestroySpeed(const ItemStackBase&, const Block&) const;
    // virtual bool hurtActor(ItemStack&, Actor&, Mob&) const;
    WeaponItem(const std::__ndk1::string&, int, const Item::Tier&);
};


#endif //KEX_ITEMS_WEAPONITEM_HPP