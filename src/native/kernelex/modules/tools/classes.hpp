#include <string>
#include <vector>
#include <innercore/legacy_item_registry.h>
#include <Item.hpp>

#ifndef KEX_MODULES_TOOLS_CLASSES_HPP
#define KEX_MODULES_TOOLS_CLASSES_HPP


class ToolFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
    public:
    Item::Tier* tier;
    int enchantType;
    virtual void registerItem();
};


class SwordFactory : public ToolFactory {
    public:
    virtual void registerItem();
    SwordFactory(): ToolFactory() {
        enchantType = 16;
    }
};
class SwordProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    SwordFactory* factory;
    SwordProvider(SwordFactory* swordFactory): factory(swordFactory) {};
    ~SwordProvider();
    virtual SwordFactory* getFactory() {
        return factory;
    }
};


class AxeFactory : public ToolFactory {
    public:
    virtual void registerItem();
    AxeFactory(): ToolFactory() {
        enchantType = 512;
    }
};
class AxeProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    AxeFactory* factory;
    AxeProvider(AxeFactory* axeFactory): factory(axeFactory) {};
    ~AxeProvider();
    virtual AxeFactory* getFactory() {
        return factory;
    }
};


class PickaxeFactory : public ToolFactory {
    public:
    virtual void registerItem();
    PickaxeFactory(): ToolFactory() {
        enchantType = 1024;
    }
};
class PickaxeProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    PickaxeFactory* factory;
    PickaxeProvider(PickaxeFactory* pickaxeFactory): factory(pickaxeFactory) {};
    ~PickaxeProvider();
    virtual PickaxeFactory* getFactory() {
        return factory;
    }
};


class ShovelFactory : public ToolFactory {
    public:
    virtual void registerItem();
    ShovelFactory(): ToolFactory() {
        enchantType = 2048;
    }
};
class ShovelProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    ShovelFactory* factory;
    ShovelProvider(ShovelFactory* shovelFactory): factory(shovelFactory) {};
    ~ShovelProvider();
    virtual ShovelFactory* getFactory() {
        return factory;
    }
};


class HoeFactory : public ToolFactory {
    public:
    virtual void registerItem();
    HoeFactory(): ToolFactory() {
        enchantType = 64;
    }
};
class HoeProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    HoeFactory* factory;
    HoeProvider(HoeFactory* hoeFactory): factory(hoeFactory) {};
    ~HoeProvider();
    virtual HoeFactory* getFactory() {
        return factory;
    }
};


class CustomToolFactory : public ToolFactory {
    public:
    bool isWeapon = false;
    std::vector<std::string> blockMaterials;
    int baseAttackDamage = 0;
    virtual void registerItem();
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


#endif //KEX_MODULES_TOOLS_CLASSES_HPP