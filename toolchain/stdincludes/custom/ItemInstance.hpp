#ifndef KEX_ITEMINSTANCE_HPP
#define KEX_ITEMINSTANCE_HPP


#ifndef KEX_ITEMSTACKBASE_HPP
    class ItemStackBase { public: };
#endif

class ItemInstance : public ItemStackBase {
    public:
    char filler[88];
    ItemInstance(ItemStackBase const&);
    ItemInstance& operator=(ItemInstance const&);
};


#endif //KEX_ITEMINSTANCE_HPP