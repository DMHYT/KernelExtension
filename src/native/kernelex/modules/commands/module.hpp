#include <mod.h>

#include <commands/CommandRegistry.hpp>

#ifndef KEX_MODULES_COMMANDS_HPP
#define KEX_MODULES_COMMANDS_HPP


class KEXCommandsModule : public Module {
    public:
    static void setupCustom(CommandRegistry&);
    static Command* onCreateAPICommand(CommandRegistry*, const CommandRegistry::ParseToken&, const CommandOrigin&, int, stl::string&, stl::vector<stl::string>&);
    KEXCommandsModule(Module* parent): Module(parent, "kex.commands") {};
    virtual void initialize();
};


#endif //KEX_MODULES_COMMANDS_HPP