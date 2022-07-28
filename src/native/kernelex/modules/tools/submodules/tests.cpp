#include "../tooltypes/base.hpp"
#include "../module.hpp"


std::unordered_set<int> KEXToolsModule::SimpleTests::allVanillaTools {
    268, 271, 270, 269, 290, 272, 275, 274, 273, 291, 267, 258, 257, 257, 292, 276, 279, 278, 277, 293, 283, 286, 285, 284, 294, 727, 835, 804, 726, 880, 359, 259
};
std::unordered_map<std::string, std::unordered_set<int>> KEXToolsModule::SimpleTests::vanillaToolsMap {
    { "SWORD", { 268, 272, 267, 276, 283, 727 } },
    { "AXE", { 271, 275, 258, 279, 286, 835 } },
    { "PICKAXE", { 270, 274, 257, 278, 285, 804 } },
    { "SHOVEL", { 269, 273, 256, 277, 284, 726 } },
    { "HOE", { 290, 291, 292, 293, 294, 880 } },
    { "SHEARS", { 359 } },
    { "FLINT_AND_STEEL", { 259 } }
};


#define FACTORY(ID) auto factory = LegacyItemRegistry::findFactoryById(ID);
#define FACTORY_CHECKER(NAME, TYPE) \
    bool KEXToolsModule::SimpleTests::NAME(int id) { \
        if(vanillaToolsMap[#TYPE].find(id) != vanillaToolsMap[#TYPE].end()) return true; \
        FACTORY(id) if(!isTool(factory)) return false; \
        return ((ToolFactory*) factory)->getToolType() == ToolFactory::TYPE; \
    }


bool KEXToolsModule::SimpleTests::isTool(int id) {
    if(allVanillaTools.find(id) != allVanillaTools.end()) return true;
    FACTORY(id) return isTool(factory);
}

bool KEXToolsModule::SimpleTests::isTool(LegacyItemRegistry::LegacyItemFactoryBase* factory) {
    if(factory == nullptr) return false;
    return factory->getType() == ToolFactory::_factoryTypeId;
}

FACTORY_CHECKER(isSword, SWORD)
FACTORY_CHECKER(isAxe, AXE)
FACTORY_CHECKER(isPickaxe, PICKAXE)
FACTORY_CHECKER(isShovel, SHOVEL)
FACTORY_CHECKER(isHoe, HOE)
FACTORY_CHECKER(isShears, SHEARS)
FACTORY_CHECKER(isFlintAndSteel, FLINT_AND_STEEL)


#undef FACTORY
#undef FACTORY_CHECKER