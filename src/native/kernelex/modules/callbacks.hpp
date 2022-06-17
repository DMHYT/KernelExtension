#include <mod.h>

#ifndef KEX_MODULES_CALLBACKS_HPP
#define KEX_MODULES_CALLBACKS_HPP


class KEXCallbacksModule : public Module {
    public:
    KEXCallbacksModule(Module* parent): Module(parent, "kex.callbacks") {};
    virtual void initialize();
};


#endif //KEX_MODULES_CALLBACKS_HPP