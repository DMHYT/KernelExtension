#include <Item.hpp>

#ifndef KEX_ITEMS_FLINTANDSTEELITEM_HPP
#define KEX_ITEMS_FLINTANDSTEELITEM_HPP


class FlintAndSteelItem : public Item {
    public:
    // virtual bool isDestructive(int) const;
    // virtual int getEnchantSlot() const;
    // virtual void* dispense(BlockSource&, Container&, int, Vec3 const&, unsigned char) const;
    // virtual void* hurtActor(ItemStack&, Actor&, Mob&) const;
    // virtual void* _calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&) const;
    // virtual void* _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float, float) const;
    FlintAndSteelItem(std::__ndk1::string const&, int);
};


#endif //KEX_ITEMS_FLINTANDSTEELITEM_HPP