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
#ifndef KEX_MOB_HPP
    class Mob;
#endif
#ifndef KEX_ITEMS_DIGGERITEM_HPP
    class DiggerItem;
#endif
#ifndef KEX_ITEMS_WEAPONITEM_HPP
    class WeaponItem;
#endif

namespace CustomToolPatches {
    namespace Digger {
        float getDestroySpeed(DiggerItem*, ItemStackBase const&, Block const&);
        bool hurtActor(DiggerItem*, ItemStack&, Actor&, Mob&);
        bool mineBlock(DiggerItem*, ItemStack&, Block const&, int, int, int, Actor*);
    }
    namespace Weapon {
        float getDestroySpeed(WeaponItem*, ItemStackBase const&, Block const&);
        bool hurtActor(WeaponItem*, ItemStack&, Actor&, Mob&);
        bool mineBlock(WeaponItem*, ItemStack&, Block const&, int, int, int, Actor*);
    }
}


#endif //KEX_MODULES_TOOLS_PATCHES_HPP