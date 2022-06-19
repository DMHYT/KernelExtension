#include <stl/memory>
#include <stl/string>
#include <stl/vector>
#include <stl.h>

#include "CommandSelector.hpp"

#ifndef KEX_COMMANDMESSAGE_HPP
#define KEX_COMMANDMESSAGE_HPP


class CommandMessage {
    public:
    struct MessageComponent {
        stl::string msg; // 12
        stl::unique_ptr<CommandSelector<Actor>> actor; // 16
    };
    stl::vector<MessageComponent> components; // 12
    CommandMessage();
    stl::string getMessage(const CommandOrigin&) const;
};


#endif //KEX_COMMANDMESSAGE_HPP