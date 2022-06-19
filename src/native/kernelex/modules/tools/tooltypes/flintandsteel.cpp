#include <jni.h>

#include <innercore/id_conversion_map.h>

#include <items/FlintAndSteelItem.hpp>

#include "flintandsteel.hpp"


void FlintAndSteelFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        ItemRegistry::registerItemFixed<FlintAndSteelItem>(new FlintAndSteelProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId);
    }
}


void FlintAndSteelProvider::setupVtable(void* table) {
    LegacyItemProviderBase::setupVtable(table);
    void** vtable = (void**) table;
    VTABLE_FIND_OFFSET(Item_dispense, _ZTV4Item, _ZNK4Item8dispenseER11BlockSourceR9ContaineriRK4Vec3h);
    vtable[Item_dispense] = SYMBOL("mcpe", "_ZNK17FlintAndSteelItem8dispenseER11BlockSourceR9ContaineriRK4Vec3h");
}


extern "C" JNIEXPORT void JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeRegisterFlintAndSteel
(JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jboolean isTech, jint durability) {
    const char* cNameId = env->GetStringUTFChars(nameId, 0);
    const char* cName = env->GetStringUTFChars(name, 0);
    const char* cTextureName = env->GetStringUTFChars(textureName, 0);
    FlintAndSteelFactory* factory = new FlintAndSteelFactory();
    std::string itemNameId(cNameId);
    if(itemNameId.rfind("item_", 0) != 0) itemNameId = "item_" + itemNameId;
    factory->initParameters(id, itemNameId, cName, cTextureName, textureMeta);
    factory->props.stack = 1;
    factory->props.durability = durability;
    LegacyItemRegistry::registerItemFactory(factory);
    if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
    env->ReleaseStringUTFChars(nameId, cNameId);
    env->ReleaseStringUTFChars(name, cName);
    env->ReleaseStringUTFChars(textureName, cTextureName);
}