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
        JAVA_CLASS(ToolsModule, "vsdum/kex/modules/ToolsModule")
        JAVA_METHOD(ToolsModule, onBroke, "()Z")
        JAVA_METHOD(ToolsModule, calcDestroyTime, "(IIIIIBFFFF)F")
        JAVA_METHOD(ToolsModule, getAttackDamageBonus, "(IIIJI)I")
        JAVA_CLASS(LootModule, "vsdum/kex/modules/LootModule")
        JAVA_METHOD(LootModule, modify, "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")
        JAVA_CLASS(CallbacksModule, "vsdum/kex/modules/CallbacksModule")
        JAVA_METHOD(CallbacksModule, onPlayerJump, "(J)V")
        JAVA_METHOD(CallbacksModule, onGameModeChanged, "(I)V")
    }
    namespace ToolsModule {
        bool onBroke() {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::ToolsModule(), Cache::ToolsModule_onBroke());
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
    namespace CallbacksModule {
        void onPlayerJump(long long uid) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::CallbacksModule(), Cache::CallbacksModule_onPlayerJump(), (jlong) uid);
        }
        void onGameModeChanged(int mode) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::CallbacksModule(), Cache::CallbacksModule_onGameModeChanged(), mode);
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