#include "base.hpp"

#ifndef KEX_MODULES_TOOLS_TYPES_HOE_HPP
#define KEX_MODULES_TOOLS_TYPES_HOE_HPP


class HoeFactory : public ToolFactory {
    public:
    virtual void registerItem();
    HoeFactory(): ToolFactory() {
        enchantType = 64;
    }
    virtual ToolType getToolType() {
        return HOE;
    }
};


class HoeProvider : public DiggerProvider {
    public:
    HoeFactory* factory;
    HoeProvider(HoeFactory* hoeFactory): factory(hoeFactory) {};
    ~HoeProvider();
    virtual HoeFactory* getFactory() {
        return factory;
    }
};


#endif //KEX_MODULES_TOOLS_TYPES_HOE_HPP