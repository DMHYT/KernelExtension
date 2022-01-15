#include <mod.h>

#include "modules/loot.hpp"
#include "modules/items.hpp"
#include "modules/tools.hpp"

#include "Java.h"


class KernelExtensionMain : public Module {
public:
	KernelExtensionMain(): Module("kernelex") {};
	virtual void initialize() {
		
    }
};


MAIN {
	Module* main = new KernelExtensionMain();
	Module* loot = new KEXLootModule(main);
	Module* items = new KEXItemsModule(main);
	Module* tools = new KEXToolsModule(main);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    Java::init(vm);
    return JNI_VERSION_1_6;
}
