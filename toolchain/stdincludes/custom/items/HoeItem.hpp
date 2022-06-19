#include <items/DiggerItem.hpp>

#ifndef KEX_ITEMS_HOEITEM_HPP
#define KEX_ITEMS_HOEITEM_HPP


class HoeItem : public DiggerItem {
    public:
    // virtual void* executeEvent(ItemStackBase&, const std::__ndk1::string&, RenderParams&) const;
    // virtual void* getEnchantSlot() const;
    HoeItem(const std::__ndk1::string&, int, const Item::Tier&);
};


#endif //KEX_ITEMS_HOEITEM_HPP