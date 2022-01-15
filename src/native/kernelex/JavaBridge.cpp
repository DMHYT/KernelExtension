#include "JavaBridge.h"

namespace JavaBridge {

#define DEFINE_JAVA_CLASS(name, signature) \
    jclass _##name = nullptr; \
    jclass name() { \
        if (_##name == nullptr) { \
            JNIEnv *env = Java::attach(); \
            jclass tempRef = env->FindClass(signature); \
            _##name = static_cast<jclass>(env->NewGlobalRef(tempRef)); \
            env->DeleteLocalRef(tempRef); \
        } \
        return _##name; \
    }

#define DEFINE_JAVA_METHOD(clazz, name, signature) \
    jmethodID _##clazz#_##name = nullptr; \
    jmethodID clazz#_##name() { \
        if (_##name == nullptr) { \
            _##name = Java::attach()->GetStaticMethodID( \
                    clazz(), #name, signature \
            ); \
        } \
        return _##name; \
    }

    namespace Cache {
        DEFINE_JAVA_CLASS(ToolsModule, "vsdum/kex/modules/ToolsModule")

        DEFINE_JAVA_METHOD(ToolsModule, onBroke, "(J)Z")

        DEFINE_JAVA_METHOD(ToolsModule, modifyEnchant, "(JIIIIII)V")

        DEFINE_JAVA_METHOD(ToolsModule, onAttack, "(JJJ)Z")

        DEFINE_JAVA_METHOD(ToolsModule, onMineBlock, "(JIIIIII)V")

        DEFINE_JAVA_METHOD(ToolsModule, onDestroy, "(JIIIIIIJ)Z")

        DEFINE_JAVA_METHOD(ToolsModule, calcDestroyTime, "(JIIIIIBFFFF)F")

    }

    namespace ToolsModule {

        bool onBroke(jlong stack) {
            JNIEnv *env = Java::attach();
            jclass clazz = Cache::ToolsModule();
            jmethodID method = Cache::ToolsModule_onBroke();

            return env->CallStaticBooleanMethod(clazz, method, ((jlong) stack));
        }
    }



}