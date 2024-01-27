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


int ItemStackBase::getAttackDamageKEX(Actor* actor, Actor* victim) const {
    Item* item = this->getItem();
    if(item == nullptr) return 0;
    int id = IdConversion::dynamicToStatic(item->id, IdConversion::ITEM);
    if(KEXToolsModule::SimpleTests::isCustomTool(id)) {
        CustomToolFactory* factory = (CustomToolFactory*) LegacyItemRegistry::findFactoryById(id);
        if(factory != nullptr && factory->dynamicDamageEnabled) {
            ItemInstanceExtra* extra = new ItemInstanceExtra((ItemStack*) this);
            return factory->baseAttackDamage + KEXJavaBridge::CustomToolEvents::getAttackDamageBonus(id, 1, this->getDamageValue(), (jlong) extra, factory->tier->getAttackDamageBonus(), (jlong) actor->getUniqueID()->id, (jlong) victim->getUniqueID()->id);
        }
    }
    VTABLE_FIND_OFFSET(Item_getAttackDamage, _ZTV4Item, _ZNK4Item15getAttackDamageEv);
    return VTABLE_CALL<int>(Item_getAttackDamage, item);
}


void KEXToolsModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK13ItemStackBase15getAttackDamageEv"),
        LAMBDA((HookManager::CallbackController* controller, ItemStackBase* stack), {
            controller->replace();
            return stack->getAttackDamageKEX(nullptr, nullptr);
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );
    
}