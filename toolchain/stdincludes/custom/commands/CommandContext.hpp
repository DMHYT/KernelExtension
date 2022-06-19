#include <stl/string>
#include <stl/memory>

#include "CommandRegistry.hpp"

#ifndef KEX_COMMANDCONTEXT_HPP
#define KEX_COMMANDCONTEXT_HPP


class CommandContext {
    public:
    std::__ndk1::string command; // 12
    CommandOrigin* origin; // 16
    int version; // 20
    CommandContext(const std::__ndk1::string&, std::__ndk1::unique_ptr<CommandOrigin>, int);
    CommandOrigin& getCommandOrigin() const;
};


#endif //KEX_COMMANDCONTEXT_HPP