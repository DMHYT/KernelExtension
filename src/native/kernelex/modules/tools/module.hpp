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
        inline void onEvent(int xIn, int yIn, int zIn, unsigned char sideIn) {
            x = xIn, y = yIn, z = zIn, side = sideIn;
        }
    };
    class Data {
        public:
        static LastDestroyedBlock* lastClient;
        static std::unordered_map<long long, LastDestroyedBlock*> last;
        static std::unordered_map<int, BlockDataInterface*> blockData;
        static std::unordered_map<int, int> toolsToBrokenIds;
        static std::unordered_set<int> customTools;
    };
    class ToolAPI {
        public:
        static inline bool isCustomTool(int id) {
            return KEXToolsModule::Data::customTools.find(id) != KEXToolsModule::Data::customTools.end();
        }
        static const char* getBlockMaterialName(int id);
        static int getBlockDestroyLevel(int id);
        static bool getBlockIsNative(int id);
        static void setBlockMaterialName(int id, const char* materialName);
        static void setBlockDestroyLevel(int id, int destroyLevel);
        static void setBlockIsNative(int id, bool isNative);
        static Item::Tier* getItemTier(DiggerItem*);
    };
    class CustomToolPatches {
        public:
        static inline float diggerGetDestroySpeed(DiggerItem* _this, ItemStackBase const& stack, Block const& block) {
            return KEXToolsModule::Data::lastClient->getOrCalculateSpeed(stack, block, _this);
        }
        static inline float weaponGetDestroySpeed(WeaponItem* _this, ItemStackBase const& stack, Block const& block) {
            return KEXToolsModule::Data::lastClient->getOrCalculateSpeed(stack, block, _this);
        }
        static inline bool hurtActor(Item*, ItemStack&, Actor&, Mob&) { return true; }
        static inline bool mineBlock__instance(Item*, ItemInstance&, Block const&, int, int, int, Actor*) { return true; }
        static inline bool mineBlock__stack(Item*, ItemStack&, Block const&, int, int, int, Actor*) { return true; }
        static void appendFormattedHovertext(Item*, ItemStackBase const&, Level&, std::__ndk1::string&, bool);
        static float _shearsTieredGetDestroySpeed(ShearsItem*, ItemStackBase const&, Block const&);
    };
    KEXToolsModule(Module* parent): Module(parent, "kex.tools") {};
    virtual void initialize();
};


#endif //KEX_MODULES_TOOLS_MODULE_HPP