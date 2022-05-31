#include <stl/memory>
#include <stl/string>
#include <stl/utility>
#include <stl/vector>

#include <unordered_map>

#include <symbol.h>

#include "../../../../../../DMH/cppheaders/json/value.h"

#include <enums.hpp>

#include <ActorDefinitionIdentifier.hpp>
#include <Block.hpp>
#include "CommandIntegerRange.hpp"
#include "CommandItem.hpp"
#include "CommandMessage.hpp"
#include "CommandPosition.hpp"
#include <MobEffect.hpp>
#include "RelativeFloat.hpp"

#ifndef KEX_COMMANDREGISTRY_HPP
#define KEX_COMMANDREGISTRY_HPP


class Command;
class CommandParameterData;
class CommandRegistry;
class Dimension;


template<typename T>
class typeid_t {
    public:
    static constexpr unsigned short count = 0;
    unsigned short value;
    typeid_t<T>(typeid_t<T> const& id): value(id.value) {}
    typeid_t<T>(unsigned short value): value(value) {}
};

template<>
class typeid_t<CommandRegistry> {
    public:
    static unsigned short count;
    unsigned short value;
    typeid_t<CommandRegistry>(typeid_t<CommandRegistry> const& id): value(id.value) {}
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

template typeid_t<CommandRegistry> type_id<CommandRegistry, ActorDamageCause>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, AutomaticID<Dimension, int>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, Block const*>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, bool>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandMessage>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandPosition>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandPositionFloat>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandSelector<Actor>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandSelector<Player>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, EquipmentSlot>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, float>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, int>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, Json::Value>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, Mirror>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, MobEffect const*>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, RelativeFloat>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, std::__ndk1::string>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, std::__ndk1::unique_ptr<Command>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, WildcardCommandSelector<Actor>>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandItem>();
template typeid_t<CommandRegistry> type_id<CommandRegistry, CommandIntegerRange>();
template<>
inline typeid_t<CommandRegistry> type_id<CommandRegistry, ActorDefinitionIdentifier const*>() {
    static typeid_t<CommandRegistry> id = *(typeid_t<CommandRegistry>*) SYMBOL("mcpe", "_ZZ7type_idI15CommandRegistryPK25ActorDefinitionIdentifierE8typeid_tIT_EvE2id");
    return id;
}


class CommandVersion {
    public:
    int min, max; // 8
    CommandVersion(int, int);
};


class CommandRegistry {
    public:

    typedef unsigned int Symbol;

    struct ParseToken {
        std::__ndk1::unique_ptr<ParseToken> child; // 4
        std::__ndk1::unique_ptr<ParseToken> next; // 8
        ParseToken* parent; // 12
        const char* text; // 16
        unsigned int length; // 20
        Symbol type; // 24
        std::__ndk1::string toString() const;
    };

    using ParseFn = bool (CommandRegistry::*)(
        void*, ParseToken const&, CommandOrigin const&, int, std::__ndk1::string&, 
        std::__ndk1::vector<std::__ndk1::string>&) const;

    struct Overload {
        using Factory = std::__ndk1::unique_ptr<Command> (*)();
        CommandVersion version; // 8
        Factory factory; // 12
        std::__ndk1::vector<CommandParameterData> params; // 24
        int someShit; // 28
        Overload(CommandVersion, Factory);
    };

    struct Signature {
        std::__ndk1::string name; // 12
        std::__ndk1::string description; // 24
        std::__ndk1::vector<Overload> overloads; // 36
        char rest[28]; // 64
    };

    template<typename T>
    struct DefaultIdConverter {

        template<typename Target, typename Source>
        static Target convert(Source source) {
            return (Target) source;
        }

        unsigned long long operator()(T value) const {
            return convert<unsigned long long, T>(value);
        }

        T operator()(unsigned long long value) const {
            return convert<T, unsigned long long>(value);
        }

    };

    void registerCommand(std::__ndk1::string const&, const char*, CommandPermissionLevel, CommandFlag, CommandFlag);

    void registerAlias(std::__ndk1::string, std::__ndk1::string);

    void registerOverloadInternal(Signature&, Overload&);

    inline void registerOverload(const char* commandName, Overload::Factory factory, std::__ndk1::vector<CommandParameterData>&& args) {
        Signature* signature = findCommand(commandName);
        Overload overload(CommandVersion(1, 0x7fffffff), factory);
        overload.params = args;
        signature->overloads.emplace_back(overload);
        registerOverloadInternal(*signature, overload);
    }

    template<typename CommandType, typename... Params>
    inline void registerOverload(const char* commandName, Params... params) {
        registerOverload(commandName, (Overload::Factory) &allocateCommand<CommandType>, { params... });
    }

    Signature* findCommand(std::__ndk1::string const&);

    template<typename CommandType>
    static inline std::__ndk1::unique_ptr<CommandType> allocateCommand() {
        return std::__ndk1::unique_ptr<CommandType>(new CommandType());
    }
    
    template<typename CommandType>
    inline void registerOverloadParamsVec(const char* commandName, const std::__ndk1::vector<CommandParameterData>& params) {
        CommandVersion version(1, 0x7fffffff);
        Overload overload(version, (Overload::Factory) &allocateCommand<CommandType>);
        overload.params = params;
        Signature* signature = findCommand(commandName);
        signature->overloads.emplace_back(overload);
        registerOverloadInternal(*signature, overload);
    }

    Symbol addEnumValuesInternal(std::__ndk1::string const&, std::__ndk1::vector<std::__ndk1::pair<unsigned int, unsigned long long>> const&, typeid_t<CommandRegistry>, ParseFn);
    Symbol addEnumValuesInternal(std::__ndk1::string const&, std::__ndk1::vector<std::__ndk1::pair<std::__ndk1::string, unsigned long long>> const&, typeid_t<CommandRegistry>, ParseFn);
    unsigned long long getEnumData(ParseToken const&) const;

    template<typename Type, typename IDConverter = DefaultIdConverter<Type>>
    inline bool parseEnum(void* target, ParseToken const& token, CommandOrigin const&, int, std::__ndk1::string&, std::__ndk1::vector<std::__ndk1::string>&) const {
        auto data = getEnumData(token);
        *(Type*)target = IDConverter{}(data);
        return true;
    }
    
    template<typename Type, typename IDConverter = DefaultIdConverter<Type>>
    inline Symbol addEnumValues(std::__ndk1::string const& name, typeid_t<CommandRegistry> tid, std::__ndk1::vector<std::__ndk1::pair<std::__ndk1::string, Type>> const& values) {
        std::__ndk1::vector<std::__ndk1::pair<std::__ndk1::string, unsigned long long>> converted;
        IDConverter converter;
        for(auto& value : values) {
            converted.emplace_back(value.first, converter(value.second));
        }
        return addEnumValuesInternal(name, converted, tid, (ParseFn) &CommandRegistry::parseEnum<Type, IDConverter>);
    }

    template<typename T>
    inline CommandRegistry* addEnum(const char* name, std::__ndk1::vector<std::__ndk1::pair<std::__ndk1::string, T>> const& values) {
        this->addEnumValues<T>(name, type_id<CommandRegistry, T>(), values);
        return this;
    }

    static std::unordered_map<std::string, void*> KEX_parsePointers;

    template<typename Type>
    inline bool fakeParse(void*, ParseToken const&, CommandOrigin const&, int, std::__ndk1::string&, std::__ndk1::vector<std::__ndk1::string>&) const { return false; }

    template<typename T>
    static inline ParseFn getParseFn() {
        if(!std::is_same<CommandOperator, T>::value && std::is_enum<T>::value) {
            return (ParseFn) &CommandRegistry::fakeParse<T>;
        }
        auto found = CommandRegistry::KEX_parsePointers.find(typeid(T).name());
        if(found == CommandRegistry::KEX_parsePointers.end()) return (ParseFn) &CommandRegistry::fakeParse<T>;
        union {
            void* unresolved;
            ParseFn resolved;
        } u;
        u.unresolved = found->second;
        return (ParseFn) u.resolved;
    }
    
};


class CommandParameterData {
    public:
    // typeid_t<CommandRegistry> tid; // 4
    // CommandRegistry::ParseFn parser; // 8
    // std::__ndk1::string name; // 20
    // const char* description; // 24
    // int something; // 28
    // CommandParameterDataType type; // 32
    // int offset; // 36
    // int flag_offset; // 40
    // bool optional; // 41
    // unsigned char options; // 42
    // char something2[6]; // 48
    char filler[48]; // 48
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