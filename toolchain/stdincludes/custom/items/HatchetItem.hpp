#include <items/DiggerItem.hpp>

#ifndef KEX_ITEMS_HATCHETITEM_HPP
#define KEX_ITEMS_HATCHETITEM_HPP


class HatchetItem : public DiggerItem {
    public:
    // virtual void* executeEvent(const stl::string&, RenderParams&) const;
    // virtual void* getEnchantSlot() const;
    // virtual float getDestroySpeed(const ItemStackBase&, const Block&) const;
    HatchetItem(const stl::string&, int, const Item::Tier&);
};


#endif //KEX_ITEMS_HATCHETITEM_HPP