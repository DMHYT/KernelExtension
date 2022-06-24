#include <cstdlib>
#include <jni.h>
#include <string.h>

#include <logger.h>

#include <innercore/vtable.h>

#include <ActorUniqueID.hpp>

#include "command_registry.hpp"


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_modules_commands_CommandsNativeAPI_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


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
        if(KEXCommandRegistry::customEnums.find(cEnumName) == KEXCommandRegistry::customEnums.end() && KEXCommandRegistry::customStringEnums.find(cEnumName) == KEXCommandRegistry::customStringEnums.end()) {
            jsize l = env->GetArrayLength(strings);
            if(l > 0) {
                stl::vector<stl::pair<stl::string, int>> values;
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
            Logger::debug("KEX-WARNING", "Command enum %s has already been registered by KEX API! Try using another name!", cEnumName);
        }
        env->ReleaseStringUTFChars(enumName, cEnumName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_commands_CommandsNativeAPI_nativeAddStringEnum
    (JNIEnv* env, jclass, jstring enumName, jobjectArray strings) {
        const char* cEnumName = env->GetStringUTFChars(enumName, 0);
        if(KEXCommandRegistry::customEnums.find(cEnumName) == KEXCommandRegistry::customEnums.end() && KEXCommandRegistry::customStringEnums.find(cEnumName) == KEXCommandRegistry::customStringEnums.end()) {
            jsize l = env->GetArrayLength(strings);
            if(l > 0) {
                stl::vector<stl::string> values;
                for(int i = 0; i < l; i++) {
                    jstring s = (jstring) env->GetObjectArrayElement(strings, i);
                    const char* cs = env->GetStringUTFChars(s, 0);
                    values.push_back(cs);
                    env->ReleaseStringUTFChars(s, cs);
                    env->DeleteLocalRef(s);
                }
                KEXCommandRegistry::customStringEnums.emplace(cEnumName, values);
            }
        } else {
            Logger::debug("KEX-WARNING", "Command enum %s has already been registered by KEX API! Try using another name!", cEnumName);
        }
        env->ReleaseStringUTFChars(enumName, cEnumName);
    }
    __EXPORT__(void, BuildIntArgument, jstring paramName, jboolean mandatory, jint fieldOffset, jint defaultValue) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::Int(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, int>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, int>(fieldOffset, cParamName, isSetOffset),
                defaultValue, false
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildFloatArgument, jstring paramName, jboolean mandatory, jint fieldOffset, jfloat defaultValue) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::Float(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, float>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, float>(fieldOffset, cParamName, isSetOffset),
                defaultValue
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildBoolArgument, jstring paramName, jboolean mandatory, jint fieldOffset, jboolean defaultValue) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::Bool(
                mandatory ? commands::mandatoryEnum<KEXCommandRegistry::KEXAPICommand, bool>(fieldOffset, cParamName, "Boolean", isSetOffset)
                : commands::optionalEnum<KEXCommandRegistry::KEXAPICommand, bool>(fieldOffset, cParamName, "Boolean", isSetOffset),
                defaultValue
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildRelativeFloatArgument, jstring paramName, jboolean mandatory, jint fieldOffset, jfloat defaultValue) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::RelFloat(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, RelativeFloat>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, RelativeFloat>(fieldOffset, cParamName, isSetOffset),
                defaultValue
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildPositionArgument, jstring paramName, jboolean mandatory, jint fieldOffset, jfloat defaultX, jfloat defaultY, jfloat defaultZ) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::Pos(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandPosition>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, CommandPosition>(fieldOffset, cParamName, isSetOffset),
                defaultX, defaultY, defaultZ
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildFloatPositionArgument, jstring paramName, jboolean mandatory, jint fieldOffset, jfloat defaultX, jfloat defaultY, jfloat defaultZ) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::FloatPos(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandPositionFloat>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, CommandPositionFloat>(fieldOffset, cParamName, isSetOffset),
                defaultX, defaultY, defaultZ
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildStringArgument, jstring paramName, jboolean mandatory, jint fieldOffset, jstring defaultValue) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        const char* cDefaultValue = defaultValue == nullptr ? nullptr : env->GetStringUTFChars(defaultValue, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::String(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, stl::string>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, stl::string>(fieldOffset, cParamName, isSetOffset),
                cDefaultValue == nullptr ? "" : cDefaultValue, false
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
        if(cDefaultValue != nullptr) env->ReleaseStringUTFChars(defaultValue, cDefaultValue);
    }
    __EXPORT__(void, BuildMessageArgument, jstring paramName, jboolean mandatory, jint fieldOffset) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::Message(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandMessage>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, CommandMessage>(fieldOffset, cParamName, isSetOffset)
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildJsonArgument, jstring paramName, jboolean mandatory, jint fieldOffset) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::JSON(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, Json::Value>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, Json::Value>(fieldOffset, cParamName, isSetOffset)
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildEntityArgument, jstring paramName, jboolean mandatory, jint fieldOffset) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::Entity(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandSelector<Actor>>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, CommandSelector<Actor>>(fieldOffset, cParamName, isSetOffset)
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildPlayerArgument, jstring paramName, jboolean mandatory, jint fieldOffset) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::PlayerArg(
                mandatory ? commands::mandatory<KEXCommandRegistry::KEXAPICommand, CommandSelector<Player>>(fieldOffset, cParamName, isSetOffset)
                : commands::optional<KEXCommandRegistry::KEXAPICommand, CommandSelector<Player>>(fieldOffset, cParamName, isSetOffset)
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildEnumArgument, jstring paramName, jboolean mandatory, jint fieldOffset, jstring enumName, jint defaultValue) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        int isSetOffset = 2047 - vec->size();
        const char* cEnumNameTemp = env->GetStringUTFChars(enumName, 0);
        char* cEnumName = (char*) malloc(strlen(cEnumNameTemp) + 1);
        strcpy(cEnumName, cEnumNameTemp);
        env->ReleaseStringUTFChars(enumName, cEnumNameTemp);
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::Int(
                mandatory ? commands::mandatoryEnum<KEXCommandRegistry::KEXAPICommand>(fieldOffset, cParamName, cEnumName, isSetOffset)
                : commands::optionalEnum<KEXCommandRegistry::KEXAPICommand>(fieldOffset, cParamName, cEnumName, isSetOffset),
                defaultValue, true
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
    }
    __EXPORT__(void, BuildStringEnumArgument, jstring paramName, jboolean mandatory, jint fieldOffset, jstring enumName, jstring defaultValue) {
        auto vec = (std::vector<KEXCommandRegistry::ArgumentTypes::Base*>*) ptr;
        const char* cParamName = env->GetStringUTFChars(paramName, 0);
        const char* cDefaultValue = defaultValue == nullptr ? nullptr : env->GetStringUTFChars(defaultValue, 0);
        int isSetOffset = 2047 - vec->size();
        const char* cEnumNameTemp = env->GetStringUTFChars(enumName, 0);
        char* cEnumName = (char*) malloc(strlen(cEnumNameTemp) + 1);
        strcpy(cEnumName, cEnumNameTemp);
        env->ReleaseStringUTFChars(enumName, cEnumNameTemp);
        vec->push_back(
            new KEXCommandRegistry::ArgumentTypes::String(
                mandatory ? commands::mandatoryEnum<KEXCommandRegistry::KEXAPICommand, stl::string, (CommandRegistry::ParseFn) &CommandRegistry::parse<stl::string>>(fieldOffset, cParamName, cEnumName, isSetOffset)
                : commands::optionalEnum<KEXCommandRegistry::KEXAPICommand, stl::string, (CommandRegistry::ParseFn) &CommandRegistry::parse<stl::string>>(fieldOffset, cParamName, cEnumName, isSetOffset),
                cDefaultValue == nullptr ? "" : cDefaultValue, true
            )
        );
        env->ReleaseStringUTFChars(paramName, cParamName);
        if(cDefaultValue != nullptr) env->ReleaseStringUTFChars(defaultValue, cDefaultValue);
    }
    __EXPORT__(jint, GetInt, jint offset) {
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr;
        return *(int*) ((char*) cmd + offset);
    }
    __EXPORT__(jfloat, GetFloat, jint offset) {
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr;
        return *(float*) ((char*) cmd + offset);
    }
    __EXPORT__(jboolean, GetBool, jint offset) {
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr;
        return *(bool*) ((char*) cmd + offset);
    }
    __EXPORT__(jfloat, GetRelativeFloat, jint offset, jfloat center) {
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr;
        return ((RelativeFloat*) ((char*) cmd + offset))->getValue(center);
    }
    __EXPORT__(jfloatArray, GetPosition, jint offset, jlong originPtr, jfloat centerX, jfloat centerY, jfloat centerZ) {
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr;
        auto origin = (CommandOrigin*) originPtr;
        BlockPos pos = ((CommandPosition*) ((char*) cmd + offset))->getBlockPos(*origin, Vec3(centerX, centerY, centerZ));
        jfloatArray result = env->NewFloatArray(3);
        jfloat fill[3];
        fill[0] = (float) pos.x; fill[1] = (float) pos.y; fill[2] = (float) pos.z;
        env->SetFloatArrayRegion(result, 0, 3, fill);
        return result;
    }
    __EXPORT__(jfloatArray, GetFloatPosition, jint offset, jlong originPtr, jfloat centerX, jfloat centerY, jfloat centerZ) {
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr;
        auto origin = (CommandOrigin*) originPtr;
        Vec3 pos = ((CommandPositionFloat*) ((char*) cmd + offset))->getPosition(*origin, Vec3(centerX, centerY, centerZ));
        jfloatArray result = env->NewFloatArray(3);
        jfloat fill[3];
        fill[0] = pos.x; fill[1] = pos.y; fill[2] = pos.z;
        env->SetFloatArrayRegion(result, 0, 3, fill);
        return result;
    }
    __EXPORT__(jstring, GetString, jint offset) {
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr;
        return env->NewStringUTF(((stl::string*) ((char*) cmd + offset))->c_str());
    }
    __EXPORT__(jstring, GetMessage, jint offset, jlong originPtr) {
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr;
        auto origin = (CommandOrigin*) originPtr;
        return env->NewStringUTF(((CommandMessage*) ((char*) cmd + offset))->getMessage(*origin).c_str());
    }
    __EXPORT__(jstring, GetJson, jint offset) {
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr;
        return env->NewStringUTF(((Json::Value*) ((char*) cmd + offset))->toStyledString().c_str());
    }
    #define GET_SELECTOR(NAME, TYPE) __EXPORT__(jlongArray, NAME, jint offset, jlong originPtr) { \
        auto cmd = (KEXCommandRegistry::KEXAPICommand*) ptr; \
        auto origin = (CommandOrigin*) originPtr; \
        stl::vector<TYPE*>* results = ((CommandSelector<TYPE>*) ((char*) cmd + offset))->results(*origin).data.get(); \
        int l = results->size(); \
        jlongArray result = env->NewLongArray(l); \
        jlong fill[l]; \
        for(int i = 0; i < l; i++) { \
            fill[i] = (jlong) results->at(i)->getUniqueID()->id; \
        } \
        env->SetLongArrayRegion(result, 0, l, fill); \
        return result; \
    }
    GET_SELECTOR(GetEntities, Actor)
    GET_SELECTOR(GetPlayers, Player)
    #undef GET_SELECTOR
    __EXPORT__(jintArray, GetSourceBlockPosition) {
        auto origin = (CommandOrigin*) ptr;
        VTABLE_FIND_OFFSET(PlayerCommandOrigin_getBlockPosition, _ZTV19PlayerCommandOrigin, _ZNK19PlayerCommandOrigin16getBlockPositionEv);
        BlockPos pos = VTABLE_CALL<BlockPos>(PlayerCommandOrigin_getBlockPosition, origin);
        jintArray result = env->NewIntArray(3);
        jint fill[3];
        fill[0] = pos.x; fill[1] = pos.y; fill[2] = pos.z;
        env->SetIntArrayRegion(result, 0, 3, fill);
        return result;
    }
    __EXPORT__(jfloatArray, GetSourceWorldPosition) {
        auto origin = (CommandOrigin*) ptr;
        VTABLE_FIND_OFFSET(PlayerCommandOrigin_getWorldPosition, _ZTV19PlayerCommandOrigin, _ZNK19PlayerCommandOrigin16getWorldPositionEv);
        Vec3 pos = VTABLE_CALL<Vec3>(PlayerCommandOrigin_getWorldPosition, origin);
        jfloatArray result = env->NewFloatArray(3);
        jfloat fill[3];
        fill[0] = pos.x; fill[1] = pos.y; fill[2] = pos.z;
        env->SetFloatArrayRegion(result, 0, 3, fill);
        return result;
    }
    __EXPORT__(jlong, GetSourceLevel) {
        auto origin = (CommandOrigin*) ptr;
        VTABLE_FIND_OFFSET(PlayerCommandOrigin_getLevel, _ZTV19PlayerCommandOrigin, _ZNK19PlayerCommandOrigin8getLevelEv);
        Level* level = VTABLE_CALL<Level*>(PlayerCommandOrigin_getLevel, origin);
        if(level == nullptr) return 0;
        return (jlong) level;
    }
    __EXPORT__(jlong, GetSourceDimension) {
        auto origin = (CommandOrigin*) ptr;
        VTABLE_FIND_OFFSET(PlayerCommandOrigin_getLevel, _ZTV19PlayerCommandOrigin, _ZNK19PlayerCommandOrigin12getDimensionEv);
        Dimension* dimension = VTABLE_CALL<Dimension*>(PlayerCommandOrigin_getLevel, origin);
        if(dimension == nullptr) return 0;
        return (jlong) dimension;
    }
    __EXPORT__(jlong, GetSourceEntity) {
        auto origin = (CommandOrigin*) ptr;
        VTABLE_FIND_OFFSET(PlayerCommandOrigin_getEntity, _ZTV19PlayerCommandOrigin, _ZNK19PlayerCommandOrigin9getEntityEv);
        Actor* actor = VTABLE_CALL<Actor*>(PlayerCommandOrigin_getEntity, origin);
        if(actor == nullptr) return 0;
        return actor->getUniqueID()->id;
    }
    __EXPORT__(void, EmptySuccess) {
        ((CommandOutput*) ptr)->success();
    }
    __EXPORT__(void, Success, jstring msg) {
        auto output = (CommandOutput*) ptr;
        const char* cMsg = env->GetStringUTFChars(msg, 0);
        output->success(cMsg, {});
        env->ReleaseStringUTFChars(msg, cMsg);
    }
    __EXPORT__(void, Error, jstring msg) {
        auto output = (CommandOutput*) ptr;
        const char* cMsg = env->GetStringUTFChars(msg, 0);
        output->error(cMsg, {});
        env->ReleaseStringUTFChars(msg, cMsg);
    }
}


#undef __EXPORT__