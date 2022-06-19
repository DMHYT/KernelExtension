#include <Item.hpp>

#ifndef KEX_ITEMS_SHEARSITEM_HPP
#define KEX_ITEMS_SHEARSITEM_HPP


class ShearsItem : public Item {
    public:
    char extraFiller[212]; // 512
    // virtual bool canDestroySpecial(const Block&) const;
    // virtual void* getEnchantSlot() const;
    // virtual void* dispense(BlockSource&, Container&, int, const Vec3&, unsigned char) const;
    // virtual float getDestroySpeed(const ItemStackBase&, const Block&) const;
    // virtual bool hurtActor(ItemStack&, Actor&, Mob&) const;
    // virtual bool mineBlock(ItemStack&, const Block&, int, int, int, Actor*) const;
    // virtual void* _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float, float) const;
    ShearsItem(const stl::string&, int);
};


#endif //KEX_ITEMS_SHEARSITEM_HPP