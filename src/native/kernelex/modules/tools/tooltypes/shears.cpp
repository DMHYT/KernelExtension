#include <jni.h>

#include <innercore/id_conversion_map.h>

#include <static_symbol.hpp>

#include <items/ShearsItem.hpp>

#include "../module.hpp"
#include "shears.hpp"


void ShearsFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        IdPool* pool = ItemRegistry::getItemIdPool();
        id = pool->allocateId(nameId, id, IdPool::FLAG_ID_USED);
        if(id != INVALID_ID) {
            void* alloc = operator new(300);
            STATIC_SYMBOL(ShearsConstructor, "_ZN10ShearsItemC2ERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi", (ShearsItem*, stl_string const&, int));
            ShearsConstructor((ShearsItem*) alloc, to_stl(nameId), id);
            ItemRegistry::registerItem((Item*) alloc, new ShearsProvider(this));
        } else {
            Logger::error("InnerCore-ItemRegistry", "failed to register item for id '%s': cannot allocate id for some reason", nameId.data());
        }
    }
}


void ShearsProvider::setupVtable(void* table) {
    LegacyItemProviderBase::setupVtable(table);
    void** vtable = (void**) table;
    VTABLE_FIND_OFFSET(Item_hurtActor, _ZTV4Item, _ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob);
    VTABLE_FIND_OFFSET(Item_mineBlock__instance, _ZTV4Item, _ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor);
    VTABLE_FIND_OFFSET(Item_mineBlock__stack, _ZTV4Item, _ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor);
    VTABLE_FIND_OFFSET(Item_dispense, _ZTV4Item, _ZNK4Item8dispenseER11BlockSourceR9ContaineriRK4Vec3h);
    vtable[Item_hurtActor] = SYMBOL("mcpe", "_ZNK10ShearsItem9hurtActorER9ItemStackR5ActorR3Mob");
    vtable[Item_mineBlock__instance] = SYMBOL("mcpe", "_ZNK4Item9mineBlockER12ItemInstanceRK5BlockiiiP5Actor");
    vtable[Item_mineBlock__stack] = SYMBOL("mcpe", "_ZNK10ShearsItem9mineBlockER9ItemStackRK5BlockiiiP5Actor");
    vtable[Item_dispense] = SYMBOL("mcpe", "_ZNK10ShearsItem8dispenseER11BlockSourceR9ContaineriRK4Vec3h");
    if(factory->tier != nullptr) {
        VTABLE_FIND_OFFSET(ShearsItem_getDestroySpeed, _ZTV10ShearsItem, _ZNK10ShearsItem15getDestroySpeedERK13ItemStackBaseRK5Block);
        vtable[ShearsItem_getDestroySpeed] = ADDRESS(KEXToolsModule::CustomToolPatches::_shearsTieredGetDestroySpeed);
    }
}


extern "C" JNIEXPORT void JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeRegisterShears
(JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech, jint durabilityIfWithoutTier) {
    const char* cNameId = env->GetStringUTFChars(nameId, 0);
    const char* cName = env->GetStringUTFChars(name, 0);
    const char* cTextureName = env->GetStringUTFChars(textureName, 0);
    ShearsFactory* factory = new ShearsFactory();
    std::string itemNameId(cNameId);
    if(itemNameId.rfind("item_", 0) != 0) itemNameId = "item_" + itemNameId;
    factory->initParameters(id, itemNameId, std::string(cName), std::string(cTextureName), textureMeta);
    factory->props.stack = 1;
    if(tierPtr != 0) factory->tier = (Item::Tier*) tierPtr;
    else factory->props.durability = durabilityIfWithoutTier;
    LegacyItemRegistry::registerItemFactory(factory);
    if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
    env->ReleaseStringUTFChars(nameId, cNameId);
    env->ReleaseStringUTFChars(name, cName);
    env->ReleaseStringUTFChars(textureName, cTextureName);
}