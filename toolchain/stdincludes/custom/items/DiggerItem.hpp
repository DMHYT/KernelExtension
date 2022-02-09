#include <stl/vector>
#include <Item.hpp>

#ifndef KEX_ITEMS_DIGGERITEM_HPP
#define KEX_ITEMS_DIGGERITEM_HPP


class DiggerItem : public Item {
    public:
    float speed; // 304
    Item::Tier* tier; // 308
    int attackDamage; // 312
    // virtual int getAttackDamage() const;
    // virtual bool isHandEquipped() const;
    // virtual void* appendFormattedHovertext(ItemStackBase const&, Level&, std::__ndk1::string&, bool) const;
    // virtual bool isValidRepairItem(ItemStackBase const&, ItemStackBase const&) const;
    // virtual int getEnchantValue() const;
    // virtual float getDestroySpeed(ItemStackBase const&, Block const&) const;
    // virtual bool mineBlock(ItemStack&, Block const&, int, int, int, Actor*) const;
    DiggerItem(std::__ndk1::string const&, int, int, Item::Tier const&, std::__ndk1::vector<Block const*> const&);
    bool hasBlock(Block const&) const;
    void setBlocks(std::__ndk1::vector<Block const*> const&);
};


#endif //KEX_ITEMS_DIGGERITEM_HPP