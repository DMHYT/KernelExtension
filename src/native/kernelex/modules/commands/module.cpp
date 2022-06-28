#include <regex>

#include <hook.h>
#include <symbol.h>
#include <static_symbol.h>

#include "../../utils/java_utils.hpp"
#include "command_registry.hpp"
#include "module.hpp"


void KEXCommandsModule::setupCustom(CommandRegistry& registry) {
    Logger::debug("KEX-CommandRegistry", "Setup started...");
    if(!KEXCommandRegistry::customEnums.empty() || !KEXCommandRegistry::customStringEnums.empty()) {
        Logger::debug("KEX-CommandRegistry", "Registering %d custom command enums and literals...", KEXCommandRegistry::customEnums.size() + KEXCommandRegistry::customStringEnums.size());
        for(auto iter = KEXCommandRegistry::customEnums.begin(); iter != KEXCommandRegistry::customEnums.end(); iter++) {
            registry.addEnumValues<int>(iter->first.c_str(), iter->second);
            if(iter->first.rfind("KEXLITERAL-", 0) == 0) {
                Logger::debug("KEX-CommandRegistry", "Successfully registered command literal: %s", iter->first.substr(11).c_str());
            } else {
                Logger::debug("KEX-CommandRegistry", "Successfully registered custom command enum: %s", iter->first.c_str());
            }
        }
        for(auto iter = KEXCommandRegistry::customStringEnums.begin(); iter != KEXCommandRegistry::customStringEnums.end(); iter++) {
            registry.addEnumValues(iter->first.c_str(), iter->second);
            Logger::debug("KEX-CommandRegistry", "Successfully registered custom command enum: %s", iter->first.c_str());
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


Command* KEXCommandsModule::onCreateAPICommand(CommandRegistry* registry, const CommandRegistry::ParseToken& token, const CommandOrigin& origin, int version, stl::string& str, stl::vector<stl::string>& strvec) {
    STATIC_SYMBOL(CommandRegistry_isParseMatch, "_ZN15CommandRegistry12isParseMatchERK20CommandParameterDataNS_6SymbolE", (const CommandParameterData&, CommandRegistry::Symbol*), bool)
    auto commandName = token.child->toString();
    auto signature = registry->findCommand(commandName);
    if(signature != nullptr) {
        auto startToken = token.child->next.get();
        for(int overloadIndex = 0; overloadIndex < signature->overloads.size(); overloadIndex++) {
            auto& overload = signature->overloads.at(overloadIndex);
            if(overload.version.isCompatible(version)) {
                auto tokenToUse = startToken;
                bool parseResult = true;
                for(const auto& param : overload.params) {
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
                    auto command = new KEXCommandRegistry::KEXAPICommand(version, registry, signature->mainSymbol, signature->perm, signature->flag, commandName.c_str(), overloadIndex);
                    KEXCommandRegistry::NonNativeCommandFactory* factory = (KEXCommandRegistry::NonNativeCommandFactory*) KEXCommandRegistry::getFactoryByName(commandName.c_str());
                    for(const auto& param : factory->props.overloads.at(overloadIndex)) {
                        param->constructIn(command);
                    }
                    tokenToUse = startToken;
                    for(const auto& param : overload.params) {
                        bool& flag = *(bool*) ((char*) command + param.flag_offset);
                        flag = false;
                        if(tokenToUse != nullptr) {
                            flag = registry->parseParameter(command, param, *tokenToUse, origin, version, str, strvec);
                            tokenToUse = tokenToUse->next.get();
                        }
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
    
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN14ServerCommands19setupStandardServerER9MinecraftRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEESA_P15PermissionsFile"),
        LAMBDA((Minecraft* mc), {
            CommandRegistry* registry = mc->getCommands()->getRegistry();
            if(registry != nullptr) {
                setupCustom(*registry);
            }
        }, ),
        HookManager::RETURN | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK15CommandRegistry13createCommandERKNS_10ParseTokenERK13CommandOriginiRNSt6__ndk112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEERNS6_6vectorISC_NSA_ISC_EEEE"),
        LAMBDA((HookManager::CallbackController* controller, Command** result, CommandRegistry* registry, const CommandRegistry::ParseToken& token, const CommandOrigin& origin, int version, stl::string& str, stl::vector<stl::string>& strvec), {
            auto factory = KEXCommandRegistry::getFactoryByName(token.child->toString().c_str());
            if(factory != nullptr && !factory->isNative()) {
                controller->prevent();
                *result = onCreateAPICommand(registry, token, origin, version, str, strvec);
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN4I18n3getERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE"),
        LAMBDA((stl::string* result, const stl::string& key), {
            if(std::regex_match(key.c_str(), std::regex("^%commands.[A-z0-9_/-]{1,}.description$")) && *result == key.substr(1)) {
                JNIEnv* env = KEXJavaUtils::attach();
                auto commandName = std::regex_replace(std::regex_replace(key.c_str(), std::regex("%commands."), ""), std::regex(".description"), "");
                jstring output = KEXJavaBridge::CommandsModule::translateCommandDescription(commandName.c_str());
                const char* cOutput = env->GetStringUTFChars(output, 0);
                *result = cOutput;
                env->ReleaseStringUTFChars(output, cOutput);
                env->DeleteLocalRef(output);
            }
        }, ),
        HookManager::RETURN | HookManager::LISTENER
    );

}