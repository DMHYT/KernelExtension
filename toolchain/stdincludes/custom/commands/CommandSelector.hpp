#include <stl/functional>

#include <symbol.h>

#include <commontypes.hpp>
#include <enums.hpp>

#include <ActorDefinitionIdentifier.hpp>
#include "CommandOrigin.hpp"
#include "CommandPosition.hpp"

#ifndef KEX_COMMANDSELECTOR_HPP
#define KEX_COMMANDSELECTOR_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
    class Player;
#endif

class CommandSelectorBase {
    public:
    unsigned int version; // 4
    CommandSelectionType type; // 8
    unsigned int order; // 12
    std::__ndk1::vector<InvertableFilter<std::__ndk1::string>> nameFilters; // 24
    char something[24]; // 48
    std::__ndk1::vector<InvertableFilter<ActorDefinitionIdentifier>> familyFilters; // 60
    std::__ndk1::vector<InvertableFilter<std::__ndk1::string>> tagFilters; // 72
    std::__ndk1::vector<std::__ndk1::function<bool(CommandOrigin const&, Actor const&)>> customFilters; // 84
    CommandPosition position; // 100
    BlockPos box; // 112
    float radiusMin, radiusMax; // 120
    unsigned long long resultCount; // 128
    bool includeDeadPlayers; // 129
    char something2[5]; // 134
    bool playerOnly; // 135
    char explicitIdSelector; // 136
    char something3; // 137 + 3
    void addFilter(std::__ndk1::function<bool(CommandOrigin const&, Actor const&)>);
    bool compile(CommandOrigin const&, std::__ndk1::string&);
    std::__ndk1::string getName() const;
    bool hasName() const;
    bool isExplicitIdSelector() const;
    void setIncludeDeadPlayers(bool);
    void setType(CommandSelectionType);
    void setVersion(int);
};


template<typename T>
class CommandSelector : public CommandSelectorBase {
    public:
    CommandSelector(): CommandSelectorBase(std::is_same<T, Player>::value) {}
    inline CommandSelectorResults<T> results(CommandOrigin const& origin) const {
        CommandSelectorResults<T> (CommandSelector<T>::*rv)(CommandOrigin const& origin) const;
        if(std::is_same<Actor, T>::value) {
            *((void**)&rv) = SYMBOL("mcpe", "_ZNK15CommandSelectorI5ActorE7resultsERK13CommandOrigin");
            return (this->*rv)(origin);
        } else {
            *((void**)&rv) = SYMBOL("mcpe", "_ZNK15CommandSelectorI6PlayerE7resultsERK13CommandOrigin");
            return (this->*rv)(origin);
        }
    }
};


template<typename T>
class WildcardCommandSelector : public CommandSelectorBase {
    public:
    WildcardCommandSelector(): CommandSelectorBase(std::is_same<T, Player>::value) {}
};


#endif //KEX_COMMANDSELECTOR_HPP