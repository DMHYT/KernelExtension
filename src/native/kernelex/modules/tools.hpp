#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <mod.h>
#include <innercore/item_registry.h>
#include <innercore/legacy_item_registry.h>
#include <Item.hpp>
#include <items/DiggerItem.hpp>
#include <items/HatchetItem.hpp>
#include <items/WeaponItem.hpp>

#ifndef KEX_MODULES_TOOLS_HPP
#define KEX_MODULES_TOOLS_HPP


class BlockDataInterface {
    public:
    std::string materialName = std::string("");
    int destroyLevel = 0;
    bool isNative = false;
};


class CustomWeaponItem;
class CustomDiggerItem;
class LastDestroyedBlock {
    public:
    int x = 0;
    int y = 0;
    int z = 0;
    unsigned char side = 0;
    float destroyTime = 0.0f;
    int calculatedForX = 0;
    int calculatedForY = 0;
    int calculatedForZ = 0;
    LastDestroyedBlock() {};
    float getOrCalculateSpeed(ItemStackBase const&, Block const&, CustomWeaponItem*);
    float getOrCalculateSpeed(ItemStackBase const&, Block const&, CustomDiggerItem*);
    void onEvent(int, int, int, unsigned char);
};


class KEXToolsModule : public Module {
    public:
    static LastDestroyedBlock* lastDestroyed;
    static std::unordered_map<std::string, std::vector<int>> materializedBlocks;
    static std::unordered_map<int, BlockDataInterface*> blockData;
    static std::unordered_map<int, int> toolsToBrokenIds;
    static std::unordered_set<int> customTools;
    static bool isCustomTool(int id);
    static void putNeededBlocksByMaterialName(std::string const&, DiggerItem*);
    static void addMaterializedBlock(int id, std::string const&);
    static const char* getBlockMaterialName(int id);
    static int getBlockDestroyLevel(int id);
    static bool getBlockIsNative(int id);
    static void setBlockMaterialName(int id, const char* materialName);
    static void setBlockDestroyLevel(int id, int destroyLevel);
    static void setBlockIsNative(int id, bool isNative);
    static bool patchedCanDestroySpecial(DiggerItem*, Block const&);
    static unsigned char modifiedItemStackHurtAndBreak(ItemStackBase*, int);
    KEXToolsModule(Module* parent): Module(parent, "kex.tools") {};
    virtual void initialize();
};


class ToolFactory : public LegacyItemRegistry::LegacyItemFactoryBase {
    public:
    Item::Tier* tier;
    void setTier(Item::Tier* itemTier);
};


class SwordFactory : public ToolFactory {
    public:
    virtual void registerItem();
};
class SwordProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    SwordFactory* factory;
    SwordProvider(SwordFactory* swordFactory): factory(swordFactory) {};
    ~SwordProvider();
    virtual SwordFactory* getFactory();
};


class AxeFactory : public ToolFactory {
    public:
    virtual void registerItem();
};
class AxeProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    AxeFactory* factory;
    AxeProvider(AxeFactory* axeFactory): factory(axeFactory) {};
    ~AxeProvider();
    virtual AxeFactory* getFactory();
};


class PickaxeFactory : public ToolFactory {
    public:
    virtual void registerItem();
};
class PickaxeProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    PickaxeFactory* factory;
    PickaxeProvider(PickaxeFactory* pickaxeFactory): factory(pickaxeFactory) {};
    ~PickaxeProvider();
    virtual PickaxeFactory* getFactory();
};


class ShovelFactory : public ToolFactory {
    public:
    virtual void registerItem();
};
class ShovelProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    ShovelFactory* factory;
    ShovelProvider(ShovelFactory* shovelFactory): factory(shovelFactory) {};
    ~ShovelProvider();
    virtual ShovelFactory* getFactory();
};


class HoeFactory : public ToolFactory {
    public:
    virtual void registerItem();
};
class HoeProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    HoeFactory* factory;
    HoeProvider(HoeFactory* hoeFactory): factory(hoeFactory) {};
    ~HoeProvider();
    virtual HoeFactory* getFactory();
};


class CustomWeaponItem : public WeaponItem {
    public:
    virtual float getDestroySpeed(ItemStackBase const&, Block const&) const;
    virtual bool hurtActor(ItemStack&, Actor&, Mob&) const;
    virtual bool mineBlock(ItemStack&, Block const&, int, int, int, Actor*) const;
    CustomWeaponItem(std::__ndk1::string const&, int, int, Item::Tier const&);
};
class CustomDiggerItem : public DiggerItem {
    public:
    virtual float getDestroySpeed(ItemStackBase const&, Block const&) const;
    virtual bool hurtActor(ItemStack&, Actor&, Mob&) const;
    virtual bool mineBlock(ItemStack&, Block const&, int, int, int, Actor*) const;
    CustomDiggerItem(std::__ndk1::string const&, int, int, Item::Tier const&, std::vector<std::string> const&);
};
class CustomToolFactory : public ToolFactory {
    public:
    bool isWeapon = false;
    std::vector<std::string> blockMaterials;
    int baseAttackDamage = 0;
    virtual void registerItem();
    void setIsWeapon(bool);
    void setBlockMaterials(std::vector<std::string> const&);
    void setBaseAttackDamage(int);
};
class CustomToolProvider : public LegacyItemRegistry::LegacyItemProviderBase {
    public:
    CustomToolFactory* factory;
    CustomToolProvider(CustomToolFactory* customToolFactory): factory(customToolFactory) {};
    ~CustomToolProvider();
    virtual CustomToolFactory* getFactory();
};


#endif //KEX_MODULES_TOOLS_HPP