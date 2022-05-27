#include "base.hpp"

#ifndef KEX_MODULES_TOOLS_TYPES_SHOVEL_HPP
#define KEX_MODULES_TOOLS_TYPES_SHOVEL_HPP


class ShovelFactory : public ToolFactory {
    public:
    virtual void registerItem();
    ShovelFactory(): ToolFactory() {
        enchantType = 2048;
    }
    virtual ToolType getToolType() {
        return SHOVEL;
    }
};


class ShovelProvider : public DiggerProvider {
    public:
    ShovelFactory* factory;
    ShovelProvider(ShovelFactory* shovelFactory): factory(shovelFactory) {};
    ~ShovelProvider();
    virtual ShovelFactory* getFactory() {
        return factory;
    }
};


#endif //KEX_MODULES_TOOLS_TYPES_SHOVEL_HPP