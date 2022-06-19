#include <stl/memory>
#include <stl/string>
#include <stl/vector>

#include "CommandSelector.hpp"

#ifndef KEX_COMMANDMESSAGE_HPP
#define KEX_COMMANDMESSAGE_HPP


class CommandMessage {
    public:
    struct MessageComponent {
        std::__ndk1::string msg; // 12
        std::__ndk1::unique_ptr<CommandSelector<Actor>> actor; // 16
    };
    std::__ndk1::vector<MessageComponent> components; // 12
    CommandMessage();
    std::__ndk1::string getMessage(const CommandOrigin&) const;
};


#endif //KEX_COMMANDMESSAGE_HPP