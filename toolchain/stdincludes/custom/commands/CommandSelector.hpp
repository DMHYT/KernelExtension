#include <commontypes.hpp>
#include <enums.hpp>

#include <ActorDefinitionIdentifier.hpp>
#include "CommandPosition.hpp"
#include <Player.hpp>

#ifndef KEX_COMMANDSELECTOR_HPP
#define KEX_COMMANDSELECTOR_HPP


class CommandSelectorBase {
    public:
    char filler[120]; // 120
    void addFilter(stl::function<bool(const CommandOrigin&, const Actor&)>);
    bool compile(const CommandOrigin&, stl::string&);
    stl::string getName() const;
    bool hasName() const;
    bool isExplicitIdSelector() const;
    void setIncludeDeadPlayers(bool);
    void setType(CommandSelectionType);
    void setVersion(int);
};


template<typename T>
class CommandSelector : public CommandSelectorBase {
    public:
    CommandSelector();
    CommandSelectorResults<T> results(const CommandOrigin& origin) const;
};


template<typename T>
class WildcardCommandSelector : public CommandSelectorBase {
    public:
    WildcardCommandSelector(): CommandSelectorBase(std::is_same<T, Player>::value) {}
};


#endif //KEX_COMMANDSELECTOR_HPP