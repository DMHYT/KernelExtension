#include <string>
#include <unordered_map>
#include <unordered_set>
#include <mod.h>
#include <Block.hpp>
#include <items/DiggerItem.hpp>
#include <items/WeaponItem.hpp>
#include <ItemStackBase.hpp>

#ifndef KEX_MODULES_TOOLS_MODULE_HPP
#define KEX_MODULES_TOOLS_MODULE_HPP


class BlockDataInterface {
    public:
    std::string materialName = std::string("");
    int destroyLevel = 0;
    bool isNative = false;
};


class LastDestroyedBlock {
    public:
    int x = 0;
    int y = 0;
    int z = 0;
    unsigned char side = 0;
    float destroySpeed = 1.0f;
    int calculatedForX = 0;
    int calculatedForY = 0;
    int calculatedForZ = 0;
    LastDestroyedBlock() {};
    float getOrCalculateSpeed(ItemStackBase const&, Block const&, WeaponItem*);
    float getOrCalculateSpeed(ItemStackBase const&, Block const&, DiggerItem*);
    void onEvent(int, int, int, unsigned char);
};


class KEXToolsModule : public Module {
    public:
    static LastDestroyedBlock* lastDestroyedClient;
    static std::unordered_map<long long, LastDestroyedBlock*> lastDestroyed;
    static std::unordered_map<int, BlockDataInterface*> blockData;
    static std::unordered_map<int, int> toolsToBrokenIds;
    static std::unordered_set<int> customTools;
    static bool isCustomTool(int id);
    static const char* getBlockMaterialName(int id);
    static int getBlockDestroyLevel(int id);
    static bool getBlockIsNative(int id);
    static void setBlockMaterialName(int id, const char* materialName);
    static void setBlockDestroyLevel(int id, int destroyLevel);
    static void setBlockIsNative(int id, bool isNative);
    static Item::Tier* getItemTier(DiggerItem*);
    static bool patchedCanDestroySpecial(DiggerItem*, Block const&);
    static bool patchedHasBlock(DiggerItem*, Block const&);
    static unsigned char modifiedItemStackHurtAndBreak(ItemStackBase*, int);
    KEXToolsModule(Module* parent): Module(parent, "kex.tools") {};
    virtual void initialize();
};


#endif //KEX_MODULES_TOOLS_MODULE_HPP