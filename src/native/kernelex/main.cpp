#include <mod.h>

#include "modules/loot.hpp"
#include "modules/items.hpp"
#include "modules/tools/module.hpp"

#include "utils/java_utils.hpp"


class KernelExtensionMain : public Module {
public:
	KernelExtensionMain(): Module("kernelex") {};
	virtual void initialize() {
		
    }
};


extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    KEXJavaUtils::init(vm);
    return JNI_VERSION_1_6;
} NO_JNI_MAIN {
	Module* main = new KernelExtensionMain();
	Module* loot = new KEXLootModule(main);
	Module* items = new KEXItemsModule(main);
	Module* tools = new KEXToolsModule(main);
}


extern "C" JNIEXPORT void JNICALL Java_vsdum_kex_KernelExtension_defineCallbackClasses
(JNIEnv* env, jclass) {
	KEXJavaBridge::Cache::ToolsModule(env);
	KEXJavaBridge::Cache::LootModule(env);
}