#include <Item.hpp>

#ifndef KEX_ITEMS_FLINTANDSTEELITEM_HPP
#define KEX_ITEMS_FLINTANDSTEELITEM_HPP


class FlintAndSteelItem : public Item {
    public:
    char extraFiller[212]; // 512
    // virtual bool isDestructive(int) const;
    // virtual int getEnchantSlot() const;
    // virtual void* dispense(BlockSource&, Container&, int, const Vec3&, unsigned char) const;
    // virtual void* hurtActor(ItemStack&, Actor&, Mob&) const;
    // virtual void* _calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&) const;
    // virtual void* _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float, float) const;
    FlintAndSteelItem(const stl::string&, int);
};


#endif //KEX_ITEMS_FLINTANDSTEELITEM_HPP