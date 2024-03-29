#include <stl/string>
#include <stl.h>

#ifndef KEX_ITEMSTACK_HPP
#define KEX_ITEMSTACK_HPP


#ifndef KEX_BLOCK_HPP
    class Block;
#endif
#ifndef KEX_BLOCKLEGACY_HPP
    class BlockLegacy;
#endif
#ifndef KEX_COMPOUNDTAG_HPP
    class CompoundTag;
#endif
#ifndef KEX_ITEM_HPP
    class Item;
#endif
#ifndef KEX_ITEMINSTANCE_HPP
    class ItemInstance;
#endif
#ifndef KEX_ITEMSTACKBASE_HPP
    class ItemStackBase { public: char filler[96]; };
#endif

class ItemStack : public ItemStackBase {
    public:
    // virtual void reinit(const Item&, int, int);
    // virtual void reinit(const BlockLegacy&, int);
    // here these three pure virtual methods are overloaded
    // virtual void setNull();
    // virtual const stl::string& toString() const;
    // virtual const stl::string& toDebugString() const;
    ItemStack(const ItemInstance&);
    ItemStack(const Block&, int, const CompoundTag*);
    ItemStack(const ItemStack&);
    ItemStack(const Item&, int);
    ItemStack(const Item&, int, int);
    ItemStack(const BlockLegacy&, int);
    ItemStack();
    ItemStack& operator=(const ItemStack&);
};


#endif //KEX_ITEMSTACK_HPP