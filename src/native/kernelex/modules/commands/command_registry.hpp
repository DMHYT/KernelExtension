#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <logger.h>
#include <static_symbol.h>

#include <commands/Command.hpp>
#include <commands/commands.hpp>

#ifndef _KEX_COMMANDREGISTRY_HPP
#define _KEX_COMMANDREGISTRY_HPP


class KEXCommandRegistry {
    public:

    class KEXAPICommand : public Command {
        public:
        std::string commandName; // 32
        int overloadIndex; // 36
        char extraFiller[2012]; // 2048
        KEXAPICommand(int _version, CommandRegistry* _registry, CommandRegistry::Symbol _symbol, CommandPermissionLevel perm, CommandFlag _flag, const std::string& name, int index)
            : Command(_version, _registry, _symbol, perm, _flag), commandName(name), overloadIndex(index) {}
        KEXAPICommand(): Command() {}
        virtual ~KEXAPICommand();
        virtual void execute(const CommandOrigin& origin, CommandOutput& output) const;
    };

    class NativeCommandFactoryBase {
        public:
        NativeCommandFactoryBase() {}
        virtual void setup(CommandRegistry& registry) = 0;
        virtual bool isNative() const { return true; }
    };


    class ArgumentTypes {
        public:

        class Base {
            public:
            CommandParameterData paramData;
            virtual int getArgumentType() const = 0;
            virtual void constructIn(KEXAPICommand* command) = 0;
            virtual void destructIn(KEXAPICommand* command) {}
            Base(const CommandParameterData& _paramData)
                : paramData(_paramData) {}
        };

        class Int : public Base {
            public:
            int defaultValue;
            bool isEnum;
            virtual int getArgumentType() const { return isEnum ? 11 : 0; }
            virtual void constructIn(KEXAPICommand* command) {
                *(int*) ((char*) command + paramData.offset) = defaultValue;
            }
            Int(const CommandParameterData& _paramData, int _defaultValue, bool _isEnum)
                : Base(_paramData), defaultValue(_defaultValue), isEnum(_isEnum) {}
        };

        class Float : public Base {
            public:
            float defaultValue;
            virtual int getArgumentType() const { return 1; }
            virtual void constructIn(KEXAPICommand* command) {
                *(float*) ((char*) command + paramData.offset) = defaultValue;
            }
            Float(const CommandParameterData& _paramData, float _defaultValue)
                : Base(_paramData), defaultValue(_defaultValue) {}
        };

        class Bool : public Base {
            public:
            bool defaultValue;
            virtual int getArgumentType() const { return 2; }
            virtual void constructIn(KEXAPICommand* command) {
                *(bool*) ((char*) command + paramData.offset) = defaultValue;
            }
            Bool(const CommandParameterData& _paramData, bool _defaultValue)
                : Base(_paramData), defaultValue(_defaultValue) {}
        };

        class RelFloat : public Base {
            public:
            float defaultValue;
            virtual int getArgumentType() const { return 3; }
            virtual void constructIn(KEXAPICommand* command) {
                new ((char*) command + paramData.offset) RelativeFloat(defaultValue);
            }
            RelFloat(const CommandParameterData& _paramData, float _defaultValue)
                : Base(_paramData), defaultValue(_defaultValue) {}
        };

        class Pos : public Base {
            public:
            float defX, defY, defZ;
            virtual int getArgumentType() const { return 4; }
            virtual void constructIn(KEXAPICommand* command) {
                new ((char*) command + paramData.offset) CommandPosition(defX, defY, defZ);
            }
            Pos(const CommandParameterData& _paramData, float x, float y, float z)
                : Base(_paramData), defX(x), defY(y), defZ(z) {}
        };

        class FloatPos : public Base {
            public:
            float defX, defY, defZ;
            virtual int getArgumentType() const { return 5; }
            virtual void constructIn(KEXAPICommand* command) {
                new ((char*) command + paramData.offset) CommandPositionFloat(defX, defY, defZ);
            }
            FloatPos(const CommandParameterData& _paramData, float x, float y, float z)
                : Base(_paramData), defX(x), defY(y), defZ(z) {}
        };
        
        class String : public Base {
            public:
            std::string defaultValue;
            bool isEnum;
            virtual int getArgumentType() const { return isEnum ? 12 : 6; }
            virtual void constructIn(KEXAPICommand* command) {
                new ((char*) command + paramData.offset) stl::string(defaultValue.c_str());
            }
            String(const CommandParameterData& _paramData, const std::string& _defaultValue, bool _isEnum)
                : Base(_paramData), defaultValue(_defaultValue), isEnum(_isEnum) {}
        };

        class Message : public Base {
            public:
            virtual int getArgumentType() const { return 7; }
            virtual void constructIn(KEXAPICommand* command) {
                new ((char*) command + paramData.offset) CommandMessage();
            }
            virtual void destructIn(KEXAPICommand* command) {
                delete (CommandMessage*) ((char*) command + paramData.offset);
            }
            Message(const CommandParameterData& _paramData)
                : Base(_paramData) {}
        };

        class JSON : public Base {
            public:
            virtual int getArgumentType() const { return 8; }
            virtual void constructIn(KEXAPICommand* command) {
                new ((char*) command + paramData.offset) Json::Value(0);
            }
            virtual void destructIn(KEXAPICommand* command) {
                delete (Json::Value*) ((char*) command + paramData.offset);
            }
            JSON(const CommandParameterData& _paramData)
                : Base(_paramData) {}
        };

        class Entity : public Base {
            public:
            virtual int getArgumentType() const { return 9; }
            virtual void constructIn(KEXAPICommand* command) {
                new ((char*) command + paramData.offset) CommandSelector<Actor>();
            }
            virtual void destructIn(KEXAPICommand* command) {
                STATIC_SYMBOL(destructSelector, "_ZN19CommandSelectorBaseD2Ev", (CommandSelectorBase*), void)
                destructSelector((CommandSelectorBase*) ((char*) command + paramData.offset));
            }
            Entity(const CommandParameterData& _paramData)
                : Base(_paramData) {}
        };

        class PlayerArg : public Base {
            public:
            virtual int getArgumentType() const { return 10; }
            virtual void constructIn(KEXAPICommand* command) {
                new ((char*) command + paramData.offset) CommandSelector<Player>();
            }
            virtual void destructIn(KEXAPICommand* command) {
                STATIC_SYMBOL(destructSelector, "_ZN19CommandSelectorBaseD2Ev", (CommandSelectorBase*), void)
                destructSelector((CommandSelectorBase*) ((char*) command + paramData.offset));
            }
            PlayerArg(const CommandParameterData& _paramData)
                : Base(_paramData) {}
        };

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
            std::vector<std::vector<ArgumentTypes::Base*>> overloads;
        } props;
        NonNativeCommandFactory(): NativeCommandFactoryBase() {}
        virtual void setup(CommandRegistry& registry);
        virtual bool isNative() const { return false; }
        void init(const std::string& commandName, CommandPermissionLevel permissionLevel);
        void addAlias(const std::string& alias);
        void setFlags(int first, int last);
        std::vector<ArgumentTypes::Base*>* addOverload(int overloadIndex);
    };

    static std::unordered_map<std::string, NativeCommandFactoryBase*> registeredFactories;
    static std::unordered_set<std::string> usedNamesAndAliases;
    static std::vector<std::pair<std::string, std::string>> staticAliases;
    static std::unordered_map<std::string, stl::vector<stl::pair<stl::string, int>>> customEnums;
    static std::unordered_map<std::string, stl::vector<stl::string>> customStringEnums;
    static void registerNativeCommandFactory(const std::string& commandName, NativeCommandFactoryBase* factory);
    static NativeCommandFactoryBase* getFactoryByName(const std::string& commandName);

};


#endif //_KEX_COMMANDREGISTRY_HPP