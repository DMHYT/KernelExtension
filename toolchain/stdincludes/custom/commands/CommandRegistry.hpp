#include <stl/memory>
#include <stl/string>
#include <stl/utility>
#include <stl/vector>
#include <stl.h>

#include <json/value.h>

#include <enums.hpp>

#include <ActorDefinitionIdentifier.hpp>
#include <Block.hpp>
#include "CommandIntegerRange.hpp"
#include "CommandItem.hpp"
#include "CommandMessage.hpp"
#include "CommandPosition.hpp"
#include "CommandWildcardInt.hpp"
#include <MobEffect.hpp>
#include "RelativeFloat.hpp"

#ifndef KEX_COMMANDREGISTRY_HPP
#define KEX_COMMANDREGISTRY_HPP


class Command;
class CommandOrigin;
class CommandParameterData;
class CommandRegistry;
class Dimension;


template<typename T>
class typeid_t {
    public:
    static constexpr unsigned short count = 0;
    unsigned short value;
    typeid_t<T>(const typeid_t<T>& id): value(id.value) {}
    typeid_t<T>(unsigned short value): value(value) {}
};

template<>
class typeid_t<CommandRegistry> {
    public:
    static unsigned short count;
    unsigned short value;
    typeid_t<CommandRegistry>(const typeid_t<CommandRegistry>& id): value(id.value) {}
    typeid_t<CommandRegistry>(unsigned short value): value(value) {}
};

template<typename T>
typeid_t<T> type_id() {
    static typeid_t<T> id = typeid_t<T>::count++;
    return id;
}
template<typename T, typename T2>
typeid_t<T> type_id() {
    static typeid_t<T> id = typeid_t<T>::count++;
    return id;
}

template typeid_t<CommandRegistry> type_id<CommandRegistry, AutomaticID<Dimension, int>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, bool>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandMessage>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandPosition>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandPositionFloat>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandSelector<Actor>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandSelector<Player>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, float>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, int>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, Json::Value>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, RelativeFloat>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, stl::string>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, stl::unique_ptr<Command>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, WildcardCommandSelector<Actor>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandItem>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandWildcardInt>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, const ActorDefinitionIdentifier*>();


class CommandVersion {
    public:
    int min, max; // 8
    inline CommandVersion(): min(0), max(0x7fffffff) {}
    CommandVersion(int, int);
    bool isCompatible(int) const;
};


class CommandRegistry {
    public:

    struct Symbol { unsigned int val; };

    struct ParseToken {
        stl::unique_ptr<ParseToken> child; // 4
        stl::unique_ptr<ParseToken> next; // 8
        ParseToken* parent; // 12
        const char* text; // 16
        unsigned int length; // 20
        Symbol tokenType; // 24
        stl::string toString() const;
    };

    using ParseFn = bool (CommandRegistry::*)(
        void*, const ParseToken&, const CommandOrigin&, int, stl::string&, 
        stl::vector<stl::string>&) const;

    struct Overload {
        using Factory = stl::unique_ptr<Command> (*)();
        CommandVersion version; // 8
        Factory factory; // 12
        stl::vector<CommandParameterData> params; // 24
        int someShit; // 28
        inline Overload(CommandVersion v, Factory f, const stl::vector<CommandParameterData>& p)
            : version(v), factory(f), params(p), someShit(-1) {}
        Overload(CommandVersion, Factory);
    };

    struct Signature {
        stl::string name; // 12
        stl::string description; // 24
        stl::vector<Overload> overloads; // 36
        CommandPermissionLevel perm; // 37 + 3
        Symbol mainSymbol; // 44
        Symbol altSymbol; // 48
        CommandFlag flag; // 49
        char unk[15]; // 64
    };

    template<typename T> struct DefaultIdConverter;

    void registerCommand(const stl::string&, const char*, CommandPermissionLevel, CommandFlag, CommandFlag);
    void registerAlias(stl::string, stl::string);
    void registerOverloadInternal(Signature&, Overload&);
    Signature* findCommand(const stl::string&);
    template<typename Type, typename IDConverter = DefaultIdConverter<Type>> int addEnumValues(const stl::string& name, const stl::vector<stl::pair<stl::string, Type>>& values);
    template<typename Type> bool parse(void*, const ParseToken&, const CommandOrigin&, int, stl::string&, stl::vector<stl::string>&) const;
    template<typename Type, typename IDConverter = DefaultIdConverter<Type>> bool parseEnum(void*, const ParseToken&, const CommandOrigin&, int, stl::string&, stl::vector<stl::string>&) const;
    bool parseParameter(Command*, const CommandParameterData&, const ParseToken&, const CommandOrigin&, int, stl::string&, stl::vector<stl::string>&) const;
    stl::string getCommandName(const stl::string&) const;
    static bool isParseMatch(const CommandParameterData&, Symbol);

    inline void registerOverload(const char* commandName, Overload::Factory factory, stl::vector<CommandParameterData>&& args) {
        auto signature = findCommand(commandName);
        Overload overload(CommandVersion(1, 0x7fffffff), factory);
        overload.params = args;
        signature->overloads.emplace_back(overload);
        registerOverloadInternal(*signature, overload);
    }

    template<typename CommandType, typename... Params>
    inline void registerOverload(const char* commandName, Params... params) {
        registerOverload(commandName, (Overload::Factory) &allocateCommand<CommandType>, { params... });
    }

    template<typename CommandType>
    static inline stl::unique_ptr<CommandType> allocateCommand() {
        return stl::unique_ptr<CommandType>(new CommandType());
    }
    
    template<typename CommandType>
    inline void registerOverloadParamsVec(const char* commandName, const stl::vector<CommandParameterData>& params) {
        auto signature = findCommand(commandName);
        signature->overloads.emplace_back(CommandVersion{}, (Overload::Factory) &allocateCommand<CommandType>, params);
        registerOverloadInternal(*signature, signature->overloads.back());
    }
    
};


class CommandParameterData {
    public:
    typeid_t<CommandRegistry> tid; // 2 + 2
    CommandRegistry::ParseFn parser; // 12
    stl::string name; // 24
    const char* description; // 28
    int something; // 32
    CommandParameterDataType type; // 36
    int offset; // 40
    int flag_offset; // 44
    bool optional; // 45
    unsigned char options; // 46 + 2
    CommandParameterData(typeid_t<CommandRegistry> tid, CommandRegistry::ParseFn parser, const char* paramName, CommandParameterDataType type, const char* enumName, int offset, bool optional, int flagOffset);
    CommandParameterData& addOptions(CommandParameterOption);
};


class MinecraftCommands {
    public:
    CommandRegistry* getRegistry() const;
};

class Minecraft {
    public:
    MinecraftCommands* getCommands();
};


#endif //KEX_COMMANDREGISTRY_HPP