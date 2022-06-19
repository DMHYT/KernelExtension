#include <stl/string>
#include <stl.h>

#ifndef KEX_ITEMSTACKBASE_HPP
#define KEX_ITEMSTACKBASE_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
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
    char filler[96];
    // virtual void setNull(); // pure virtual
    // virtual const stl::string& toString(); // pure virtual
    // virtual const stl::string& toDebugString(); // pure virtual
    ItemStackBase(const Block&, int, const CompoundTag*);
    ItemStackBase(const BlockLegacy&, int, short);
    ItemStackBase(const ItemStackBase&);
    ItemStackBase(const Item&);
    ItemStackBase(const Item&, int, int);
    ItemStackBase(const Item&, int, int, const CompoundTag*);
    ItemStackBase();
    ItemStackBase(const Item&, int);
    short getMaxDamage() const;
    bool isBlock() const;
    Item* getItem() const;
    bool isNull() const;
    int getId() const;
    short getDamageValue() const;
    ItemStackBase& operator=(const ItemStackBase&);
    ~ItemStackBase();
    void hurtAndBreak(int, Actor*);
};


#endif //KEX_ITEMSTACKBASE_HPP