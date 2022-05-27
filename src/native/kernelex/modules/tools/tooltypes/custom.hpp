#include <set>
#include <string>

#include "base.hpp"

#ifndef KEX_MODULES_TOOLS_TYPES_CUSTOM_HPP
#define KEX_MODULES_TOOLS_TYPES_CUSTOM_HPP


class CustomToolFactory : public ToolFactory {
    public:
    bool isWeapon = false;
    std::set<std::string> blockMaterials;
    int baseAttackDamage = 0;
    bool dynamicDamageEnabled = false;
    virtual void registerItem();
    virtual ToolType getToolType() {
        return isWeapon ? CUSTOM_WEAPON : CUSTOM_DIGGER;
    }
};


class CustomToolProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    CustomToolFactory* factory;
    CustomToolProvider(CustomToolFactory* customToolFactory): factory(customToolFactory) {};
    ~CustomToolProvider();
    virtual void setupVtable(void*);
    virtual CustomToolFactory* getFactory() {
        return factory;
    }
};


#endif //KEX_MODULES_TOOLS_TYPES_CUSTOM_HPP