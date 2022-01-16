#include <cstdlib>
#include "java_utils.hpp"


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

namespace KEXJavaBridge {
#define JAVA_CLASS(name, signature) \
    jclass _##name = nullptr; \
    jclass name() { \
        if(_##name == nullptr) { \
            JNIEnv* env = KEXJavaUtils::attach(); \
            jclass tempRef = env->FindClass(signature); \
            _##name = static_cast<jclass>(env->NewGlobalRef(tempRef)); \
            env->DeleteLocalRef(tempRef); \
        } \
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
        JAVA_METHOD(ToolsModule, onBroke, "(J)Z")
        JAVA_METHOD(ToolsModule, modifyEnchant, "(JIIIBII)V")
        JAVA_METHOD(ToolsModule, onAttack, "(JJJ)Z")
        JAVA_METHOD(ToolsModule, onMineBlock, "(JIIIBII)V")
        JAVA_METHOD(ToolsModule, onDestroy, "(JIIIBIIJ)Z")
        JAVA_METHOD(ToolsModule, calcDestroyTime, "(JIIIIIBFFFF)F")
        JAVA_CLASS(LootModule, "vsdum/kex/modules/LootModule")
        JAVA_METHOD(LootModule, modify, "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")
    }
    namespace ToolsModule {
        bool onBroke(jlong stack) {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::ToolsModule(), Cache::ToolsModule_onBroke(), stack);
        }
        void modifyEnchant(jlong stack, int x, int y, int z, char side, int id, int data) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::ToolsModule(), Cache::ToolsModule_modifyEnchant(), stack, x, y, z, (jbyte) side, id, data);
        }
        bool onAttack(jlong stack, jlong victim, jlong attacker) {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::ToolsModule(), Cache::ToolsModule_onAttack(), stack, victim, attacker);
        }
        void onMineBlock(jlong stack, int x, int y, int z, char side, int id, int data) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::ToolsModule(), Cache::ToolsModule_onMineBlock(), stack, x, y, z, (jbyte) side, id, data);
        }
        bool onDestroy(jlong stack, int x, int y, int z, char side, int id, int data, jlong actor) {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::ToolsModule(), Cache::ToolsModule_onDestroy(), stack, x, y, z, (jbyte) side, id, data, actor);
        }
        float calcDestroyTime(jlong stack, int id, int data, int x, int y, int z, char side, float baseDestroyTime, float divider, float modifier, float defaultTime) {
            return KEXJavaUtils::attach()->CallStaticFloatMethod(Cache::ToolsModule(), Cache::ToolsModule_calcDestroyTime(), stack, id, data, x, y, z, (jbyte) side, baseDestroyTime, divider, modifier, defaultTime);
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