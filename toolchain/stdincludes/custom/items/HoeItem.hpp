#include <items/DiggerItem.hpp>

#ifndef KEX_ITEMS_HOEITEM_HPP
#define KEX_ITEMS_HOEITEM_HPP


class HoeItem : public DiggerItem {
    public:
    virtual void* executeEvent(ItemStackBase&, std::__ndk1::string const&, RenderParams&) const;
    virtual void* getEnchantSlot() const;
    HoeItem(std::__ndk1::string const&, int, Item::Tier const&);
};


#endif //KEX_ITEMS_HOEITEM_HPP