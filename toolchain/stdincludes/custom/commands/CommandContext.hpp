#include <stl/string>
#include <stl/memory>
#include <stl.h>

#include "CommandRegistry.hpp"

#ifndef KEX_COMMANDCONTEXT_HPP
#define KEX_COMMANDCONTEXT_HPP


class CommandContext {
    public:
    stl::string command; // 12
    CommandOrigin* origin; // 16
    int version; // 20
    CommandContext(const stl::string&, stl::unique_ptr<CommandOrigin>, int);
    CommandOrigin& getCommandOrigin() const;
};


#endif //KEX_COMMANDCONTEXT_HPP