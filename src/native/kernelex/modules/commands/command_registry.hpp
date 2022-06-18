#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <logger.h>

#include <commands/Command.hpp>
#include <commands/commands.hpp>

#ifndef _KEX_COMMANDREGISTRY_HPP
#define _KEX_COMMANDREGISTRY_HPP


class KEXCommandRegistry {
    public:
    class NativeCommandFactoryBase {
        public:
        NativeCommandFactoryBase() {}
        virtual void setup(CommandRegistry& registry) = 0;
        virtual bool isNative() const { return true; }
    };
    class NonNativeCommandFactory : public NativeCommandFactoryBase {
        public:
        struct {
            std::string name = "";
            std::string description = "";
            std::vector<std::string> aliases;
            CommandPermissionLevel permissionLevel = CommandPermissionLevel::GAMEMASTERS;
            CommandFlag flag1 = (CommandFlag) 0;
            CommandFlag flag2 = (CommandFlag) 0;
            std::vector<std::__ndk1::vector<CommandParameterData>> overloads;
            bool customParsed = false;
        } props;
        NonNativeCommandFactory(): NativeCommandFactoryBase() {}
        virtual void setup(CommandRegistry& registry);
        virtual bool isNative() const { return false; }
        void init(const std::string& commandName, CommandPermissionLevel permissionLevel);
        void addAlias(const std::string& alias);
        void setFlags(int first, int last);
        void setCustomParsed(bool customParsed);
        std::__ndk1::vector<CommandParameterData>* addOverload(int overloadIndex);
    };
    static std::unordered_map<std::string, NativeCommandFactoryBase*> registeredFactories;
    static std::unordered_set<std::string> usedNamesAndAliases;
    static std::vector<std::pair<std::string, std::string>> staticAliases;
    static std::unordered_map<std::string, std::__ndk1::vector<std::__ndk1::pair<std::__ndk1::string, int>>> customEnums;
    static void registerNativeCommandFactory(const std::string& commandName, NativeCommandFactoryBase* factory);
    static NativeCommandFactoryBase* getFactoryByName(const std::string& commandName);
    class KEXAPICommand : public Command {
        public:
        int overloadIndex; // 36
        char extraFiller[2012]; // 2048
        KEXAPICommand(int _version, CommandRegistry* _registry, CommandRegistry::Symbol _symbol, CommandPermissionLevel perm, CommandFlag _flag, int index)
            : Command(_version, _registry, _symbol, perm, _flag), overloadIndex(index) {}
        KEXAPICommand(): Command() {}
        virtual void execute(CommandOrigin const& origin, CommandOutput& output) const;
    };
};


#endif //_KEX_COMMANDREGISTRY_HPP