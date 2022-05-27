#include "base.hpp"

#ifndef KEX_MODULES_TOOLS_TYPES_SWORD_HPP
#define KEX_MODULES_TOOLS_TYPES_SWORD_HPP


class SwordFactory : public ToolFactory {
    public:
    virtual void registerItem();
    SwordFactory(): ToolFactory() {
        enchantType = 16;
    }
    virtual ToolType getToolType() {
        return SWORD;
    }
};


class SwordProvider : public WeaponProvider {
    public:
    SwordFactory* factory;
    SwordProvider(SwordFactory* swordFactory): factory(swordFactory) {};
    ~SwordProvider();
    virtual SwordFactory* getFactory() {
        return factory;
    }
};


#endif //KEX_MODULES_TOOLS_TYPES_SWORD_HPP