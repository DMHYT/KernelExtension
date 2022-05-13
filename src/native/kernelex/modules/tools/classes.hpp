#include <set>
#include <string>

#include <innercore/legacy_item_registry.h>

#include <Item.hpp>

#ifndef KEX_MODULES_TOOLS_CLASSES_HPP
#define KEX_MODULES_TOOLS_CLASSES_HPP


class ToolFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
    public:
    enum ToolType {
        UNSPECIFIED,
        SWORD,
        AXE,
        PICKAXE,
        SHOVEL,
        HOE,
        CUSTOM_DIGGER,
        CUSTOM_WEAPON,
        SHEARS,
        FLINT_AND_STEEL
    };
    static const int _factoryTypeId = 200;
    Item::Tier* tier = nullptr;
    int enchantType;
    virtual void registerItem();
    virtual int getType() {
        return _factoryTypeId;
    }
    virtual ToolType getToolType() {
        return UNSPECIFIED;
    }
};
class DiggerProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    virtual void setupVtable(void*);
};
class WeaponProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    virtual void setupVtable(void*);
};


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


#endif //KEX_MODULES_TOOLS_CLASSES_HPP