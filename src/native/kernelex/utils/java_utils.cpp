#include <cstdlib>
#include <logger.h>
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
        JAVA_CLASS(ToolsModule, "vsdum/kex/modules/ToolsModule")
        JAVA_METHOD(ToolsModule, onBroke, "()Z")
        JAVA_METHOD(ToolsModule, modifyEnchant, "(IIIBIIJ)V")
        JAVA_METHOD(ToolsModule, onAttack, "(JJ)Z")
        JAVA_METHOD(ToolsModule, onMineBlock, "(IIIBIIJ)V")
        JAVA_METHOD(ToolsModule, onDestroy, "(IIIBIIJ)Z")
        JAVA_METHOD(ToolsModule, calcDestroyTime, "(IIIIIBFFFF)F")
        JAVA_METHOD(ToolsModule, getAttackDamageBonus, "(IIIJI)I")
        JAVA_CLASS(LootModule, "vsdum/kex/modules/LootModule")
        JAVA_METHOD(LootModule, modify, "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")
    }
    namespace ToolsModule {
        bool onBroke() {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::ToolsModule(), Cache::ToolsModule_onBroke());
        }
        void modifyEnchant(int x, int y, int z, char side, int id, int data, jlong actor) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::ToolsModule(), Cache::ToolsModule_modifyEnchant(), x, y, z, (jbyte) side, id, data, actor);
        }
        bool onAttack(jlong victim, jlong attacker) {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::ToolsModule(), Cache::ToolsModule_onAttack(), victim, attacker);
        }
        void onMineBlock(int x, int y, int z, char side, int id, int data, jlong actor) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::ToolsModule(), Cache::ToolsModule_onMineBlock(), x, y, z, (jbyte) side, id, data, actor);
        }
        bool onDestroy(int x, int y, int z, char side, int id, int data, jlong actor) {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::ToolsModule(), Cache::ToolsModule_onDestroy(), x, y, z, (jbyte) side, id, data, actor);
        }
        float calcDestroyTime(int id, int data, int x, int y, int z, char side, float baseDestroyTime, float divider, float modifier, float defaultTime) {
            return KEXJavaUtils::attach()->CallStaticFloatMethod(Cache::ToolsModule(), Cache::ToolsModule_calcDestroyTime(), id, data, x, y, z, (jbyte) side, baseDestroyTime, divider, modifier, defaultTime);
        }
        int getAttackDamageBonus(int id, int count, int data, jlong extra, int defaultValue) {
            return KEXJavaUtils::attach()->CallStaticIntMethod(Cache::ToolsModule(), Cache::ToolsModule_getAttackDamageBonus(), id, count, data, extra, defaultValue);
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