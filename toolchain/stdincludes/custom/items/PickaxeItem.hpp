#include <items/DiggerItem.hpp>

#ifndef KEX_ITEMS_PICKAXEITEM_HPP
#define KEX_ITEMS_PICKAXEITEM_HPP


class PickaxeItem : public DiggerItem {
    public:
    // virtual bool canDestroySpecial(Block const&) const;
    // virtual void* getEnchantSlot() const;
    // virtual float getDestroySpeed(ItemStackBase const&, Block const&) const;
    PickaxeItem(std::__ndk1::string const&, int, Item::Tier const&);
};


#endif //KEX_ITEMS_PICKAXEITEM_HPP