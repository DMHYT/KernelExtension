#include "CommandRegistry.hpp"

#ifndef KEX_COMMANDS_COMMANDS_HPP
#define KEX_COMMANDS_COMMANDS_HPP


namespace commands {


    template<typename CommandClass, typename FieldType>
    static inline int getFieldOffset(FieldType CommandClass::*src) {
        union {
            FieldType CommandClass::*src;
            int value;
        } u;
        u.src = src;
        return u.value;
    }

    // mandatory

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData mandatory(int valueFieldOffset, const char* paramName, const char* enumName, int isSetFieldOffset) {
        return CommandParameterData(
            type_id<CommandRegistry, FieldType>(),
            (CommandRegistry::ParseFn) &CommandRegistry::parse<FieldType>,
            paramName, CommandParameterDataType::NORMAL, enumName,
            valueFieldOffset, false, isSetFieldOffset
        );
    }

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData mandatory(int valueFieldOffset, const char* paramName, int isSetFieldOffset) {
        return mandatory<CommandClass, FieldType>(valueFieldOffset, paramName, nullptr, isSetFieldOffset);
    }

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData mandatory(FieldType CommandClass::* valueFieldOffset, const char* paramName, bool CommandClass::* isSetFieldOffset) {
        return mandatory<CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, getFieldOffset(isSetFieldOffset));
    }

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData mandatory(FieldType CommandClass::* valueFieldOffset, const char* paramName, const char* enumName, bool CommandClass::* isSetFieldOffset) {
        return mandatory<CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, enumName, getFieldOffset(isSetFieldOffset));
    }

    template<typename CommandClass, typename FieldType = int>
    inline CommandParameterData mandatoryEnum(int valueFieldOffset, const char* paramName, const char* enumName, int isSetFieldOffset) {
        return CommandParameterData(
            type_id<CommandRegistry, FieldType>(),
            (CommandRegistry::ParseFn) &CommandRegistry::parseEnum<FieldType>,
            paramName, CommandParameterDataType::ENUM, enumName,
            valueFieldOffset, false, isSetFieldOffset
        );
    }

    template<typename CommandClass, typename FieldType = int>
    inline CommandParameterData mandatoryEnum(FieldType CommandClass::* valueFieldOffset, const char* paramName, const char* enumName, bool CommandClass::* isSetFieldOffset) {
        return mandatoryEnum<CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, enumName, getFieldOffset(isSetFieldOffset));
    }

    // optional

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData optional(int valueFieldOffset, const char* paramName, const char* enumName, int isSetFieldOffset) {
        return CommandParameterData(
            type_id<CommandRegistry, FieldType>(),
            (CommandRegistry::ParseFn) &CommandRegistry::parse<FieldType>,
            paramName, CommandParameterDataType::NORMAL, enumName,
            valueFieldOffset, true, isSetFieldOffset
        );
    }

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData optional(int valueFieldOffset, const char* paramName, int isSetFieldOffset) {
        return optional<CommandClass, FieldType>(valueFieldOffset, paramName, nullptr, isSetFieldOffset);
    }

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData optional(FieldType CommandClass::* valueFieldOffset, const char* paramName, bool CommandClass::* isSetFieldOffset) {
        return optional<CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, getFieldOffset(isSetFieldOffset));
    }

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData optional(FieldType CommandClass::* valueFieldOffset, const char* paramName, const char* enumName, bool CommandClass::* isSetFieldOffset) {
        return optional<CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, enumName, getFieldOffset(isSetFieldOffset));
    }

    template<typename CommandClass, typename FieldType = int>
    inline CommandParameterData optionalEnum(int valueFieldOffset, const char* paramName, const char* enumName, int isSetFieldOffset) {
        return CommandParameterData(
            type_id<CommandRegistry, FieldType>(),
            (CommandRegistry::ParseFn) &CommandRegistry::parseEnum<FieldType>,
            paramName, CommandParameterDataType::ENUM, enumName,
            valueFieldOffset, true, isSetFieldOffset
        );
    }

    template<typename CommandClass, typename FieldType = int>
    inline CommandParameterData optionalEnum(FieldType CommandClass::* valueFieldOffset, const char* paramName, const char* enumName, bool CommandClass::* isSetFieldOffset) {
        return optionalEnum<CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, enumName, getFieldOffset(isSetFieldOffset));
    }
    

}


#endif //KEX_COMMANDS_COMMANDS_HPP