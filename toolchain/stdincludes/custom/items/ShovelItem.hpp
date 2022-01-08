#include <items/DiggerItem.hpp>

#ifndef KEX_ITEMS_SHOVELITEM_HPP
#define KEX_ITEMS_SHOVELITEM_HPP


class ShovelItem : public DiggerItem {
    public:
    virtual void* executeEvent(ItemStackBase&, std::__ndk1::string const&, RenderParams&) const;
    virtual bool canDestroySpecial(Block const&) const;
    virtual void* getEnchantSlot() const;
    virtual void* _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float, float) const;
    ShovelItem(std::__ndk1::string const&, int, Item::Tier const&);
};


#endif //KEX_ITEMS_SHOVELITEM_HPP