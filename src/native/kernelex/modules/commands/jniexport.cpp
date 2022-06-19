#include <cstdlib>
#include <jni.h>
#include <string.h>

#include <logger.h>

#include "command_registry.hpp"


extern "C" {
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_commands_CommandsNativeAPI_nativeNewCommand
    (JNIEnv* env, jclass, jstring commandName, jint permissionLevel, jobjectArray aliases) {
        const char* cCommandName = env->GetStringUTFChars(commandName, 0);
        if(KEXCommandRegistry::usedNamesAndAliases.find(cCommandName) != KEXCommandRegistry::usedNamesAndAliases.end()) return 0;
        KEXCommandRegistry::usedNamesAndAliases.emplace(cCommandName);
        auto factory = new KEXCommandRegistry::NonNativeCommandFactory();
        factory->init(cCommandName, (CommandPermissionLevel) permissionLevel);
        jsize l = env->GetArrayLength(aliases);
        for(int i = 0; i < l; i++) {
            jstring alias = (jstring) env->GetObjectArrayElement(aliases, i);
            const char* cAlias = env->GetStringUTFChars(alias, 0);
            factory->addAlias(cAlias);
            env->ReleaseStringUTFChars(alias, cAlias);
            env->DeleteLocalRef(alias);
        }
        KEXCommandRegistry::registeredFactories.emplace(cCommandName, factory);
        env->ReleaseStringUTFChars(commandName, cCommandName);
        return (jlong) factory;
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_commands_CommandsNativeAPI_nativeAddOverload
    (JNIEnv*, jclass, jlong factoryPtr, jint overloadIndex) {
        auto factory = (KEXCommandRegistry::NonNativeCommandFactory*) factoryPtr;
        return (jlong) factory->addOverload(overloadIndex);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_commands_CommandsNativeAPI_nativeBuildArgument
    (JNIEnv* env, jclass, jlong vectorPtr, jstring paramName, jint paramType, jstring enumName, jboolean mandatory, jint fieldOffset) {
        auto vec = (std::__ndk1::vector<CommandParameterData>*) vectorPtr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        const char* cEnumNameTemp = enumName == nullptr ? nullptr : env->GetStringUTFChars(enumName, 0);
        char* cEnumName = cEnumNameTemp == nullptr ? nullptr : (char*) malloc(strlen(cEnumNameTemp) + 1);
        if(enumName != nullptr) {
            strcpy(cEnumName, cEnumNameTemp);
            env->ReleaseStringUTFChars(enumName, cEnumNameTemp);
        }
        int isSetOffset = 2047 - vec->size();
        if(mandatory) {
            if(paramType == 0 || paramType == 15) {
                if(cEnumName == nullptr) {
                    vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, int>(fieldOffset, cParamName, isSetOffset));
                } else {
                    vec->push_back(commands::mandatory<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, int>(fieldOffset, cParamName, cEnumName, isSetOffset));
                }
            } else if(paramType == 1) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, float>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 2) {
                vec->push_back(commands::mandatory<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, bool>(fieldOffset, cParamName, cEnumName, isSetOffset));
            } else if(paramType == 3) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, RelativeFloat>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 4) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandPosition>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 5) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandPositionFloat>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 6) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, std::__ndk1::string>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 7) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandMessage>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 8) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandWildcardInt>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 9) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, Json::Value>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 10) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandSelector<Actor>>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 11) {
                vec->push_back(commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandSelector<Player>>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 12) {
                vec->push_back(commands::mandatory<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, CommandItem>(fieldOffset, cParamName, cEnumName, isSetOffset));
            } else if(paramType == 13) {
                vec->push_back(commands::mandatory<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, const Block*>(fieldOffset, cParamName, cEnumName, isSetOffset));
            } else if(paramType == 14) {
                vec->push_back(commands::mandatory<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, const MobEffect*>(fieldOffset, cParamName, cEnumName, isSetOffset));
            }
        } else {
            if(paramType == 0 || paramType == 15) {
                if(cEnumName == nullptr) {
                    vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, int>(fieldOffset, cParamName, isSetOffset));
                } else {
                    vec->push_back(commands::optional<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, int>(fieldOffset, cParamName, cEnumName, isSetOffset));
                }
            } else if(paramType == 1) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, float>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 2) {
                vec->push_back(commands::optional<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, bool>(fieldOffset, cParamName, cEnumName, isSetOffset));
            } else if(paramType == 3) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, RelativeFloat>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 4) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, CommandPosition>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 5) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, CommandPositionFloat>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 6) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, std::__ndk1::string>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 7) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, CommandMessage>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 8) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, CommandWildcardInt>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 9) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, Json::Value>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 10) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, CommandSelector<Actor>>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 11) {
                vec->push_back(commands::optional<KEXCommandRegistry::KEXAPICommand, CommandSelector<Player>>(fieldOffset, cParamName, isSetOffset));
            } else if(paramType == 12) {
                vec->push_back(commands::optional<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, CommandItem>(fieldOffset, cParamName, cEnumName, isSetOffset));
            } else if(paramType == 13) {
                vec->push_back(commands::optional<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, const Block*>(fieldOffset, cParamName, cEnumName, isSetOffset));
            } else if(paramType == 14) {
                vec->push_back(commands::optional<CommandParameterDataType::ENUM, KEXCommandRegistry::KEXAPICommand, const MobEffect*>(fieldOffset, cParamName, cEnumName, isSetOffset));
            }
        }
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_CommandsModule_registerAlias
    (JNIEnv* env, jclass, jstring name, jstring alias) {
        const char* cName = env->GetStringUTFChars(name, 0);
        const char* cAlias = env->GetStringUTFChars(alias, 0);
        if(KEXCommandRegistry::usedNamesAndAliases.find(cAlias) != KEXCommandRegistry::usedNamesAndAliases.end()) {
            Logger::debug("KEX-WARNING", "Alias %s for command %s has already been registered as a command name or as an alias, by vanilla or by KEX API!", cAlias, cName);
        } else {
            KEXCommandRegistry::usedNamesAndAliases.emplace(cAlias);
            KEXCommandRegistry::staticAliases.push_back({ cName, cAlias });
        }
        env->ReleaseStringUTFChars(name, cName);
        env->ReleaseStringUTFChars(alias, cAlias);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_commands_CommandsNativeAPI_nativeAddEnum
    (JNIEnv* env, jclass, jstring enumName, jobjectArray strings, jintArray ints) {
        const char* cEnumName = env->GetStringUTFChars(enumName, 0);
        if(KEXCommandRegistry::customEnums.find(cEnumName) == KEXCommandRegistry::customEnums.end()) {
            jsize l = env->GetArrayLength(strings);
            if(l > 0) {
                std::__ndk1::vector<std::__ndk1::pair<std::__ndk1::string, int>> values;
                jint* cInts = env->GetIntArrayElements(ints, 0);
                for(int i = 0; i < l; i++) {
                    jstring s = (jstring) env->GetObjectArrayElement(strings, i);
                    const char* cs = env->GetStringUTFChars(s, 0);
                    values.push_back({ cs, cInts[i] });
                    env->ReleaseStringUTFChars(s, cs);
                    env->DeleteLocalRef(s);
                }
                env->ReleaseIntArrayElements(ints, cInts, 0);
                KEXCommandRegistry::customEnums.emplace(cEnumName, values);
            }
        } else {
            Logger::debug("KEX-WARNING", "Command enum %s has already been registered by vanilla or by KEX API! Try using another name!", cEnumName);
        }
        env->ReleaseStringUTFChars(enumName, cEnumName);
    }
}