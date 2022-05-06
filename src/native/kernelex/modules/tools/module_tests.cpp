#include "classes.hpp"
#include "module.hpp"


#define FACTORY(ID) LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(ID);
#define FACTORY_CHECKER(NAME, TYPE) \
    bool KEXToolsModule::SimpleTests::NAME(int id) { \
        FACTORY(id) if(!isTool(factory)) return false; \
        return ((ToolFactory*) factory)->getToolType() == ToolFactory::TYPE; \
    }


bool KEXToolsModule::SimpleTests::isTool(int id) {
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