#include <mod.h>
#include "modules/loot.hpp"


class KernelExtensionMain : public Module {
public:
	KernelExtensionMain(): Module("kernelex") {};
	virtual void initialize() {
		
    }
};


MAIN {
	Module* main = new KernelExtensionMain();
	Module* loot = new KEXLootModule(main);
}