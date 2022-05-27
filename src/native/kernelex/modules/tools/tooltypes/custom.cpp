#include <jni.h>

#include <innercore/id_conversion_map.h>

#include <items/DiggerItem.hpp>
#include <items/WeaponItem.hpp>

#include "custom.hpp"
#include "../module.hpp"
#include "../submodules/method_patches.hpp"


void CustomToolFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        if(isWeapon) {
            WeaponItem* registeredItem = ItemRegistry::registerItemFixed<WeaponItem>(new CustomToolProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier);
            registeredItem->attackDamage = baseAttackDamage + tier->getAttackDamageBonus();
        } else {
            std::__ndk1::vector<Block const*> blocks;
            ItemRegistry::registerItemFixed<DiggerItem>(new CustomToolProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, baseAttackDamage, *tier, blocks);
        }
    }
}


void CustomToolProvider::setupVtable(void* table) {
    LegacyItemProviderBase::setupVtable(table);
    void** vtable = (void**) table;
    VTABLE_FIND_OFFSET(Item_hurtActor, _ZTV4Item, _ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob);
    VTABLE_FIND_OFFSET(Item_mineBlock__instance, _ZTV4Item, _ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor);
    VTABLE_FIND_OFFSET(Item_mineBlock__stack, _ZTV4Item, _ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor);
    vtable[Item_hurtActor] = ADDRESS(KEXToolsModule::CustomToolPatches::hurtActor);
    vtable[Item_mineBlock__instance] = ADDRESS(KEXToolsModule::CustomToolPatches::mineBlock__instance);
    vtable[Item_mineBlock__stack] = ADDRESS(KEXToolsModule::CustomToolPatches::mineBlock__stack);
    if(factory->isWeapon) {
        VTABLE_FIND_OFFSET(WeaponItem_getDestroySpeed, _ZTV10WeaponItem, _ZNK10WeaponItem15getDestroySpeedERK13ItemStackBaseRK5Block);
        vtable[WeaponItem_getDestroySpeed] = ADDRESS(KEXToolsModule::CustomToolPatches::weaponGetDestroySpeed);
    } else {
        VTABLE_FIND_OFFSET(DiggerItem_getDestroySpeed, _ZTV10DiggerItem, _ZNK10DiggerItem15getDestroySpeedERK13ItemStackBaseRK5Block);
        VTABLE_FIND_OFFSET(Item_canDestroySpecial, _ZTV4Item, _ZNK4Item17canDestroySpecialERK5Block);
        vtable[DiggerItem_getDestroySpeed] = ADDRESS(KEXToolsModule::CustomToolPatches::diggerGetDestroySpeed);
        vtable[Item_canDestroySpecial] = ADDRESS(KEXToolPatchesModule::canDestroySpecial);
    }
    if(factory->dynamicDamageEnabled) {
        VTABLE_FIND_OFFSET(Item_appendFormattedHovertext, _ZTV4Item, _ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb);
        vtable[Item_appendFormattedHovertext] = ADDRESS(KEXToolsModule::CustomToolPatches::appendFormattedHovertext);
    }
}


extern "C" JNIEXPORT void JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeRegisterCustomTool
(JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech, jboolean isWeapon, jobjectArray blockMaterials, jint brokenId, jint baseAttackDamage, jint enchantType) {
    const char* cNameId = env->GetStringUTFChars(nameId, 0);
    const char* cName = env->GetStringUTFChars(name, 0);
    const char* cTextureName = env->GetStringUTFChars(textureName, 0);
    CustomToolFactory* factory = new CustomToolFactory();
    factory->isWeapon = isWeapon;
    factory->baseAttackDamage = baseAttackDamage;
    std::string itemNameId(cNameId);
    if(itemNameId.rfind("item_", 0) != 0) itemNameId = "item_" + itemNameId;
    factory->initParameters(id, itemNameId, std::string(cName), std::string(cTextureName), textureMeta);
    factory->props.stack = 1;
    factory->enchantType = enchantType;
    factory->tier = (Item::Tier*) tierPtr;
    if(brokenId != 0) KEXToolsModule::Data::toolsToBrokenIds.emplace(id, brokenId);
    if(blockMaterials != NULL && !isWeapon) {
        std::set<std::string> materials;
        jsize l = env->GetArrayLength(blockMaterials);
        if(l > 0) {
            for(int i = 0; i < l; ++i) {
                jobject el = env->GetObjectArrayElement(blockMaterials, i);
                if(el != NULL) {
                    jstring sEl = (jstring) el;
                    const char* cEl = env->GetStringUTFChars(sEl, 0);
                    if(materials.find(cEl) == materials.end()) {
                        materials.emplace(std::string(cEl));
                    }
                    env->ReleaseStringUTFChars(sEl, cEl);
                }
            }
            factory->blockMaterials = materials;
        }
    }
    LegacyItemRegistry::registerItemFactory(factory);
    // if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
    env->ReleaseStringUTFChars(nameId, cNameId);
    env->ReleaseStringUTFChars(name, cName);
    env->ReleaseStringUTFChars(textureName, cTextureName);
    KEXToolsModule::Data::customTools.emplace(id);
}