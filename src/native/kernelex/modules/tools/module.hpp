#include <string>
#include <unordered_map>
#include <unordered_set>

#include <mod.h>

#include <innercore/legacy_item_registry.h>

#include <commontypes.hpp>

#include <Block.hpp>
#include <items/DiggerItem.hpp>
#include <items/ShearsItem.hpp>
#include <items/WeaponItem.hpp>
#include <ItemStackBase.hpp>

#ifndef KEX_MODULES_TOOLS_MODULE_HPP
#define KEX_MODULES_TOOLS_MODULE_HPP


class KEXToolsModule : public Module {
    public:
    class SimpleTests {
        public:
        static std::unordered_set<int> allVanillaTools;
        static std::unordered_map<std::string, std::unordered_set<int>> vanillaToolsMap;
        static bool isTool(int id);
        static bool isTool(LegacyItemRegistry::LegacyItemFactoryBase* factory);
        static bool isSword(int id);
        static bool isAxe(int id);
        static bool isPickaxe(int id);
        static bool isShovel(int id);
        static bool isHoe(int id);
        inline static bool isCustomTool(int id) {
            return KEXToolsModule::ToolAPI::isCustomTool(id);
        }
        static bool isShears(int id);
        static bool isFlintAndSteel(int id);
    };
    class BlockDataInterface {
        public:
        std::string materialName = "";
        int destroyLevel = 0;
        bool isNative = false;
    };
    class LastDestroyedBlock {
        public:
        float destroySpeed = 1.0f;
        int calculatedForX = 0;
        int calculatedForY = 0;
        int calculatedForZ = 0;
        unsigned char calculatedForSide = 0;
        short calculatedForId = 0;
        int calculatedForData = 0;
        LastDestroyedBlock() {};
        float getOrCalculateSpeed(const ItemStackBase&, const Block&, WeaponItem*, const BlockPos& pos, unsigned char side);
        float getOrCalculateSpeed(const ItemStackBase&, const Block&, DiggerItem*, const BlockPos& pos, unsigned char side);
    };
    class Data {
        public:
        static LastDestroyedBlock* lastDestroyedBlock;
        static std::unordered_map<int, BlockDataInterface*> blockData;
        static std::unordered_map<int, int> toolsToBrokenIds;
        static std::unordered_set<int> customTools;
    };
    class ToolAPI {
        public:
        static inline bool isCustomTool(int id) {
            return KEXToolsModule::Data::customTools.find(id) != KEXToolsModule::Data::customTools.end();
        }
        static std::string getBlockMaterialName(int id);
        static int getBlockDestroyLevel(int id);
        static bool getBlockIsNative(int id);
        static void setBlockMaterialName(int id, const char* materialName);
        static void setBlockDestroyLevel(int id, int destroyLevel);
        static void setBlockIsNative(int id, bool isNative);
        static Item::Tier* getItemTier(DiggerItem*);
        static bool itemHasMaterial(int id, const std::string& materialName);
    };
    class CustomToolPatches {
        public:
        static float diggerGetDestroySpeed(DiggerItem* _this, const ItemStackBase& stack, const Block& block);
        static float weaponGetDestroySpeed(WeaponItem* _this, const ItemStackBase& stack, const Block& block);
        static inline bool hurtActor(Item*, ItemStack&, Actor&, Mob&) { return true; }
        static inline bool mineBlock__instance(Item*, ItemInstance&, const Block&, int, int, int, Actor*) { return true; }
        static inline bool mineBlock__stack(Item*, ItemStack&, const Block&, int, int, int, Actor*) { return true; }
        static void appendFormattedHovertext(Item*, const ItemStackBase&, Level&, stl::string&, bool);
        static float _shearsTieredGetDestroySpeed(ShearsItem*, const ItemStackBase&, const Block&);
    };
    KEXToolsModule(Module* parent): Module(parent, "kex.tools") {};
    virtual void initialize();
};


#endif //KEX_MODULES_TOOLS_MODULE_HPP