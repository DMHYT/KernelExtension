#include "base.hpp"

#ifndef KEX_MODULES_TOOLS_TYPES_PICKAXE_HPP
#define KEX_MODULES_TOOLS_TYPES_PICKAXE_HPP


class PickaxeFactory : public ToolFactory {
    public:
    virtual void registerItem();
    PickaxeFactory(): ToolFactory() {
        enchantType = 1024;
    }
    virtual ToolType getToolType() {
        return PICKAXE;
    }
};


class PickaxeProvider : public DiggerProvider {
    public:
    PickaxeFactory* factory;
    PickaxeProvider(PickaxeFactory* pickaxeFactory): factory(pickaxeFactory) {};
    ~PickaxeProvider();
    virtual PickaxeFactory* getFactory() {
        return factory;
    }
};


#endif //KEX_MODULES_TOOLS_TYPES_PICKAXE_HPP