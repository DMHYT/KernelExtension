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
std::unordered_map<std::string, void*> CommandRegistry::KEX_parsePointers;


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
            for(const std::string& alias : props.aliases) {
                registry.registerAlias(props.name.c_str(), alias.c_str());
            }
        }
        for(const std::__ndk1::vector<CommandParameterData>& overload : props.overloads) {
            registry.registerOverloadParamsVec<KEXAPICommand>(props.name.c_str(), overload);
        }
    }
}


void KEXCommandRegistry::NonNativeCommandFactory::init(const std::string& commandName) {
    props.name = commandName;
    props.description = "commands." + commandName + ".description";
}

void KEXCommandRegistry::NonNativeCommandFactory::addAlias(const std::string& alias) {
    if(usedNamesAndAliases.find(alias) != usedNamesAndAliases.end()) {
        Logger::debug("KEX-WARNING", "Alias %s for command %s has already been registered as a command name or as an alias, by vanilla or by KEX API!", alias.c_str(), props.name.c_str());
    } else {
        props.aliases.push_back(alias);
        usedNamesAndAliases.emplace(alias);
    }
}

void KEXCommandRegistry::NonNativeCommandFactory::setPermissionLevel(CommandPermissionLevel level) {
    props.permissionLevel = level;
}

void KEXCommandRegistry::NonNativeCommandFactory::setFlags(int first, int last) {
    props.flag1 = (CommandFlag) first;
    props.flag2 = (CommandFlag) last;
}

void KEXCommandRegistry::NonNativeCommandFactory::setCustomParsed(bool customParsed) {
    props.customParsed = customParsed;
}

const std::__ndk1::vector<CommandParameterData>& KEXCommandRegistry::NonNativeCommandFactory::addOverload() {
    props.overloads.push_back(std::__ndk1::vector<CommandParameterData>());
    return props.overloads.back();
}


void KEXCommandRegistry::KEXAPICommand::execute(CommandOrigin const& origin, CommandOutput& output) const {

}