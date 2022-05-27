#include "base.hpp"

#ifndef KEX_MODULES_TOOLS_TYPES_SHEARS_HPP
#define KEX_MODULES_TOOLS_TYPES_SHEARS_HPP


class ShearsFactory : public ToolFactory {
    public:
    virtual void registerItem();
    ShearsFactory(): ToolFactory() {
        enchantType = 128;
    }
    virtual ToolType getToolType() {
        return SHEARS;
    }
};


class ShearsProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    ShearsFactory* factory;
    ShearsProvider(ShearsFactory* shearsFactory): factory(shearsFactory) {};
    ~ShearsProvider();
    virtual void setupVtable(void*);
    virtual ShearsFactory* getFactory() {
        return factory;
    }
};


#endif //KEX_MODULES_TOOLS_TYPES_SHEARS_HPP