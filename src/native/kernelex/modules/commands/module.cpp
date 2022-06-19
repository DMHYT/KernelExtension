#include <hook.h>
#include <symbol.h>
#include <static_symbol.h>

#include <commands/commands.hpp>
#include <commands/CommandContext.hpp>

#include "command_registry.hpp"
#include "module.hpp"


class KEXTestCommand : public Command {
    public:
    char extraFiller[992]; // 1024
    KEXTestCommand(): Command() {}
    virtual void execute(const CommandOrigin& origin, CommandOutput& output) const {
        Logger::debug("KEX", "CALLED KEXTEST COMMAND!!!");
    }
};

class KEXTestCommandFactory : public KEXCommandRegistry::NativeCommandFactoryBase {
    public:
    KEXTestCommandFactory(): NativeCommandFactoryBase() {}
    virtual void setup(CommandRegistry& registry) {
        registry.addEnumValues<int>("KEXTestEnum", {
            { "testenummember0", 0 },
            { "testenummember1", 1 },
            { "testenummember2", 2 },
            { "testenummember3", 3 }
        });
        registry.registerCommand("kextest", "commands.kextest.description", CommandPermissionLevel::GAMEMASTERS, CommandFlag::CFLAG_NONE, CommandFlag::CFLAG_NONE);
        registry.registerOverloadParamsVec<KEXTestCommand>("kextest", {
            commands::mandatory<CommandParameterDataType::ENUM, KEXTestCommand, int>(568, "customEnum", "KEXTestEnum", -1),
            commands::mandatory<KEXTestCommand, CommandSelector<Actor>>(280, "actor", -1),
            commands::mandatory<KEXTestCommand, CommandSelector<Player>>(420, "player", -1),
            commands::mandatory<CommandParameterDataType::ENUM, KEXTestCommand, const Block*>(560, "block", "Block", -1),
            commands::mandatory<CommandParameterDataType::ENUM, KEXTestCommand, const MobEffect*>(564, "effect", "Effect", -1),
            commands::mandatory<KEXTestCommand, int>(256, "int", -1),
            commands::mandatory<KEXTestCommand, float>(260, "float", -1),
            commands::mandatory<CommandParameterDataType::ENUM, KEXTestCommand, bool>(268, "bool", "Boolean", -1),
            commands::mandatory<KEXTestCommand, CommandPosition>(264, "pos", -1),
        });
    }
};


void KEXCommandsModule::setupCustom(CommandRegistry& registry) {
    Logger::debug("KEX-CommandRegistry", "Setup started...");
    if(!KEXCommandRegistry::customEnums.empty()) {
        Logger::debug("KEX-CommandRegistry", "Registering %d custom command enums and literals...", KEXCommandRegistry::customEnums.size());
        for(auto iter = KEXCommandRegistry::customEnums.begin(); iter != KEXCommandRegistry::customEnums.end(); iter++) {
            registry.addEnumValues<int>(iter->first.c_str(), iter->second);
            if(iter->first.rfind("KEXLITERAL-", 0) == 0) {
                Logger::debug("KEX-CommandRegistry", "Successfully registered command literal: %s", iter->first.substr(11).c_str());
            } else {
                Logger::debug("KEX-CommandRegistry", "Successfully registered custom command enum: %s", iter->first.c_str());
            }
        }
    }
    if(!KEXCommandRegistry::registeredFactories.empty()) {
        Logger::debug("KEX-CommandRegistry", "Registering %d custom commands...", KEXCommandRegistry::registeredFactories.size());
        for(auto iter = KEXCommandRegistry::registeredFactories.begin(); iter != KEXCommandRegistry::registeredFactories.end(); iter++) {
            iter->second->setup(registry);
            Logger::debug("KEX-CommandRegistry", "Successfully registered custom command: /%s", iter->first.c_str());
        }
    }
    if(!KEXCommandRegistry::staticAliases.empty()) {
        Logger::debug("KEX-CommandRegistry", "Registering %d separate command aliases...", KEXCommandRegistry::staticAliases.size());
        for(const auto& al : KEXCommandRegistry::staticAliases) {
            registry.registerAlias(al.first.c_str(), al.second.c_str());
        }
    }
    Logger::debug("KEX-CommandRegistry", "Setup successfully finished!");
}


Command* KEXCommandsModule::onCreateAPICommand(CommandRegistry* registry, const CommandRegistry::ParseToken& token, const CommandOrigin& origin, int version, std::__ndk1::string& str, std::__ndk1::vector<std::__ndk1::string>& strvec) {
    STATIC_SYMBOL(CommandRegistry_isParseMatch, "_ZN15CommandRegistry12isParseMatchERK20CommandParameterDataNS_6SymbolE", (const CommandParameterData&, CommandRegistry::Symbol*), bool)
    CommandRegistry::Signature* signature = registry->findCommand(token.child->toString());
    if(signature != nullptr) {
        CommandRegistry::ParseToken* startToken = token.child->next.get();
        for(int overloadIndex = 0; overloadIndex < signature->overloads.size(); overloadIndex++) {
            CommandRegistry::Overload& overload = signature->overloads.at(overloadIndex);
            if(overload.version.isCompatible(version)) {
                CommandRegistry::ParseToken* tokenToUse = startToken;
                bool parseResult = true;
                for(const CommandParameterData& param : overload.params) {
                    if(tokenToUse == nullptr) {
                        if(!param.optional) parseResult = false;
                        break;
                    }
                    if(!CommandRegistry_isParseMatch(param, &tokenToUse->tokenType)) {
                        parseResult = false;
                        break;
                    }
                    tokenToUse = tokenToUse->next.get();
                }
                if(parseResult) {
                    KEXCommandRegistry::KEXAPICommand* command = new KEXCommandRegistry::KEXAPICommand(version, registry, signature->mainSymbol, signature->perm, signature->flag, overloadIndex);
                    tokenToUse = startToken;
                    for(const CommandParameterData& param : overload.params) {
                        bool paramParseResult = registry->parseParameter(command, param, *tokenToUse, origin, version, str, strvec);
                        if(param.flag_offset >= 0) *(bool*) ((char*) command + param.flag_offset) = paramParseResult;
                        if(tokenToUse->next != nullptr) tokenToUse = tokenToUse->next.get();
                    }
                    return command;
                }
            }
        }
    }
    return nullptr;
}


void KEXCommandsModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    // CommandMessage, std::__ndk1::string, bool, float, int, CommandSelector<Actor>, CommandSelector<Player>, CommandPosition, CommandPositionFloat, Json::Value, std::__ndk1::unique_ptr<Command>, RelativeFloat, const Block*, const MobEffect*, CommandItem, WildcardCommandSelector<Actor>, const ActorDefinitionIdentifier*
    HookManager::addCallback(SYMBOL("mcpe", "_ZN14ServerCommands19setupStandardServerER9MinecraftRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEESA_P15PermissionsFile"), LAMBDA((Minecraft* mc), {
        CommandRegistry* registry = mc->getCommands()->getRegistry();
        if(registry != nullptr) {
            setupCustom(*registry);
        }
    }, ), HookManager::RETURN | HookManager::LISTENER);
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK15CommandRegistry13createCommandERKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEERNS6_6vectorISC_NSA_ISC_EEEE"), LAMBDA((HookManager::CallbackController* controller, Command** result, CommandRegistry* registry, const CommandRegistry::ParseToken& token, const CommandOrigin& origin, int version, std::__ndk1::string& str, std::__ndk1::vector<std::__ndk1::string>& strvec), {
        auto found = KEXCommandRegistry::registeredFactories.find(token.child->toString().c_str());
        if(found != KEXCommandRegistry::registeredFactories.end() && !found->second->isNative()) {
            controller->prevent();
            *result = onCreateAPICommand(registry, token, origin, version, str, strvec);
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER);
    KEXCommandRegistry::registerNativeCommandFactory("kextest", new KEXTestCommandFactory());
}