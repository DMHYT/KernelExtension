#include <items/DiggerItem.hpp>

#ifndef KEX_ITEMS_PICKAXEITEM_HPP
#define KEX_ITEMS_PICKAXEITEM_HPP


class PickaxeItem : public DiggerItem {
    public:
    // virtual bool canDestroySpecial(const Block&) const;
    // virtual void* getEnchantSlot() const;
    // virtual float getDestroySpeed(const ItemStackBase&, const Block&) const;
    PickaxeItem(const std::__ndk1::string&, int, const Item::Tier&);
};


#endif //KEX_ITEMS_PICKAXEITEM_HPP