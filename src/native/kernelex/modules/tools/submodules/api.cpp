#include <innercore/block_registry.h>
#include <innercore/id_conversion_map.h>

#include "../submodules/method_patches.hpp"
#include "../tooltypes/base.hpp"
#include "../module.hpp"


std::string KEXToolsModule::ToolAPI::getBlockMaterialName(int id) {
    auto found = KEXToolsModule::Data::blockData.find(id);
    if(found != KEXToolsModule::Data::blockData.end()) {
        return found->second->materialName;
    } else {
        KEXToolsModule::Data::blockData.emplace(id, new KEXToolsModule::BlockDataInterface());
    }
    return "";
}


int KEXToolsModule::ToolAPI::getBlockDestroyLevel(int id) {
    auto found = KEXToolsModule::Data::blockData.find(id);
    if(found != KEXToolsModule::Data::blockData.end()) {
        return found->second->destroyLevel;
    } else {
        KEXToolsModule::Data::blockData.emplace(id, new KEXToolsModule::BlockDataInterface());
        return 0;
    }
}


bool KEXToolsModule::ToolAPI::getBlockIsNative(int id) {
    auto found = KEXToolsModule::Data::blockData.find(id);
    if(found != KEXToolsModule::Data::blockData.end()) {
        return found->second->isNative;
    } else {
        KEXToolsModule::Data::blockData.emplace(id, new KEXToolsModule::BlockDataInterface());
        return false;
    }
}


void KEXToolsModule::ToolAPI::setBlockMaterialName(int id, const char* materialName) {
    auto found = KEXToolsModule::Data::blockData.find(id);
    if(found != KEXToolsModule::Data::blockData.end()) {
        found->second->materialName = materialName;
    } else {
        auto iface = new KEXToolsModule::BlockDataInterface();
        iface->materialName = materialName;
        KEXToolsModule::Data::blockData.emplace(id, iface);
    }
}


void KEXToolsModule::ToolAPI::setBlockDestroyLevel(int id, int destroyLevel) {
    auto found = KEXToolsModule::Data::blockData.find(id);
    if(found != KEXToolsModule::Data::blockData.end()) {
        found->second->destroyLevel = destroyLevel;
    } else {
        auto iface = new KEXToolsModule::BlockDataInterface();
        iface->destroyLevel = destroyLevel;
        KEXToolsModule::Data::blockData.emplace(id, iface);
    }
}


void KEXToolsModule::ToolAPI::setBlockIsNative(int id, bool isNative) {
    auto found = KEXToolsModule::Data::blockData.find(id);
    if(found != KEXToolsModule::Data::blockData.end()) {
        found->second->isNative = isNative;
    } else {
        auto iface = new KEXToolsModule::BlockDataInterface();
        iface->isNative = isNative;
        KEXToolsModule::Data::blockData.emplace(id, iface);
    }
}


Item::Tier* KEXToolsModule::ToolAPI::getItemTier(DiggerItem* item) {
    int staticId = IdConversion::dynamicToStatic(item->id, IdConversion::ITEM);
    if(staticId < 900) {
        return item->tier;
    } else {
        auto factory = LegacyItemRegistry::findFactoryById(staticId);
        if(factory == nullptr) return nullptr;
        if(factory->getType() == ToolFactory::_factoryTypeId) {
            return ((ToolFactory*) factory)->tier;
        }
        return nullptr;
    }
}


bool KEXToolsModule::ToolAPI::itemHasMaterial(int itemID, const std::string& materialName) {
    static HashedString diggerTag("minecraft:digger");
    static HashedString weaponTag("minecraft:weapon");
    auto item = ItemRegistry::getItemById(IdConversion::staticToDynamic(itemID, IdConversion::ITEM));
    if(item == nullptr) return false;
    if(item->hasTag(weaponTag)) return materialName == "plant" || materialName == "fibre";
    if(item->hasTag(diggerTag)) return KEXToolPatchesModule::hasBlockMaterial((DiggerItem*) item, materialName);
    return false;
}