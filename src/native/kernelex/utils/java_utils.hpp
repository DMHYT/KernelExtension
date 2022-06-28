#include <stl/vector>
#include <stl/string>
#include <stl.h>

#include <jni.h>

#ifndef KEX_UTILS_JAVA_UTILS_HPP
#define KEX_UTILS_JAVA_UTILS_HPP


namespace KEXJavaUtils {
    JNIEnv* attach();
    void init(JavaVM* vm);
}

namespace KEXJavaBridge {
    namespace Cache {
        jclass KernelExtension(JNIEnv* env);
        jclass CustomToolEvents(JNIEnv* env);
        jclass LootModule(JNIEnv* env);
        jclass CallbacksModule(JNIEnv* env);
        jclass CallbacksModule();
        jclass ItemsModule(JNIEnv* env);
        jclass DamageModule(JNIEnv* env);
        jclass CommandsModule(JNIEnv* env);
    }
    namespace KernelExtension {
        void setMinecraftTextboxText(const char* text);
    }
    namespace CustomToolEvents {
        bool onBroke();
        float calcDestroyTime(int id, int data, int x, int y, int z, char side, float baseDestroyTime, float divider, float modifier, float defaultTime);
        int getAttackDamageBonus(int id, int count, int data, jlong extra, int defaultValue);
    }
    namespace LootModule {
        jstring modify(const char* tableName, const char* json);
        void onDrop(const char* tableName, jlong vectorPtr, jint vectorSize, jlong contextPtr);
        void applyCustomLootFunction(const char* functionName, const char* jsonString, jlong stackPtr, jlong contextPtr);
    }
    namespace CallbacksModule {
        void onPlayerJump(long long uid);
        void onGameModeChanged(int mode);
    }
    namespace ItemsModule {
        int getUseDurationDynamic(jlong stackPtr);
        jstring appendFormattedHovertext(jlong stackPtr, jlong levelPtr, const char* text);
        void getDynamicFoodValues(jlong stackPtr, jlong foodPtr);
    }
    namespace DamageModule {
        jstring getDeathMessage(jlong sourcePtr, const char* nickname, jlong actorPtr);
        jstring translateAndFormatDeathMessage(const char* causeName, const stl::vector<stl::string>& formatData);
    }
    namespace CommandsModule {
        void callAPICommand(const char* commandName, jlong commandPointer, jint overloadIndex, jlong originPtr, jlong outputPtr, int paramsCount);
        jstring translateCommandDescription(const char* commandName);
    }
}


#endif //KEX_UTILS_JAVA_UTILS_HPP