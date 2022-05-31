#include <mod.h>

#ifndef KEX_MODULES_COMMANDS_HPP
#define KEX_MODULES_COMMANDS_HPP


class KEXCommandsModule : public Module {
    public:
    KEXCommandsModule(Module* parent): Module(parent, "kex.commands") {};
    virtual void initialize();
};


#endif //KEX_MODULES_COMMANDS_HPP