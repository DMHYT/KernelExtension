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


    template<typename CommandClass, typename FieldType>
    inline CommandParameterData mandatory(int valueFieldOffset, const char* paramName, int isSetFieldOffset) {
        return CommandParameterData(
            type_id<CommandRegistry, FieldType>(),
            (CommandRegistry::ParseFn) &CommandRegistry::parse<FieldType>,
            paramName, CommandParameterDataType::NORMAL, nullptr,
            valueFieldOffset, false, isSetFieldOffset
        );
    }

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData mandatory(FieldType CommandClass::* valueFieldOffset, const char* paramName, bool CommandClass::* isSetFieldOffset) {
        return mandatory<CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, getFieldOffset(isSetFieldOffset));
    }


    template<CommandParameterDataType DataType, typename CommandClass, typename FieldType>
    inline CommandParameterData mandatory(int valueFieldOffset, const char* paramName, const char* paramDescription, int isSetFieldOffset) {
        return CommandParameterData(
            type_id<CommandRegistry, FieldType>(),
            (CommandRegistry::ParseFn) &CommandRegistry::parseEnum<FieldType>,
            paramName, DataType, paramDescription,
            valueFieldOffset, false, isSetFieldOffset
        );
    }

    template<CommandParameterDataType DataType, typename CommandClass, typename FieldType>
    inline CommandParameterData mandatory(FieldType CommandClass::* valueFieldOffset, const char* paramName, const char* paramDescription, bool CommandClass::* isSetFieldOffset) {
        return mandatory<DataType, CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, paramDescription, getFieldOffset(isSetFieldOffset));
    }


    template<typename CommandClass, typename FieldType>
    inline CommandParameterData optional(int valueFieldOffset, const char* paramName, int isSetFieldOffset) {
        return CommandParameterData(
            type_id<CommandRegistry, FieldType>(),
            (CommandRegistry::ParseFn) &CommandRegistry::parse<FieldType>,
            paramName, CommandParameterDataType::NORMAL, nullptr,
            valueFieldOffset, true, isSetFieldOffset
        );
    }

    template<typename CommandClass, typename FieldType>
    inline CommandParameterData optional(FieldType CommandClass::* valueFieldOffset, const char* paramName, bool CommandClass::* isSetFieldOffset) {
        return optional<CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, getFieldOffset(isSetFieldOffset));
    }


    template<CommandParameterDataType DataType, typename CommandClass, typename FieldType>
    inline CommandParameterData optional(int valueFieldOffset, const char* paramName, const char* paramDescription, int isSetFieldOffset) {
        return CommandParameterData(
            type_id<CommandRegistry, FieldType>(),
            (CommandRegistry::ParseFn) &CommandRegistry::parseEnum<FieldType>,
            paramName, DataType, paramDescription,
            valueFieldOffset, true, isSetFieldOffset
        );
    }

    template<CommandParameterDataType DataType, typename CommandClass, typename FieldType>
    inline CommandParameterData optional(FieldType CommandClass::* valueFieldOffset, const char* paramName, const char* paramDescription, bool CommandClass::* isSetFieldOffset) {
        return optional<DataType, CommandClass, FieldType>(getFieldOffset(valueFieldOffset), paramName, paramDescription, getFieldOffset(isSetFieldOffset));
    }
    

}


#endif //KEX_COMMANDS_COMMANDS_HPP