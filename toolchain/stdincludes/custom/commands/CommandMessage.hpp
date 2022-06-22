#include <stl/memory>
#include <stl/string>
#include <stl/vector>
#include <stl.h>

#include "CommandSelector.hpp"

#ifndef KEX_COMMANDMESSAGE_HPP
#define KEX_COMMANDMESSAGE_HPP


class CommandMessage {
    public:
    char filler[12];
    CommandMessage();
    stl::string getMessage(const CommandOrigin&) const;
    ~CommandMessage();
};


#endif //KEX_COMMANDMESSAGE_HPP