#include <hook.h>
#include <symbol.h>

#include <innercore/id_conversion_map.h>

#include <ActorUniqueID.hpp>
#include <GameMode.hpp>
#include <Level.hpp>
#include <Player.hpp>

#include "../../utils/java_utils.hpp"
#include "tooltypes/custom.hpp"
#include "module.hpp"


void KEXToolsModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    HookManager::addCallback(SYMBOL("mcpe", "_ZN8GameMode17startDestroyBlockERK8BlockPoshRb"), LAMBDA((GameMode* mode, const BlockPos& pos, unsigned char side, bool& someBoolRef), {
        if(!mode->player->getLevel()->isClientSide()) {
            long long player = mode->player->getUniqueID()->id;
            auto found = KEXToolsModule::Data::last.find(player);
            if(found == KEXToolsModule::Data::last.end()) {
                KEXToolsModule::Data::last.emplace(player, new KEXToolsModule::LastDestroyedBlock());
                found = KEXToolsModule::Data::last.find(player);
            }
            found->second->onEvent(pos.x, pos.y, pos.z, side);
        } else {
            KEXToolsModule::Data::lastClient->onEvent(pos.x, pos.y, pos.z, side);
        }
    }, ), HookManager::CALL | HookManager::LISTENER);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN8GameMode12destroyBlockERK8BlockPosh"), LAMBDA((GameMode* mode, const BlockPos& pos, unsigned char side), {
        if(!mode->player->getLevel()->isClientSide()) {
            long long player = mode->player->getUniqueID()->id;
            auto found = KEXToolsModule::Data::last.find(player);
            if(found == KEXToolsModule::Data::last.end()) {
                KEXToolsModule::Data::last.emplace(player, new KEXToolsModule::LastDestroyedBlock());
                found = KEXToolsModule::Data::last.find(player);
            }
            found->second->onEvent(pos.x, pos.y, pos.z, side);
        } else {
            KEXToolsModule::Data::lastClient->onEvent(pos.x, pos.y, pos.z, side);
        }
    }, ), HookManager::CALL | HookManager::LISTENER);
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK13ItemStackBase15getAttackDamageEv"), LAMBDA((HookManager::CallbackController* controller, ItemStackBase* stack), {
        Item* item = stack->getItem();
        if(item != nullptr) {
            int id = IdConversion::dynamicToStatic(item->id, IdConversion::ITEM);
            if(KEXToolsModule::SimpleTests::isCustomTool(id)) {
                CustomToolFactory* factory = (CustomToolFactory*) LegacyItemRegistry::findFactoryById(id);
                if(factory != nullptr && factory->dynamicDamageEnabled) {
                    controller->replace();
                    ItemInstanceExtra* extra = new ItemInstanceExtra((ItemStack*) stack);
                    int result = factory->baseAttackDamage + KEXJavaBridge::CustomToolEvents::getAttackDamageBonus(id, 1, stack->getDamageValue(), (jlong) extra, factory->tier->getAttackDamageBonus());
                    delete extra;
                    return result;
                }
            }
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
}