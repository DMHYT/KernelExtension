#include <items/DiggerItem.hpp>

#ifndef KEX_ITEMS_HATCHETITEM_HPP
#define KEX_ITEMS_HATCHETITEM_HPP


class HatchetItem : public DiggerItem {
    public:
    // virtual void* executeEvent(std::__ndk1::string const&, RenderParams&) const;
    // virtual void* getEnchantSlot() const;
    // virtual float getDestroySpeed(ItemStackBase const&, Block const&) const;
    HatchetItem(std::__ndk1::string const&, int, Item::Tier const&);
};


#endif //KEX_ITEMS_HATCHETITEM_HPP