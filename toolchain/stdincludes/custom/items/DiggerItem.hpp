#include <stl/vector>
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
    // virtual void* appendFormattedHovertext(const ItemStackBase&, Level&, std::__ndk1::string&, bool) const;
    // virtual bool isValidRepairItem(const ItemStackBase&, const ItemStackBase&) const;
    // virtual int getEnchantValue() const;
    // virtual float getDestroySpeed(const ItemStackBase&, const Block&) const;
    // virtual bool mineBlock(ItemStack&, const Block&, int, int, int, Actor*) const;
    DiggerItem(const std::__ndk1::string&, int, int, const Item::Tier&, std::__ndk1::vector<const Block*> const&);
    bool hasBlock(const Block&) const;
    void setBlocks(std::__ndk1::vector<const Block*> const&);
};


#endif //KEX_ITEMS_DIGGERITEM_HPP