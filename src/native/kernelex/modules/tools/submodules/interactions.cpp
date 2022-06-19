#include <hook.h>
#include <symbol.h>

#include <innercore/id_conversion_map.h>
#include <innercore/vtable.h>

#include <ActorTests.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>

#include "../module.hpp"
#include "interactions.hpp"


void KEXToolInteractionsModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    
    #define HAS_EQUIPMENT_REPLACER(ID, PREDICATE) \
        VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv); \
        ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, ctx.actor); \
        if(stack != nullptr) { \
            int dynamicStackId = stack->getId(); \
            int stackId = IdConversion::dynamicToStatic(dynamicStackId, IdConversion::ITEM); \
            if(stackId != ID && KEXToolsModule::SimpleTests::PREDICATE(stackId)) { \
                test->id = dynamicStackId; \
                bool result = controller->callAndReplace<bool>(test, &ctx); \
                test->id = testId; \
                return result; \
            } \
        }

    #define IS_INSTANCE_REPLACER(ID, PREDICATE) \
        int id = IdConversion::dynamicToStatic(stack->getId(), IdConversion::ITEM); \
        if(id != ID && KEXToolsModule::SimpleTests::PREDICATE(id)) { \
            controller->replace(); \
            return true; \
        }

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK21ActorHasEquipmentTest8evaluateERK13FilterContext"),
        LAMBDA((HookManager::CallbackController* controller, ActorHasEquipmentTest* test, const FilterContext& ctx), {
            int dynamicTestId = test->id;
            int testId = IdConversion::dynamicToStatic(dynamicTestId, IdConversion::ITEM);
            if(testId == 359) { // for custom shears to shear sheep, snowmen, mooshrooms etc.
                HAS_EQUIPMENT_REPLACER(359, isShears)
            } else if(testId == 259) { // for custom flint&steel's to lit creepers
                HAS_EQUIPMENT_REPLACER(259, isFlintAndSteel)
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK13ItemStackBase10isInstanceERK12HashedStringb"),
        LAMBDA((HookManager::CallbackController* controller, ItemStackBase* stack, const HashedString& str), {
            const auto& cppstr = str.getString();
            if(cppstr == "shears") { // for custom shears to carve pumpkins, gather honey from beehives etc.
                IS_INSTANCE_REPLACER(359, isShears)
            } else if(cppstr == "flint_and_steel") { // for custom flint&steel's to lit campfires
                IS_INSTANCE_REPLACER(259, isFlintAndSteel)
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    #undef HAS_EQUIPMENT_REPLACER
    #undef IS_INSTANCE_REPLACER

    // for custom shovels to douse campfires on click
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK13CampfireBlock13canUseToDouseER9ItemStack"),
        LAMBDA((HookManager::CallbackController* controller, void* campfire, ItemStack& stack), {
            int id = IdConversion::dynamicToStatic(stack.getId(), IdConversion::ITEM);
            if(KEXToolsModule::SimpleTests::isShovel(id)) {
                controller->replace();
                return true;
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

}