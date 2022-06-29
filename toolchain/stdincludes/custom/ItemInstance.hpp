#ifndef KEX_ITEMINSTANCE_HPP
#define KEX_ITEMINSTANCE_HPP


#ifndef KEX_ITEM_HPP
    class Item;
#endif
#ifndef KEX_ITEMSTACKBASE_HPP
    class ItemStackBase { public: };
#endif

class ItemInstance : public ItemStackBase {
    public:
    char filler[88];
    ItemInstance(const ItemStackBase&);
    ItemInstance(const Item&, int, int);
    ItemInstance& operator=(const ItemInstance&);
};


#endif //KEX_ITEMINSTANCE_HPP