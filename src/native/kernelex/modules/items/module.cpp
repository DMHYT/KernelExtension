#include <hook.h>
#include <innercore_callbacks.h>
#include <symbol.h>

#include <innercore/item_registry.h>
#include <innercore/vtable.h>

#include <ItemStackBase.hpp>
#include <ItemStack.hpp>

#include "module.hpp"
#include "submodules/food.hpp"


std::unordered_map<int, KEXItemsModule::ItemParamsModifier*> KEXItemsModule::modifiers;


void KEXItemsModule::ItemParamsModifier::applyTo(int id) {
    Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
    if(item == nullptr) return;
    item->setRequiresWorldBuilder(requiresWorldBuilder);
    item->setExplodable(explodable);
    item->setFireResistant(fireResistant);
    item->setShouldDespawn(shouldDespawn);
    item->setIsMirroredArt(mirroredArt);
    if(furnaceBurnIntervalMultiplier > 0.0f) item->setFurnaceBurnIntervalMultiplier(furnaceBurnIntervalMultiplier);
    if(furnaceXPMultiplier > 0) item->setFurnaceXPmultiplier(furnaceXPMultiplier);
    void** vtable = *(void***) item;
    if(cannotBeRepairedInAnvil) {
        VTABLE_FIND_OFFSET(Item_isValidRepairItem, _ZTV4Item, _ZNK5Item17isValidRepairItemERK13ItemStackBaseRK13ItemStackBase);
        vtable[Item_isValidRepairItem] = ADDRESS(KEXItemsModule::_anvilRepairDisable);
    }
    if(cooldownTime > 0) {
        VTABLE_FIND_OFFSET(Item_getCooldownTime, _ZTV4Item, _ZNK4Item15getCooldownTimeEv);
        vtable[Item_getCooldownTime] = ADDRESS(KEXItemsModule::_getCooldownTimePatch);
    }
    if(dynamicUseDuration) {
        VTABLE_FIND_OFFSET(Item_getMaxUseDuration__instance, _ZTV4Item, _ZNK4Item17getMaxUseDurationEPK12ItemInstance);
        VTABLE_FIND_OFFSET(Item_getMaxUseDuration__stack, _ZTV4Item, _ZNK4Item17getMaxUseDurationEPK9ItemStack);
        vtable[Item_getMaxUseDuration__instance] = ADDRESS(KEXItemsModule::_getMaxUseDurationPatch);
        vtable[Item_getMaxUseDuration__stack] = ADDRESS(KEXItemsModule::_getMaxUseDurationPatch);
    }
}


void KEXItemsModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN6Player14startUsingItemERK9ItemStacki"),
        LAMBDA((HookManager::CallbackController* controller, Player* player, const ItemStack& stack, int time), {
            Item* item = stack.getItem();
            if(item != nullptr) {
                auto mod = getModifierOrNull(IdConversion::dynamicToStatic(item->id, IdConversion::ITEM));
                if(mod != nullptr && mod->dynamicUseDuration) {
                    return controller->callAndReplace<void*>(player, stack, _getMaxUseDurationPatch(item, &stack));
                }
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    Callbacks::addCallback("postModItemsInit",
        CALLBACK([], (), {
            for(auto iter = modifiers.begin(); iter != modifiers.end(); iter++) {
                iter->second->applyTo(iter->first);
            }
        })
    );

}


// HookManager::addCallback(SYMBOL("mcpe", "_ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb"), LAMBDA((Item* item, const ItemStackBase& stack, Level& level, stl::string& text, bool b), {
//     JNIEnv* env = KEXJavaUtils::attach();
//     jstring jText = KEXJavaBridge::ItemsModule::appendFormattedHovertext((jlong) &stack, (jlong) &level, text.c_str());
//     const char* cText = env->GetStringUTFChars(jText, 0);
//     text = cText;
//     env->ReleaseStringUTFChars(jText, cText);
//     env->DeleteLocalRef(jText);
// }, ), HookManager::RETURN | HookManager::LISTENER);