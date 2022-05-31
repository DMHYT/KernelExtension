#include "CommandOrigin.hpp"
#include "CommandOutput.hpp"
#include "CommandRegistry.hpp"

#ifndef KEX_COMMAND_HPP
#define KEX_COMMAND_HPP


class Command {
    public:
    char filler[2044]; // 2048
    /*0*/ virtual ~Command();
    /*1*/ virtual void execute(CommandOrigin const&, CommandOutput&) const = 0;
    Command();
    std::__ndk1::string getCommandName() const;
    static Player* getPlayerFromOrigin(CommandOrigin const&);
};


#endif //KEX_COMMAND_HPP