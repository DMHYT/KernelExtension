#include <cstdlib>

#include "java_utils.hpp"


namespace KEXJavaBridge {
#define JAVA_CLASS(name, signature) \
    jclass _##name = nullptr; \
    jclass name() { \
        return _##name; \
    } \
    jclass name(JNIEnv* env) { \
        jclass tempRef = env->FindClass(signature); \
        _##name = static_cast<jclass>(env->NewGlobalRef(tempRef)); \
        env->DeleteLocalRef(tempRef); \
        return _##name; \
    }
#define JAVA_METHOD(clazz, name, signature) \
    jmethodID _##clazz##_##name = nullptr; \
    jmethodID clazz##_##name() { \
        if(_##clazz##_##name == nullptr) { \
            _##clazz##_##name = KEXJavaUtils::attach()->GetStaticMethodID( \
                clazz(), #name, signature \
            ); \
        } \
        return _##clazz##_##name; \
    }
    namespace Cache {
        JAVA_CLASS(KernelExtension, "vsdum/kex/KernelExtension")
        JAVA_METHOD(KernelExtension, setMinecraftTextboxText, "(Ljava/lang/String;)V")
        JAVA_CLASS(CustomToolEvents, "vsdum/kex/modules/tools/CustomToolEvents")
        JAVA_METHOD(CustomToolEvents, onBroke, "()Z")
        JAVA_METHOD(CustomToolEvents, calcDestroyTime, "(IIIIIBFFFF)F")
        JAVA_METHOD(CustomToolEvents, getAttackDamageBonus, "(IIIJI)I")
        JAVA_CLASS(LootModule, "vsdum/kex/modules/LootModule")
        JAVA_METHOD(LootModule, modify, "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")
        JAVA_METHOD(LootModule, onDrop, "(Ljava/lang/String;JIJ)V")
        JAVA_METHOD(LootModule, applyCustomLootFunction, "(Ljava/lang/String;Ljava/lang/String;JJ)V")
        JAVA_CLASS(CallbacksModule, "vsdum/kex/modules/CallbacksModule")
        JAVA_CLASS(ItemsModule, "vsdum/kex/modules/ItemsModule")
        JAVA_METHOD(ItemsModule, getUseDurationDynamic, "(J)I")
        JAVA_METHOD(ItemsModule, appendFormattedHovertext, "(JJLjava/lang/String;)Ljava/lang/String;")
        JAVA_METHOD(ItemsModule, getDynamicFoodValues, "(JJ)V")
        JAVA_CLASS(DamageModule, "vsdum/kex/modules/DamageModule")
        JAVA_METHOD(DamageModule, getDeathMessage, "(JLjava/lang/String;J)Ljava/lang/String;")
        JAVA_CLASS(CommandsModule, "vsdum/kex/modules/CommandsModule")
        JAVA_METHOD(CommandsModule, callAPICommand, "(Ljava/lang/String;JIJJ[Z)V")
        JAVA_CLASS(I18n, "vsdum/kex/natives/I18n")
        JAVA_METHOD(I18n, onChooseLanguage, "(JLjava/lang/String;)V")
    }
    namespace KernelExtension {
        void setMinecraftTextboxText(const char* text) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jText = env->NewStringUTF(text);
            env->CallStaticVoidMethod(Cache::KernelExtension(), Cache::KernelExtension_setMinecraftTextboxText(), jText);
            env->DeleteLocalRef(jText);
        }
    }
    namespace CustomToolEvents {
        bool onBroke() {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::CustomToolEvents(), Cache::CustomToolEvents_onBroke());
        }
        float calcDestroyTime(int id, int data, int x, int y, int z, char side, float baseDestroyTime, float divider, float modifier, float defaultTime) {
            return KEXJavaUtils::attach()->CallStaticFloatMethod(Cache::CustomToolEvents(), Cache::CustomToolEvents_calcDestroyTime(), id, data, x, y, z, (jbyte) side, baseDestroyTime, divider, modifier, defaultTime);
        }
        int getAttackDamageBonus(int id, int count, int data, jlong extra, int defaultValue) {
            return KEXJavaUtils::attach()->CallStaticIntMethod(Cache::CustomToolEvents(), Cache::CustomToolEvents_getAttackDamageBonus(), id, count, data, extra, defaultValue);
        }
    }
    namespace LootModule {
        jstring modify(const char* tableName, const char* json) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jTableName = env->NewStringUTF(tableName);
            jstring jJson = env->NewStringUTF(json);
            jstring result = (jstring) env->CallStaticObjectMethod(Cache::LootModule(), Cache::LootModule_modify(), jTableName, jJson);
            env->DeleteLocalRef(jTableName);
            env->DeleteLocalRef(jJson);
            return result;
        }
        void onDrop(const char* tableName, jlong vectorPtr, jint vectorSize, jlong contextPtr) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jTableName = env->NewStringUTF(tableName);
            env->CallStaticVoidMethod(Cache::LootModule(), Cache::LootModule_onDrop(), jTableName, vectorPtr, vectorSize, contextPtr);
            env->DeleteLocalRef(jTableName);
        }
        void applyCustomLootFunction(const char* functionName, const char* jsonString, jlong stackPtr, jlong contextPtr) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jFunctionName = env->NewStringUTF(functionName);
            jstring jJsonString = env->NewStringUTF(jsonString);
            env->CallStaticVoidMethod(Cache::LootModule(), Cache::LootModule_applyCustomLootFunction(), jFunctionName, jJsonString, stackPtr, contextPtr);
            env->DeleteLocalRef(jFunctionName);
            env->DeleteLocalRef(jJsonString);
        }
    }
    namespace ItemsModule {
        int getUseDurationDynamic(jlong stackPtr) {
            return KEXJavaUtils::attach()->CallStaticIntMethod(Cache::ItemsModule(), Cache::ItemsModule_getUseDurationDynamic(), stackPtr);
        }
        jstring appendFormattedHovertext(jlong stackPtr, jlong levelPtr, const char* text) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jText = env->NewStringUTF(text);
            jstring result = (jstring) env->CallStaticObjectMethod(Cache::ItemsModule(), Cache::ItemsModule_appendFormattedHovertext(), stackPtr, levelPtr, jText);
            env->DeleteLocalRef(jText);
            return result;
        }
        void getDynamicFoodValues(jlong stackPtr, jlong foodPtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::ItemsModule(), Cache::ItemsModule_getDynamicFoodValues(), stackPtr, foodPtr);
        }
    }
    namespace DamageModule {
        jstring getDeathMessage(jlong sourcePtr, const char* nickname, jlong actorPtr) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jNickname = env->NewStringUTF(nickname);
            jstring result = (jstring) env->CallStaticObjectMethod(Cache::DamageModule(), Cache::DamageModule_getDeathMessage(), sourcePtr, jNickname, actorPtr);
            env->DeleteLocalRef(jNickname);
            return result;
        }
    }
    namespace CommandsModule {
        void callAPICommand(const char* commandName, jlong commandPointer, jint overloadIndex, jlong originPtr, jlong outputPtr, int paramsCount) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jCommandName = env->NewStringUTF(commandName);
            jbooleanArray paramsPresence = env->NewBooleanArray(paramsCount);
            jboolean fill[paramsCount];
            for(int i = 0; i < paramsCount; i++) {
                fill[i] = *(bool*) ((char*) commandPointer + 2047 - i);
            }
            env->SetBooleanArrayRegion(paramsPresence, 0, paramsCount, fill);
            env->CallStaticVoidMethod(Cache::CommandsModule(), Cache::CommandsModule_callAPICommand(), jCommandName, commandPointer, overloadIndex, originPtr, outputPtr, paramsPresence);
            env->DeleteLocalRef(jCommandName);
            env->DeleteLocalRef(paramsPresence);
        }
    }
    namespace I18n {
        void onChooseLanguage(jlong localizationPtr, const char* languageCode) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jLanguageCode = env->NewStringUTF(languageCode);
            env->CallStaticVoidMethod(Cache::I18n(), Cache::I18n_onChooseLanguage(), localizationPtr, jLanguageCode);
            env->DeleteLocalRef(jLanguageCode);
        }
    }
}


namespace KEXJavaUtils {
    JavaVM* jvm = nullptr;
    JNIEnv* attach() {
        JNIEnv* env = nullptr;
        int attachStatus = jvm->GetEnv((void**) &env, JNI_VERSION_1_4);
        if(attachStatus == JNI_EDETACHED) {
            jvm->AttachCurrentThread(&env, nullptr);
        }
        return env;
    }
    void init(JavaVM* vm) {
        jvm = vm;
    }
}