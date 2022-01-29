#include <jni.h>

#ifndef KEX_UTILS_JAVA_UTILS_HPP
#define KEX_UTILS_JAVA_UTILS_HPP


namespace KEXJavaUtils {
    JNIEnv* attach();
    void init(JavaVM* vm);
}

namespace KEXJavaBridge {
    namespace Cache {
        jclass ToolsModule(JNIEnv* env);
        jclass LootModule(JNIEnv* env);
    }
    namespace ToolsModule {
        bool onBroke(jlong stack);
        void modifyEnchant(jlong stack, int x, int y, int z, char side, int id, int data);
        bool onAttack(jlong stack, jlong victim, jlong attacker);
        void onMineBlock(jlong stack, int x, int y, int z, char side, int id, int data);
        bool onDestroy(jlong stack, int x, int y, int z, char side, int id, int data, jlong actor);
        float calcDestroyTime(jlong stack, int id, int data, int x, int y, int z, char side, float baseDestroyTime, float divider, float modifier, float defaultTime);
    }
    namespace LootModule {
        jstring modify(const char* tableName, const char* json);
    }
}


#endif //KEX_UTILS_JAVA_UTILS_HPP