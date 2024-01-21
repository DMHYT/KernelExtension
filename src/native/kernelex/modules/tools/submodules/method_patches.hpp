#include <mod.h>

#include <commontypes.hpp>

#include <Block.hpp>
#include <items/DiggerItem.hpp>
#include <ItemStackBase.hpp>

#ifndef KEX_MODULES_TOOLS_SUBMODULES_PATCHES_HPP
#define KEX_MODULES_TOOLS_SUBMODULES_PATCHES_HPP


class KEXToolPatchesModule : public Module {
    public:
    static HashedString* isAxeTag;
    static HashedString* isPickaxeTag;
    static HashedString* isShovelTag;
    static bool canDestroySpecial(DiggerItem*, const Block&);
    static bool hasBlockMaterial(DiggerItem*, const std::string&);
    static bool hasBlock(DiggerItem*, const Block&);
    static unsigned char hurtAndBreak(ItemStackBase*, int);
    static int calculateAttackDamage(Actor* actor, Actor* victim);
    KEXToolPatchesModule(Module* parent): Module(parent, "kex.tools.patches") {};
    virtual void initialize();
};


#endif //KEX_MODULES_TOOLS_SUBMODULES_PATCHES_HPP