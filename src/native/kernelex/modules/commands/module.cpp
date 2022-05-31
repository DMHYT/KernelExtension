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
        // registry.addEnum<int>("KEXTestEnum", {
        //     { "testenummember0", 0 },
        //     { "testenummember1", 1 },
        //     { "testenummember2", 2 },
        //     { "testenummember3", 3 }
        // });
        registry.registerCommand("kextest", "commands.kextest.description", CommandPermissionLevel::GAMEMASTERS, CommandFlag::CFLAG_NONE, CommandFlag::CFLAG_NONE);
        registry.registerOverloadParamsVec<KEXTestCommand>("kextest", {});
    }
};


void KEXCommandsModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    CommandRegistry::KEX_parsePointers = {
        { typeid(CommandMessage).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseI14CommandMessageEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS9_11char_traitsIcEENS9_9allocatorIcEEEERNS9_6vectorISF_NSD_ISF_EEEE") },
        { typeid(std::__ndk1::string).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEEEbPvRKNS_10ParseTokenERK13CommandOriginiRS7_RNS1_6vectorIS7_NS5_IS7_EEEE") },
        { typeid(bool).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseIbEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS8_11char_traitsIcEENS8_9allocatorIcEEEERNS8_6vectorISE_NSC_ISE_EEEE") },
        { typeid(float).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseIfEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS8_11char_traitsIcEENS8_9allocatorIcEEEERNS8_6vectorISE_NSC_ISE_EEEE") },
        { typeid(int).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseIiEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS8_11char_traitsIcEENS8_9allocatorIcEEEERNS8_6vectorISE_NSC_ISE_EEEE") },
        { typeid(CommandSelector<Actor>).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseI15CommandSelectorI5ActorEEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNSB_11char_traitsIcEENSB_9allocatorIcEEEERNSB_6vectorISH_NSF_ISH_EEEE") },
        { typeid(CommandSelector<Player>).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseI15CommandSelectorI6PlayerEEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNSB_11char_traitsIcEENSB_9allocatorIcEEEERNSB_6vectorISH_NSF_ISH_EEEE") },
        { typeid(CommandPosition).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseI15CommandPositionEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS9_11char_traitsIcEENS9_9allocatorIcEEEERNS9_6vectorISF_NSD_ISF_EEEE") },
        { typeid(CommandPositionFloat).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseI20CommandPositionFloatEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS9_11char_traitsIcEENS9_9allocatorIcEEEERNS9_6vectorISF_NSD_ISF_EEEE") },
        { typeid(Json::Value).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseIN4Json5ValueEEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNSA_11char_traitsIcEENSA_9allocatorIcEEEERNSA_6vectorISG_NSE_ISG_EEEE") },
        { typeid(std::__ndk1::unique_ptr<Command>).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseINSt6__ndk110unique_ptrI7CommandNS1_14default_deleteIS3_EEEEEEbPvRKNS_10ParseTokenERK13CommandOriginiRNS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEERNS1_6vectorISJ_NSH_ISJ_EEEE") },
        { typeid(RelativeFloat).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseI13RelativeFloatEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS9_11char_traitsIcEENS9_9allocatorIcEEEERNS9_6vectorISF_NSD_ISF_EEEE") },
        { typeid(Block const*).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseIPK5BlockEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNSB_11char_traitsIcEENSB_9allocatorIcEEEERNSB_6vectorISH_NSF_ISH_EEEE") },
        { typeid(MobEffect const*).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseIPK9MobEffectEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNSB_11char_traitsIcEENSB_9allocatorIcEEEERNSB_6vectorISH_NSF_ISH_EEEE") },
        { typeid(CommandItem).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseI11CommandItemEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS9_11char_traitsIcEENS9_9allocatorIcEEEERNS9_6vectorISF_NSD_ISF_EEEE") },
        { typeid(WildcardCommandSelector<Actor>).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseI23WildcardCommandSelectorI5ActorEEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNSB_11char_traitsIcEENSB_9allocatorIcEEEERNSB_6vectorISH_NSF_ISH_EEEE") },
        { typeid(ActorDefinitionIdentifier const*).name(), SYMBOL("mcpe", "_ZNK15CommandRegistry5parseIPK25ActorDefinitionIdentifierEEbPvRKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNSB_11char_traitsIcEENSB_9allocatorIcEEEERNSB_6vectorISH_NSF_ISH_EEEE") }
    };
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