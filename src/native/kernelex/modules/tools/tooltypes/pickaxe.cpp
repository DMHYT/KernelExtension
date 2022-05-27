#include <jni.h>

#include <innercore/id_conversion_map.h>

#include <items/PickaxeItem.hpp>

#include "pickaxe.hpp"


void PickaxeFactory::registerItem() {
    ToolFactory::registerItem();
    if(id != 0) {
        ItemRegistry::registerItemFixed<PickaxeItem>(new PickaxeProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier);
    }
}


extern "C" JNIEXPORT void JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeRegisterPickaxe
(JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech) {
    const char* cNameId = env->GetStringUTFChars(nameId, 0);
    const char* cName = env->GetStringUTFChars(name, 0);
    const char* cTextureName = env->GetStringUTFChars(textureName, 0);
    PickaxeFactory* factory = new PickaxeFactory();
    std::string itemNameId(cNameId);
    if(itemNameId.rfind("item_", 0) != 0) itemNameId = "item_" + itemNameId;
    factory->initParameters(id, itemNameId, std::string(cName), std::string(cTextureName), textureMeta);
    factory->props.stack = 1;
    factory->tier = (Item::Tier*) tierPtr;
    LegacyItemRegistry::registerItemFactory(factory);
    if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
    env->ReleaseStringUTFChars(nameId, cNameId);
    env->ReleaseStringUTFChars(name, cName);
    env->ReleaseStringUTFChars(textureName, cTextureName);
}