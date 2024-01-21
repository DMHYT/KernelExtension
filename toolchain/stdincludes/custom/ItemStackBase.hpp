#include <stl/memory>
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
#ifndef KEX_COMPOUNDTAG_HPP
    class CompoundTag;
#endif
#ifndef KEX_ITEM_HPP
    class Item;
#endif
#ifndef KEX_ITEMENCHANTS_HPP
    class ItemEnchants { public: char filler[40]; };
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
    Block* getBlock() const;
    Item* getItem() const;
    bool isNull() const;
    int getId() const;
    short getDamageValue() const;
    ItemStackBase& operator=(const ItemStackBase&);
    ~ItemStackBase();
    void hurtAndBreak(int, Actor*);
    operator bool() const;
    bool hasUserData() const;
    CompoundTag* getUserData() const;
    void setUserData(stl::unique_ptr<CompoundTag>);
    int getAttackDamage() const;
    bool isEnchanted() const;
    ItemEnchants constructItemEnchantsFromUserData() const;
    // Added by InnerCore
    unsigned short getCount() const;
    int getAuxValue() const;
    // custom
    int getAttackDamageKEX(Actor* attacker, Actor* victim) const;
};


#endif //KEX_ITEMSTACKBASE_HPP