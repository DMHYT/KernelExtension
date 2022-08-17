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
        jclass I18n(JNIEnv* env);
        jclass TileEntityEvents(JNIEnv* env);
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
    namespace ItemsModule {
        int getUseDurationDynamic(jlong stackPtr);
        jstring appendFormattedHovertext(jlong stackPtr, jlong levelPtr, const char* text);
        void getDynamicFoodValues(jlong stackPtr, jlong foodPtr);
    }
    namespace DamageModule {
        jstring getDeathMessage(jlong sourcePtr, const char* nickname, jlong actorPtr);
    }
    namespace CommandsModule {
        void callAPICommand(const char* commandName, jlong commandPointer, jint overloadIndex, jlong originPtr, jlong outputPtr, int paramsCount);
    }
    namespace I18n {
        void onChooseLanguage(jlong localizationPtr, const char* languageCode);
    }
    namespace TileEntityEvents {
        void construct(jlong tilePtr);
        void load(jlong tilePtr, jlong tagPtr);
        bool save(jlong tilePtr, jlong tagPtr);
        void tick(jlong tilePtr);
        bool isFinished(jlong tilePtr);
        void onChanged(jlong tilePtr);
        bool isMovable(jlong tilePtr);
        void onPlace(jlong tilePtr);
        void onMove(jlong tilePtr);
        void onRemoved(jlong tilePtr);
        void triggerEvent(jlong tilePtr, int id, int type);
        void onNeighborChanged(jlong tilePtr, int changedX, int changedY, int changedZ);
        jstring getCustomName(jlong tilePtr);
        jstring getName(jlong tilePtr);
        void setCustomName(jlong tilePtr, const char* customName);
        void onChunkLoaded(jlong tilePtr);
        void onChunkUnloaded(jlong tilePtr);
        bool onUse(jlong tilePtr, jlong playerUid, char side, float vecX, float vecY, float vecZ);
        void reportTileSideAndDimension(jlong tilePtr, bool client, int dimension);
    }
}


#endif //KEX_UTILS_JAVA_UTILS_HPP