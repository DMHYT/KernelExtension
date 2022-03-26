#include <mod.h>

#ifndef KEX_MODULES_CALLBACKS_HPP
#define KEX_MODULES_CALLBACKS_HPP


class KEXCallbacksModule : public Module {
    public:
    KEXCallbacksModule(Module* parent): Module(parent, "kernelex.callbacks") {};
    virtual void initialize();
};


#endif //KEX_MODULES_CALLBACKS_HPP