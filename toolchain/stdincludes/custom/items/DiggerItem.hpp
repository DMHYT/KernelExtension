#include <stl/vector>
#include <stl.h>

#include <Item.hpp>

#ifndef KEX_ITEMS_DIGGERITEM_HPP
#define KEX_ITEMS_DIGGERITEM_HPP


class DiggerItem : public Item {
    public:
    float speed; // 304
    Item::Tier* tier; // 308
    int attackDamage; // 312
    char extraFiller[200]; // 512
    // virtual int getAttackDamage() const;
    // virtual bool isHandEquipped() const;
    // virtual void* appendFormattedHovertext(const ItemStackBase&, Level&, stl::string&, bool) const;
    // virtual bool isValidRepairItem(const ItemStackBase&, const ItemStackBase&) const;
    // virtual int getEnchantValue() const;
    // virtual float getDestroySpeed(const ItemStackBase&, const Block&) const;
    // virtual bool mineBlock(ItemStack&, const Block&, int, int, int, Actor*) const;
    DiggerItem(const stl::string&, int, int, const Item::Tier&, const stl::vector<const Block*>&);
    bool hasBlock(const Block&) const;
    void setBlocks(const stl::vector<const Block*>&);
};


#endif //KEX_ITEMS_DIGGERITEM_HPP