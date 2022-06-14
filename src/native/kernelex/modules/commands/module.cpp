#include <hook.h>
#include <symbol.h>

#include <commands/commands.hpp>

#include "command_registry.hpp"
#include "module.hpp"


class KEXTestCommand : public Command {
    public:
    KEXTestCommand(): Command() {}
    virtual void execute(CommandOrigin const& origin, CommandOutput& output) const {
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
            // commands::mandatory<CommandParameterDataType::ENUM, KEXTestCommand, int>(568, "customEnum", "KEXTestEnum", -1)
            // commands::mandatory<KEXTestCommand, CommandSelector<Actor>>(280, "actor", -1),
            // commands::mandatory<KEXTestCommand, CommandSelector<Player>>(420, "player", -1),
            // commands::mandatory<CommandParameterDataType::ENUM, KEXTestCommand, Block const*>(560, "block", "Block", -1),
            // commands::mandatory<CommandParameterDataType::ENUM, KEXTestCommand, MobEffect const*>(564, "effect", "Effect", -1)
            // commands::mandatory<KEXTestCommand, int>(256, "int", -1),
            // commands::mandatory<KEXTestCommand, float>(260, "float", -1),
            // commands::mandatory<CommandParameterDataType::ENUM, KEXTestCommand, bool>(268, "bool", "Boolean", -1),
            // commands::mandatory<KEXTestCommand, CommandPosition>(264, "pos", -1),
        });
    }
};


void KEXCommandsModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    // CommandMessage, std::__ndk1::string, bool, float, int, CommandSelector<Actor>, CommandSelector<Player>, CommandPosition, CommandPositionFloat, Json::Value, std::__ndk1::unique_ptr<Command>, RelativeFloat, Block const*, MobEffect const*, CommandItem, WildcardCommandSelector<Actor>, ActorDefinitionIdentifier const*
    HookManager::addCallback(SYMBOL("mcpe", "_ZN14ServerCommands19setupStandardServerER9MinecraftRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEESA_P15PermissionsFile"), LAMBDA((Minecraft* mc), {
        CommandRegistry* registry = mc->getCommands()->getRegistry();
        if(registry != nullptr && !KEXCommandRegistry::registeredFactories.empty()) {
            Logger::debug("KEX-CommandRegistry", "Registering %d custom commands...", KEXCommandRegistry::registeredFactories.size());
            for(std::unordered_map<std::string, KEXCommandRegistry::NativeCommandFactoryBase*>::iterator iter = KEXCommandRegistry::registeredFactories.begin(); iter != KEXCommandRegistry::registeredFactories.end(); iter++) {
                iter->second->setup(*registry);
                Logger::debug("KEX-CommandRegistry", "Successfully registered custom command: /%s", iter->first.c_str());
            }
        }
    }, ), HookManager::RETURN | HookManager::LISTENER);
    KEXCommandRegistry::registerNativeCommandFactory("kextest", new KEXTestCommandFactory());
}