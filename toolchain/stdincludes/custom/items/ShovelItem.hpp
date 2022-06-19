#include <items/DiggerItem.hpp>

#ifndef KEX_ITEMS_SHOVELITEM_HPP
#define KEX_ITEMS_SHOVELITEM_HPP


class ShovelItem : public DiggerItem {
    public:
    // virtual void* executeEvent(ItemStackBase&, const std::__ndk1::string&, RenderParams&) const;
    // virtual bool canDestroySpecial(const Block&) const;
    // virtual void* getEnchantSlot() const;
    // virtual void* _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float, float) const;
    ShovelItem(const std::__ndk1::string&, int, const Item::Tier&);
};


#endif //KEX_ITEMS_SHOVELITEM_HPP