#include <items/DiggerItem.hpp>

#ifndef KEX_ITEMS_HOEITEM_HPP
#define KEX_ITEMS_HOEITEM_HPP


class HoeItem : public DiggerItem {
    public:
    // virtual void* executeEvent(ItemStackBase&, const stl::string&, RenderParams&) const;
    // virtual void* getEnchantSlot() const;
    HoeItem(const stl::string&, int, const Item::Tier&);
};


#endif //KEX_ITEMS_HOEITEM_HPP