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
        jclass CallbacksModule(JNIEnv* env);
    }
    namespace ToolsModule {
        bool onBroke();
        float calcDestroyTime(int id, int data, int x, int y, int z, char side, float baseDestroyTime, float divider, float modifier, float defaultTime);
        int getAttackDamageBonus(int id, int count, int data, jlong extra, int defaultValue);
    }
    namespace LootModule {
        jstring modify(const char* tableName, const char* json);
        void onDrop(const char* tableName, jlong vectorPtr, jint vectorSize, jlong contextPtr);
    }
    namespace CallbacksModule {
        void onPlayerJump(long long uid);
        void onGameModeChanged(int mode);
    }
}


#endif //KEX_UTILS_JAVA_UTILS_HPP