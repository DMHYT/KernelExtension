#include <stl/string>

#ifndef KEX_ITEMSTACK_HPP
#define KEX_ITEMSTACK_HPP


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
#ifndef KEX_ITEMINSTANCE_HPP
    class ItemInstance;
#endif
#ifndef KEX_ITEMSTACKBASE_HPP
    class ItemStackBase { public: };
#endif

class ItemStack : public ItemStackBase {
    public:
    // virtual void reinit(Item const&, int, int);
    // virtual void reinit(BlockLegacy const&, int);
    // here these three pure virtual methods are overloaded
    // virtual void setNull();
    // virtual std::__ndk1::string const& toString() const;
    // virtual std::__ndk1::string const& toDebugString() const;
    ItemStack(ItemInstance const&);
    ItemStack(Block const&, int, CompoundTag const*);
    ItemStack(ItemStack const&);
    ItemStack(Item const&, int);
    ItemStack(Item const&, int, int);
    ItemStack(BlockLegacy const&, int);
    ItemStack();
};


#endif //KEX_ITEMSTACK_HPP