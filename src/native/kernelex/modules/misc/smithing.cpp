#include <hook.h>
#include <jni.h>
#include <symbol.h>
#include <static_symbol.h>

#include <innercore/id_conversion_map.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>

#include <CompoundTag.hpp>
#include <ItemStackBase.hpp>

#include "smithing.hpp"


std::unordered_map<int, std::unordered_map<int, int>> KEXMiscSmithingModule::recipes;


void KEXMiscSmithingModule::replaceRecipeResult(ItemInstance* result, void* containerManagerController) {
    STATIC_SYMBOL(ContainerManagerController__getItem0, "_ZNK26ContainerManagerController9_getItem0E17ContainerEnumName", (void*, int), ItemInstance*);
    STATIC_SYMBOL(ItemInstance_emptyConstructor, "_ZN12ItemInstanceC2Ev", (ItemInstance*), void);
    bool success = false;
    ItemInstance* baseItem = ContainerManagerController__getItem0(containerManagerController, 3);
    ItemInstance* additionItem = ContainerManagerController__getItem0(containerManagerController, 4);
    if(baseItem && additionItem) {
        int baseID = IdConversion::dynamicToStatic(baseItem->getId(), IdConversion::ITEM);
        auto found = recipes.find(baseID);
        if(found != recipes.end()) {
            int additionID = IdConversion::dynamicToStatic(additionItem->getId(), IdConversion::ITEM);
            auto additionToResult = found->second;
            auto foundResult = additionToResult.find(additionID);
            if(foundResult != additionToResult.end()) {
                int resultID = IdConversion::staticToDynamic(foundResult->second, IdConversion::ITEM);
                Item* resultItem = ItemRegistry::getItemById(resultID);
                int resultCount = baseItem->getCount() > additionItem->getCount() ? additionItem->getCount() : baseItem->getCount();
                new (result) ItemInstance(*resultItem, resultCount, 0);
                if(baseItem->hasUserData()) {
                    result->setUserData(baseItem->getUserData()->clone());
                }
                success = true;
            }
        }
    }
    if(!success) ItemInstance_emptyConstructor(result);
}


bool KEXMiscSmithingModule::consumeInputs(ContainerManagerController* controller) {
    STATIC_SYMBOL(ContainerManagerController__getItem0, "_ZNK26ContainerManagerController9_getItem0E17ContainerEnumName", (void*, int), ItemInstance*);
    ItemInstance* baseItem = ContainerManagerController__getItem0(controller, 3);
    ItemInstance* additionItem = ContainerManagerController__getItem0(controller, 4);
    int consumeAmount = baseItem && additionItem ? baseItem->getCount() > additionItem->getCount() ? additionItem->getCount() : baseItem->getCount() : 0;
    SlotData slotData("smithing_table_input_items", 0);
    VTABLE_FIND_OFFSET(ContainerManagerController_handleConsume, _ZTV26ContainerManagerController, _ZN26ContainerManagerController13handleConsumeERK8SlotData18ItemTransferAmount);
    VTABLE_CALL<void>(ContainerManagerController_handleConsume, controller, &slotData, ItemTransferAmount(consumeAmount));
    return !controller->_getItem(slotData, true);
}


void KEXMiscSmithingModule::consumeMaterials(ContainerManagerController* controller) {
    STATIC_SYMBOL(ContainerManagerController__getItem0, "_ZNK26ContainerManagerController9_getItem0E17ContainerEnumName", (void*, int), ItemInstance*);
    ItemInstance* baseItem = ContainerManagerController__getItem0(controller, 3);
    ItemInstance* additionItem = ContainerManagerController__getItem0(controller, 4);
    int consumeAmount = baseItem && additionItem ? baseItem->getCount() > additionItem->getCount() ? additionItem->getCount() : baseItem->getCount() : 0;
    SlotData slotData("smithing_table_material_items", 0);
    if(!controller->_getItem(slotData, true)->isNull()) {
        VTABLE_FIND_OFFSET(ContainerManagerController_handleConsume, _ZTV26ContainerManagerController, _ZN26ContainerManagerController13handleConsumeERK8SlotData18ItemTransferAmount);
        VTABLE_CALL<void>(ContainerManagerController_handleConsume, controller, &slotData, ItemTransferAmount(consumeAmount));
    }
}


void KEXMiscSmithingModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN39SmithingTableContainerManagerController10_getResultEv"),
        LAMBDA((HookManager::CallbackController* controller, ItemInstance* result, void* containerManagerController), {
            controller->prevent();
            replaceRecipeResult(result, containerManagerController);
        }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN39SmithingTableContainerManagerController37_consumeOneFromSmithingTableInputSlotEv"),
        LAMBDA((HookManager::CallbackController* controller, ContainerManagerController* containerManagerController), {
            controller->replace();
            return consumeInputs(containerManagerController);
        }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );
    
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN39SmithingTableContainerManagerController17_consumeMaterialsEv"),
        LAMBDA((HookManager::CallbackController* controller, ContainerManagerController* containerManagerController), {
            controller->prevent();
            consumeMaterials(containerManagerController);
        }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER
    );

}


extern "C" {
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_misc_SmithingTableRecipes_nativeAddRecipe
    (JNIEnv*, jclass, jint baseID, jint additionID, jint resultID) {
        if(KEXMiscSmithingModule::recipes.find(baseID) == KEXMiscSmithingModule::recipes.end()) {
            KEXMiscSmithingModule::recipes.emplace(baseID, std::unordered_map<int, int> {});
        }
        auto& additionsMap = KEXMiscSmithingModule::recipes.at(baseID);
        if(additionsMap.find(additionID) == additionsMap.end()) {
            additionsMap.emplace(additionID, resultID);
        } else {
            Logger::debug("KEX-WARNING", "Smithing table recipe with baseID=%d, additionID=%d, was already registered before, skipping...", baseID, additionID);
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_misc_SmithingTableRecipes_nativeRemoveRecipe
    (JNIEnv*, jclass, jint baseID, jint additionID) {
        if(KEXMiscSmithingModule::recipes.find(baseID) == KEXMiscSmithingModule::recipes.end()) {
            Logger::debug("KEX-WARNING", "Smithing table recipe with baseID=%d is not present, nothing to remove, skipping...", baseID);
        }
        auto& additionsMap = KEXMiscSmithingModule::recipes.at(baseID);
        if(additionsMap.find(additionID) == additionsMap.end()) {
            Logger::debug("KEX-WARNING", "Smithing table recipe with baseID=%d, additionID=%d, is not present, nothing to remove, skipping...", baseID, additionID);
        }
        additionsMap.erase(additionID);
    }
}