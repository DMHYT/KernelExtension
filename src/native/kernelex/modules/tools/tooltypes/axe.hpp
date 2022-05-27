#include "base.hpp"

#ifndef KEX_MODULES_TOOLS_TYPES_AXE_HPP
#define KEX_MODULES_TOOLS_TYPES_AXE_HPP


class AxeFactory : public ToolFactory {
    public:
    virtual void registerItem();
    AxeFactory(): ToolFactory() {
        enchantType = 512;
    }
    virtual ToolType getToolType() {
        return AXE;
    }
};


class AxeProvider : public DiggerProvider {
    public:
    AxeFactory* factory;
    AxeProvider(AxeFactory* axeFactory): factory(axeFactory) {};
    ~AxeProvider();
    virtual AxeFactory* getFactory() {
        return factory;
    }
};


#endif //KEX_MODULES_TOOLS_TYPES_AXE_HPP