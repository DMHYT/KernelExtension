#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <logger.h>

#include <commands/Command.hpp>

#ifndef _KEX_COMMANDREGISTRY_HPP
#define _KEX_COMMANDREGISTRY_HPP


class KEXCommandRegistry {
    public:
    class NativeCommandFactoryBase {
        public:
        NativeCommandFactoryBase() {}
        virtual void setup(CommandRegistry& registry) = 0;
    };
    class NonNativeCommandFactory : public NativeCommandFactoryBase {
        public:
        struct {
            std::string name = "";
            std::string description = "";
            std::vector<std::string> aliases;
            CommandPermissionLevel permissionLevel = CommandPermissionLevel::GAMEMASTERS;
            CommandFlag flag1 = (CommandFlag) 0;
            CommandFlag flag2 = (CommandFlag) 128;
            std::vector<std::__ndk1::vector<CommandParameterData>> overloads;
            bool customParsed = false;
        } props;
        NonNativeCommandFactory(): NativeCommandFactoryBase() {}
        virtual void setup(CommandRegistry& registry);
        void init(const std::string& commandName);
        void addAlias(const std::string& alias);
        void setPermissionLevel(CommandPermissionLevel level);
        void setFlags(int first, int last);
        void setCustomParsed(bool customParsed);
        const std::__ndk1::vector<CommandParameterData>& addOverload();
    };
    static std::unordered_map<std::string, NativeCommandFactoryBase*> registeredFactories;
    static std::unordered_set<std::string> usedNamesAndAliases;
    static void registerNativeCommandFactory(const std::string& commandName, NativeCommandFactoryBase* factory);
    static NativeCommandFactoryBase* getFactoryByName(const std::string& commandName);
    class KEXAPICommand : public Command {
        public:
        KEXAPICommand(): Command() {};
        virtual void execute(CommandOrigin const& origin, CommandOutput& output) const;
    };
};


#endif //_KEX_COMMANDREGISTRY_HPP