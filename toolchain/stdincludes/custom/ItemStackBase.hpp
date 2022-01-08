#ifndef KEX_ITEMSTACKBASE_HPP
#define KEX_ITEMSTACKBASE_HPP


#ifndef KEX_ITEM_HPP
    class Item;
#endif

class ItemStackBase {
    public:
    ItemStackBase(Item const&, int, int);
    short getMaxDamage() const;
    bool isBlock() const;
    Item* getItem() const;
    int getId() const;
    short getDamageValue() const;
    ItemStackBase& operator=(ItemStackBase const&);
};


#endif //KEX_ITEMSTACKBASE_HPP