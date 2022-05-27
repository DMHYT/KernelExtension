#include "base.hpp"

#ifndef KEX_MODULES_TOOLS_TYPES_FLINTANDSTEEL_HPP
#define KEX_MODULES_TOOLS_TYPES_FLINTANDSTEEL_HPP


class FlintAndSteelFactory : public ToolFactory {
    public:
    virtual void registerItem();
    FlintAndSteelFactory(): ToolFactory() {
        enchantType = 256;
    }
    virtual ToolType getToolType() {
        return FLINT_AND_STEEL;
    }
};


class FlintAndSteelProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    FlintAndSteelFactory* factory;
    FlintAndSteelProvider(FlintAndSteelFactory* flintAndSteelFactory): factory(flintAndSteelFactory) {};
    ~FlintAndSteelProvider();
    virtual void setupVtable(void*);
    virtual FlintAndSteelFactory* getFactory() {
        return factory;
    }
};


#endif //KEX_MODULES_TOOLS_TYPES_FLINTANDSTEEL_HPP