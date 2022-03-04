#include <stl/string>

#ifndef KEX_MODULES_TOOLS_PATCHES_HPP
#define KEX_MODULES_TOOLS_PATCHES_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
#ifndef KEX_BLOCK_HPP
    class Block;
#endif
#ifndef KEX_ITEMSTACKBASE_HPP
    class ItemStackBase;
#endif
#ifndef KEX_ITEMSTACK_HPP
    class ItemStack;
#endif
#ifndef KEX_LEVEL_HPP
    class Level;
#endif
#ifndef KEX_MOB_HPP
    class Mob;
#endif
#ifndef KEX_ITEMS_DIGGERITEM_HPP
    class DiggerItem;
#endif
#ifndef KEX_ITEMS_WEAPONITEM_HPP
    class WeaponItem;
#endif
#ifndef KEX_ITEMS_SHEARSITEM_HPP
    class ShearsItem;
#endif

namespace CustomToolPatches {
    namespace Digger {
        float getDestroySpeed(DiggerItem*, ItemStackBase const&, Block const&);
        bool hurtActor(DiggerItem*, ItemStack&, Actor&, Mob&);
        bool mineBlock__instance(DiggerItem*, ItemInstance&, Block const&, int, int, int, Actor*);
        bool mineBlock__stack(DiggerItem*, ItemStack&, Block const&, int, int, int, Actor*);
        void appendFormattedHovertext(DiggerItem*, ItemStackBase const&, Level&, std::__ndk1::string&, bool);
    }
    namespace Weapon {
        float getDestroySpeed(WeaponItem*, ItemStackBase const&, Block const&);
        bool hurtActor(WeaponItem*, ItemStack&, Actor&, Mob&);
        bool mineBlock__instance(WeaponItem*, ItemInstance&, Block const&, int, int, int, Actor*);
        bool mineBlock__stack(WeaponItem*, ItemStack&, Block const&, int, int, int, Actor*);
        void appendFormattedHovertext(WeaponItem*, ItemStackBase const&, Level&, std::__ndk1::string&, bool);
    }
    void _appendFormattedHovertext(Item*, ItemStackBase const&, Level&, std::__ndk1::string&, bool);
    float _shearsTieredGetDestroySpeed(ShearsItem*, ItemStackBase const&, Block const&);
}


#endif //KEX_MODULES_TOOLS_PATCHES_HPP