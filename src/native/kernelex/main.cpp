#include <mod.h>

#include "modules/loot.hpp"
#include "modules/items.hpp"
#include "modules/tools/module.hpp"
#include "modules/tools/submodules/method_patches.hpp"
#include "modules/tools/submodules/interactions.hpp"
#include "modules/commands/module.hpp"
#include "modules/callbacks.hpp"
#include "modules/damage.hpp"
#include "modules/misc/reachdist.hpp"
#include "modules/misc/cameraroll.hpp"

#include "utils/java_utils.hpp"


class KernelExtensionMain : public Module {
public:
	KernelExtensionMain(): Module("kex") {};
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
	Module* toolPatches = new KEXToolPatchesModule(tools);
	Module* toolInteractions = new KEXToolInteractionsModule(tools);
	Module* commands = new KEXCommandsModule(main);
	Module* callbacks = new KEXCallbacksModule(main);
	Module* damage = new KEXDamageModule(main);
	Module* reachdist = new KEXMiscReachDistModule(main);
	Module* cameraroll = new KEXMiscCameraRollModule(main);
}


extern "C" JNIEXPORT void JNICALL Java_vsdum_kex_KernelExtension_defineCallbackClasses
(JNIEnv* env, jclass) {
	KEXJavaBridge::Cache::KernelExtension(env);
	KEXJavaBridge::Cache::CustomToolEvents(env);
	KEXJavaBridge::Cache::LootModule(env);
	KEXJavaBridge::Cache::CallbacksModule(env);
	KEXJavaBridge::Cache::ItemsModule(env);
	KEXJavaBridge::Cache::DamageModule(env);
	KEXJavaBridge::Cache::CommandsModule(env);
}