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
        JAVA_METHOD(LootModule, customLootConditionApplies, "(Ljava/lang/String;Ljava/lang/String;J)Z")
        JAVA_METHOD(LootModule, applyCustomLootFunction, "(Ljava/lang/String;Ljava/lang/String;JJ)V")
        JAVA_CLASS(CallbacksModule, "vsdum/kex/modules/CallbacksModule")
        JAVA_CLASS(ItemsModule, "vsdum/kex/modules/ItemsModule")
        JAVA_METHOD(ItemsModule, getUseDurationDynamic, "(J)I")
        JAVA_METHOD(ItemsModule, appendFormattedHovertext, "(JJLjava/lang/String;)Ljava/lang/String;")
        JAVA_METHOD(ItemsModule, getDynamicFoodValues, "(JJ)V")
        JAVA_CLASS(BlocksModule, "vsdum/kex/modules/BlocksModule")
        JAVA_METHOD(BlocksModule, getComparatorSignal, "(JJIIII)I")
        JAVA_METHOD(BlocksModule, onStepOn, "(IIIIJ)V")
        JAVA_METHOD(BlocksModule, onStepOff, "(IIIIJ)V")
        JAVA_CLASS(DamageModule, "vsdum/kex/modules/DamageModule")
        JAVA_METHOD(DamageModule, getDeathMessage, "(JLjava/lang/String;J)Ljava/lang/String;")
        JAVA_CLASS(CommandsModule, "vsdum/kex/modules/CommandsModule")
        JAVA_METHOD(CommandsModule, callAPICommand, "(Ljava/lang/String;JIJJ[Z)V")
        JAVA_CLASS(I18n, "vsdum/kex/natives/I18n")
        JAVA_METHOD(I18n, onChooseLanguage, "(JLjava/lang/String;)V")
        JAVA_CLASS(TileEntityEvents, "vsdum/kex/modules/tileentity/TileEntityEvents")
        JAVA_METHOD(TileEntityEvents, construct, "(J)V")
        JAVA_METHOD(TileEntityEvents, load, "(JJ)V")
        JAVA_METHOD(TileEntityEvents, save, "(JJ)Z")
        JAVA_METHOD(TileEntityEvents, tick, "(J)V")
        JAVA_METHOD(TileEntityEvents, isFinished, "(J)Z")
        JAVA_METHOD(TileEntityEvents, onChanged, "(J)V")
        JAVA_METHOD(TileEntityEvents, isMovable, "(J)Z")
        JAVA_METHOD(TileEntityEvents, onPlace, "(J)V")
        JAVA_METHOD(TileEntityEvents, onMove, "(J)V")
        JAVA_METHOD(TileEntityEvents, onRemoved, "(J)V")
        JAVA_METHOD(TileEntityEvents, triggerEvent, "(JII)V")
        JAVA_METHOD(TileEntityEvents, onNeighborChanged, "(JIII)V")
        JAVA_METHOD(TileEntityEvents, getCustomName, "(J)Ljava/lang/String;")
        JAVA_METHOD(TileEntityEvents, getName, "(J)Ljava/lang/String;")
        JAVA_METHOD(TileEntityEvents, setCustomName, "(JLjava/lang/String;)V")
        JAVA_METHOD(TileEntityEvents, onChunkLoaded, "(J)V")
        JAVA_METHOD(TileEntityEvents, onChunkUnloaded, "(J)V")
        JAVA_METHOD(TileEntityEvents, onUse, "(JJBFFF)Z")
        JAVA_METHOD(TileEntityEvents, reportTileSideAndDimension, "(JZI)V")
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
        bool customLootConditionApplies(const char* conditionName, const char* jsonString, jlong contextPtr) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jConditionName = env->NewStringUTF(conditionName);
            jstring jJsonString = env->NewStringUTF(jsonString);
            bool result = env->CallStaticBooleanMethod(Cache::LootModule(), Cache::LootModule_customLootConditionApplies(), jConditionName, jJsonString, contextPtr);
            env->DeleteLocalRef(jConditionName);
            env->DeleteLocalRef(jJsonString);
            return result;
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
    namespace BlocksModule {
        int getComparatorSignal(jlong blockLong, jlong blockSourcePtr, jint x, jint y, jint z, jint side) {
            return KEXJavaUtils::attach()->CallStaticIntMethod(Cache::BlocksModule(), Cache::BlocksModule_getComparatorSignal(), blockLong, blockSourcePtr, x, y, z, side);
        }
        void onStepOn(jint id, jint x, jint y, jint z, jlong entity) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::BlocksModule(), Cache::BlocksModule_onStepOn(), id, x, y, z, entity);
        }
        void onStepOff(jint id, jint x, jint y, jint z, jlong entity) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::BlocksModule(), Cache::BlocksModule_onStepOff(), id, x, y, z, entity);
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
    namespace TileEntityEvents {
        void construct(jlong tilePtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_construct(), tilePtr);
        }
        void load(jlong tilePtr, jlong tagPtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_load(), tilePtr, tagPtr);
        }
        bool save(jlong tilePtr, jlong tagPtr) {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_save(), tilePtr, tagPtr);
        }
        void tick(jlong tilePtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_tick(), tilePtr);
        }
        bool isFinished(jlong tilePtr) {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_isFinished(), tilePtr);
        }
        void onChanged(jlong tilePtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_onChanged(), tilePtr);
        }
        bool isMovable(jlong tilePtr) {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_isMovable(), tilePtr);
        }
        void onPlace(jlong tilePtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_onPlace(), tilePtr);
        }
        void onMove(jlong tilePtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_onMove(), tilePtr);
        }
        void onRemoved(jlong tilePtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_onRemoved(), tilePtr);
        }
        void triggerEvent(jlong tilePtr, int id, int type) {
            return KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_triggerEvent(), tilePtr, id, type);
        }
        void onNeighborChanged(jlong tilePtr, int changedX, int changedY, int changedZ) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_onNeighborChanged(), tilePtr, changedX, changedY, changedZ);
        }
        jstring getCustomName(jlong tilePtr) {
            return (jstring) KEXJavaUtils::attach()->CallStaticObjectMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_getCustomName(), tilePtr);
        }
        jstring getName(jlong tilePtr) {
            return (jstring) KEXJavaUtils::attach()->CallStaticObjectMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_getName(), tilePtr);
        }
        void setCustomName(jlong tilePtr, const char* customName) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring jCustomName = env->NewStringUTF(customName);
            env->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_setCustomName(), tilePtr, jCustomName);
            env->DeleteLocalRef(jCustomName);
        }
        void onChunkLoaded(jlong tilePtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_onChunkLoaded(), tilePtr);
        }
        void onChunkUnloaded(jlong tilePtr) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_onChunkUnloaded(), tilePtr);
        }
        bool onUse(jlong tilePtr, jlong playerUid, char side, float vecX, float vecY, float vecZ) {
            return KEXJavaUtils::attach()->CallStaticBooleanMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_onUse(), tilePtr, playerUid, side, vecX, vecY, vecZ);
        }
        void reportTileSideAndDimension(jlong tilePtr, bool client, int dimension) {
            KEXJavaUtils::attach()->CallStaticVoidMethod(Cache::TileEntityEvents(), Cache::TileEntityEvents_reportTileSideAndDimension(), tilePtr, client, dimension);
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