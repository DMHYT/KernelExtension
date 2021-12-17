#include <mod.h>


class KernelExtensionMain : public Module {
public:
	KernelExtensionMain(): Module("kernelex") {};

	virtual void initialize() {
		
    }
};


MAIN {
	Module* main = new KernelExtensionMain();
}