#include <unordered_map>
#include <jni.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <innercore/id_conversion_map.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>
#include <Item.hpp>
#include "items.hpp"


void ItemParamsModifier::applyTo(int id) {
    Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
    VTABLE_FIND_OFFSET(Item_setRequiresWorldBuilder, _ZTV4Item, _ZN4Item23setRequiresWorldBuilderEb);
    VTABLE_CALL<void>(Item_setRequiresWorldBuilder, item, requiresWorldBuilder);
    VTABLE_FIND_OFFSET(Item_setExplodable, _ZTV4Item, _ZN4Item13setExplodableEb);
    VTABLE_CALL<void>(Item_setExplodable, item, explodable);
    VTABLE_FIND_OFFSET(Item_setFireResistant, _ZTV4Item, _ZN4Item16setFireResistantEb);
    VTABLE_CALL<void>(Item_setFireResistant, item, fireResistant);
    VTABLE_FIND_OFFSET(Item_setShouldDespawn, _ZTV4Item, _ZN4Item16setShouldDespawnEb);
    VTABLE_CALL<void>(Item_setShouldDespawn, item, shouldDespawn);
    if(mirroredArt) item->setIsMirroredArt(mirroredArt);
    if(furnaceBurnIntervalMultiplier > 0) item->setFurnaceBurnIntervalMultiplier(furnaceBurnIntervalMultiplier);
    if(furnaceXPMultiplier > 0) item->setFurnaceXPmultiplier(furnaceXPMultiplier);
    if(cannotBeRepairedInAnvil) {
        void** vtable = *(void***) item;
        VTABLE_FIND_OFFSET(Item_isValidRepairItem, _ZTV4Item, _ZNK5Item17isValidRepairItemERK13ItemStackBaseRK13ItemStackBase);
        vtable[Item_isValidRepairItem] = ADDRESS(_anvilRepairDisable);
    }
}


std::unordered_map<int, ItemParamsModifier*> KEXItemsModule::itemParamsModifiers;
ItemParamsModifier* KEXItemsModule::getOrCreateModifier(int id) {
    auto found = itemParamsModifiers.find(id);
    if(found != itemParamsModifiers.end()) {
        return found->second;
    } else {
        itemParamsModifiers.insert(std::unordered_map<int, ItemParamsModifier*>::value_type(id, new ItemParamsModifier()));
        return itemParamsModifiers.at(id);
    }
}

void KEXItemsModule::initialize() {
    Callbacks::addCallback("postModItemsInit", CALLBACK([], (), {
        for(std::unordered_map<int, ItemParamsModifier*>::iterator iter = itemParamsModifiers.begin(); iter != itemParamsModifiers.end(); iter++) {
            iter->second->applyTo(iter->first);
        }
    }));
}


extern "C" {
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setRequiresWorldBuilder
    (JNIEnv*, jclass, jint id, jboolean requiresWorldBuilder) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->requiresWorldBuilder = requiresWorldBuilder;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setExplodable
    (JNIEnv*, jclass, jint id, jboolean explodable) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->explodable = explodable;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setFireResistant
    (JNIEnv*, jclass, jint id, jboolean fireResistant) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->fireResistant = fireResistant;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setShouldDespawn
    (JNIEnv*, jclass, jint id, jboolean shouldDespawn) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->shouldDespawn = shouldDespawn;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setIsMirroredArt
    (JNIEnv*, jclass, jint id, jboolean mirroredArt) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->mirroredArt = mirroredArt;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setFurnaceBurnIntervalMultiplier
    (JNIEnv*, jclass, jint id, jfloat multiplier) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->furnaceBurnIntervalMultiplier = multiplier;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setFurnaceXPMultiplier
    (JNIEnv*, jclass, jint id, jfloat multiplier) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->furnaceXPMultiplier = multiplier;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_setCannotBeRepairedInAnvil
    (JNIEnv*, jclass, jint id) {
        ItemParamsModifier* mod = KEXItemsModule::getOrCreateModifier(id);
        mod->cannotBeRepairedInAnvil = true;
    }
}