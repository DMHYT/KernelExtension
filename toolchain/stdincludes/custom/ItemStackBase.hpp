#include <stl/string>

#ifndef KEX_ITEMSTACKBASE_HPP
#define KEX_ITEMSTACKBASE_HPP


#ifndef KEX_BLOCK_HPP
    class Block;
#endif
#ifndef KEX_BLOCKLEGACY_HPP
    class BlockLegacy;
#endif
class CompoundTag;
#ifndef KEX_ITEM_HPP
    class Item;
#endif

class ItemStackBase {
    public:
    virtual void setNull(); // pure virtual
    virtual std::__ndk1::string const& toString(); // pure virtual
    virtual std::__ndk1::string const& toDebugString(); // pure virtual
    ItemStackBase(Block const&, int, CompoundTag const*);
    ItemStackBase(BlockLegacy const&, int, short);
    ItemStackBase(ItemStackBase const&);
    ItemStackBase(Item const&);
    ItemStackBase(Item const&, int, int);
    ItemStackBase(Item const&, int, int, CompoundTag const*);
    ItemStackBase();
    ItemStackBase(Item const&, int);
    short getMaxDamage() const;
    bool isBlock() const;
    Item* getItem() const;
    int getId() const;
    short getDamageValue() const;
    ItemStackBase& operator=(ItemStackBase const&);
};


#endif //KEX_ITEMSTACKBASE_HPP