#include <algorithm>
#include <string>
#include <jni.h>
#include <innercore/legacy_item_registry.h>


extern "C" {
    JNIEXPORT jobject JNICALL Java_vsdum_kex_util_nativeKillItem
    (JNIEnv* env, jclass, jint id) {
        auto found = LegacyItemRegistry::registeredFactories.find(id);
        if(found == LegacyItemRegistry::registeredFactories.end()) return NULL;
        LegacyItemRegistry::LegacyItemFactoryBase* factory = found->second;
        if(factory == nullptr) {
            LegacyItemRegistry::registeredFactories.erase(id);
            return NULL;
        }
        jclass clazz = env->FindClass("vsdum/kex/util/ItemFabricHelper$ItemFactoryInterface");
        jmethodID constructor = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIIIIIII[IZZZZZZZLjava/lang/String;)V");
        int size = factory->props.repairItemIds.size();
        jintArray repairItemIds = env->NewIntArray(size);
        jint fill[size];
        for(int i = 0; i < size; ++i) {
            fill[i] = factory->props.repairItemIds.at(i);
        }
        factory->props.repairItemIds.clear();
        env->SetIntArrayRegion(repairItemIds, 0, size, fill);
        jobject result = env->NewObject(clazz, constructor, env->NewStringUTF(factory->nameId.c_str()), env->NewStringUTF(factory->props.nameToDisplay.c_str()), env->NewStringUTF(factory->props.iconName.c_str()), factory->props.iconIndex, factory->props.durability, factory->props.stack, factory->props.animationId, factory->props.maxUseDuration, factory->props.creativeCategory, factory->props.enchantType, factory->props.enchantValue, repairItemIds, factory->props.isGlint, factory->props.isHandEquipped, factory->props.isLiquidClip, factory->props.isIconControlled, factory->props.isIconAnimated, factory->props.isArmorDamageable, factory->props.isStackedByData, factory->props.isAllowedInOffhand, env->NewStringUTF(factory->props.initProperties.c_str()));
        return result;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_util_nativeSetItem
    (JNIEnv* env, jclass, jint id, jstring nameId, jstring nameToDisplay, jstring iconName, jint iconIndex, jint durability, jint stack, jint animationId, jint maxUseDuration, jint creativeCategory, jint enchantType, jint enchantValue, jintArray repairItemIds, jboolean isGlint, jboolean isHandEquipped, jboolean isLiquidClip, jboolean isIconControlled, jboolean isIconAnimated, jboolean isArmorDamageable, jboolean isStackedByData, jboolean isAllowedInOffhand, jstring initProperties) {
        LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(id);
        if(factory != nullptr) {
            const char* cNameId = env->GetStringUTFChars(nameId, 0);
            const char* cNameToDisplay = env->GetStringUTFChars(nameToDisplay, 0);
            const char* cIconName = env->GetStringUTFChars(iconName, 0);
            const char* cInitProperties = env->GetStringUTFChars(initProperties, 0);
            factory->nameId = std::string(cNameId);
            factory->props.nameToDisplay = std::string(cNameToDisplay);
            factory->props.iconName = std::string(cIconName);
            factory->props.initProperties = std::string(cInitProperties);
            env->ReleaseStringUTFChars(nameId, cNameId);
            env->ReleaseStringUTFChars(nameToDisplay, cNameToDisplay);
            env->ReleaseStringUTFChars(iconName, cIconName);
            env->ReleaseStringUTFChars(initProperties, cInitProperties);
            factory->props.iconIndex = iconIndex;
            factory->props.durability = durability;
            factory->props.stack = stack;
            factory->props.animationId = animationId;
            factory->props.maxUseDuration = maxUseDuration;
            factory->props.creativeCategory = creativeCategory;
            factory->props.enchantType = enchantType;
            factory->props.enchantValue = enchantValue;
            jsize repairItemIdsLen = env->GetArrayLength(repairItemIds);
            jint* repairItemIdsEl = env->GetIntArrayElements(repairItemIds, 0);
            for(int i = 0; i < repairItemIdsLen; i++) {
                if(std::find(factory->props.repairItemIds.begin(), factory->props.repairItemIds.end(), repairItemIdsEl[i]) == factory->props.repairItemIds.end()) {
                    factory->props.repairItemIds.push_back(repairItemIdsEl[i]);
                }
            }
            env->ReleaseIntArrayElements(repairItemIds, repairItemIdsEl, JNI_ABORT);
            factory->props.isGlint = isGlint;
            factory->props.isHandEquipped = isHandEquipped;
            factory->props.isLiquidClip = isLiquidClip;
            factory->props.isIconControlled = isIconControlled;
            factory->props.isIconAnimated = isIconAnimated;
            factory->props.isArmorDamageable = isArmorDamageable;
            factory->props.isStackedByData = isStackedByData;
            factory->props.isAllowedInOffhand = isAllowedInOffhand;
        }
    }
}