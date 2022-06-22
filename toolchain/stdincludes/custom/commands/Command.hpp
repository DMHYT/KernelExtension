#include "CommandOutput.hpp"
#include "CommandRegistry.hpp"

#ifndef KEX_COMMAND_HPP
#define KEX_COMMAND_HPP


class Command {
    public:
    int version; // 8
    CommandRegistry* registry; // 12
    CommandRegistry::Symbol symbol; // 16
    CommandPermissionLevel permissionLevel; // 17
    CommandFlag flag; // 18 + 2
    /*0*/ virtual ~Command();
    /*1*/ virtual void execute(const CommandOrigin&, CommandOutput&) const = 0;
    inline Command(int _version, CommandRegistry* _registry, CommandRegistry::Symbol _symbol, CommandPermissionLevel perm, CommandFlag _flag)
        : version(_version), registry(_registry), symbol(_symbol), permissionLevel(perm), flag(_flag) {}
    Command();
    stl::string getCommandName() const;
    static Player* getPlayerFromOrigin(const CommandOrigin&);
};


#endif //KEX_COMMAND_HPP