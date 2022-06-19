#include <symbol.h>

#include "command_registry.hpp"


std::unordered_set<std::string> KEXCommandRegistry::usedNamesAndAliases {
    "?", "alwaysday",
    "camerashake", "clear", "clearspawnpoint", "clone", "connect",
    "daylock", "deop", "difficulty",
    "effect", "enchant", "event", "execute",
    "fill", "fog", "function",
    "gamemode", "gamerule", "give",
    "help", "kick", "kill",
    "me", "mixer", "mobevent", "msg", "music",
    "op", "particle", "playanimation", "playsound",
    "reload", "replaceitem", "ride",
    "say", "schedule", "scoreboard", "setblock", "setmaxplayers", "setworldspawn", "spawnpoint", "spreadplayers", "stopsound", "structure", "summon",
    "tag", "teleport", "tell", "tellraw", "testfor", "testforblock", "testforblocks", "tickingarea", "time", "title", "titleraw", "toggledownfall", "tp",
    "w", "weather", "wsserver", "xp"
};


std::unordered_map<std::string, KEXCommandRegistry::NativeCommandFactoryBase*> KEXCommandRegistry::registeredFactories;
std::vector<std::pair<std::string, std::string>> KEXCommandRegistry::staticAliases;
std::unordered_map<std::string, std::__ndk1::vector<std::__ndk1::pair<std::__ndk1::string, int>>> KEXCommandRegistry::customEnums;


void KEXCommandRegistry::registerNativeCommandFactory(const std::string& commandName, KEXCommandRegistry::NativeCommandFactoryBase* factory) {
    if(KEXCommandRegistry::usedNamesAndAliases.find(commandName) != KEXCommandRegistry::usedNamesAndAliases.end()) {
        Logger::debug("KEX-WARNING", "Command with name %s has already been registered by vanilla or by KEX API! Try using another name.", commandName.c_str());
    } else {
        KEXCommandRegistry::registeredFactories.emplace(commandName, factory);
    }
}


KEXCommandRegistry::NativeCommandFactoryBase* KEXCommandRegistry::getFactoryByName(const std::string& commandName) {
    auto found = KEXCommandRegistry::registeredFactories.find(commandName);
    if(found == KEXCommandRegistry::registeredFactories.end()) return nullptr;
    return found->second;
}


void KEXCommandRegistry::NonNativeCommandFactory::setup(CommandRegistry& registry) {
    if(!props.overloads.empty()) {
        registry.registerCommand(props.name.c_str(), props.description.c_str(), props.permissionLevel, props.flag1, props.flag2);
        if(!props.aliases.empty()) {
            for(const auto& alias : props.aliases) {
                registry.registerAlias(props.name.c_str(), alias.c_str());
            }
        }
        for(const auto& overload : props.overloads) {
            registry.registerOverloadParamsVec<KEXAPICommand>(props.name.c_str(), overload);
        }
    }
}


void KEXCommandRegistry::NonNativeCommandFactory::init(const std::string& commandName, CommandPermissionLevel permissionLevel) {
    props.name = commandName;
    props.description = "commands." + commandName + ".description";
    props.permissionLevel = permissionLevel;
}

void KEXCommandRegistry::NonNativeCommandFactory::addAlias(const std::string& alias) {
    if(usedNamesAndAliases.find(alias) != usedNamesAndAliases.end()) {
        Logger::debug("KEX-WARNING", "Alias %s for command %s has already been registered as a command name or as an alias, by vanilla or by KEX API!", alias.c_str(), props.name.c_str());
    } else {
        props.aliases.push_back(alias);
        usedNamesAndAliases.emplace(alias);
    }
}

void KEXCommandRegistry::NonNativeCommandFactory::setFlags(int first, int last) {
    props.flag1 = (CommandFlag) first;
    props.flag2 = (CommandFlag) last;
}

void KEXCommandRegistry::NonNativeCommandFactory::setCustomParsed(bool customParsed) {
    props.customParsed = customParsed;
}

std::__ndk1::vector<CommandParameterData>* KEXCommandRegistry::NonNativeCommandFactory::addOverload(int overloadIndex) {
    if(overloadIndex < props.overloads.size()) {
        return &props.overloads.at(overloadIndex);
    } else if(overloadIndex == props.overloads.size()) {
        props.overloads.push_back({});
        return &props.overloads.at(overloadIndex);
    }
    Logger::debug("KEX-WARNING", "Overload index %d for command %s is too big, maximum index at the moment is %d. Returning dummy vector reference...", overloadIndex, props.name.c_str(), props.overloads.size());
    return new std::__ndk1::vector<CommandParameterData>();
}


void KEXCommandRegistry::KEXAPICommand::execute(const CommandOrigin& origin, CommandOutput& output) const {}