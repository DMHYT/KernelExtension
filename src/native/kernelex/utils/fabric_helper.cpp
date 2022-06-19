#include <algorithm>
#include <dlfcn.h>
#include <jni.h>
#include <string>

#include <innercore/legacy_item_registry.h>


extern "C" {
    JNIEXPORT jlong JNICALL Java_vsdum_kex_util_ItemFactoryHelper_nativeKillItem
    (JNIEnv*, jclass, jint id) {
        auto factory = LegacyItemRegistry::findFactoryById(id);
        if(factory == nullptr) return 0;
        static void* (*newErase) (int) = (void* (*) (int)) dlsym(dlopen("libinnercore.so", RTLD_LAZY), "LegacyItemRegistry_eraseFactory");
        if(newErase != nullptr) {
            newErase(id);
        } else LegacyItemRegistry::registeredFactories.erase(id);
        return (jlong) factory;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_util_ItemFactoryHelper_nativePutPropertiesToNewFactory
    (JNIEnv*, jclass, jlong ptr, jint id) {
        auto newFactory = LegacyItemRegistry::findFactoryById(id);
        if(newFactory != nullptr) {
            auto oldFactory = (LegacyItemRegistry::LegacyItemFactoryBase*) ptr;
            if(newFactory != nullptr) {
                newFactory->props = oldFactory->props;
            }
        }
    }
    JNIEXPORT jstring JNICALL Java_vsdum_kex_util_ItemFactoryHelper_nativeFactoryGetNameId
    (JNIEnv* env, jclass, jlong ptr) {
        return env->NewStringUTF(((LegacyItemRegistry::LegacyItemFactoryBase*) ptr)->nameId.c_str());
    }
    JNIEXPORT jstring JNICALL Java_vsdum_kex_util_ItemFactoryHelper_nativeFactoryGetNameToDisplay
    (JNIEnv* env, jclass, jlong ptr) {
        return env->NewStringUTF(((LegacyItemRegistry::LegacyItemFactoryBase*) ptr)->props.nameToDisplay.c_str());
    }
    JNIEXPORT jstring JNICALL Java_vsdum_kex_util_ItemFactoryHelper_nativeFactoryGetIconName
    (JNIEnv* env, jclass, jlong ptr) {
        return env->NewStringUTF(((LegacyItemRegistry::LegacyItemFactoryBase*) ptr)->props.iconName.c_str());
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_util_ItemFactoryHelper_nativeFactoryGetIconIndex
    (JNIEnv*, jclass, jlong ptr) {
        return ((LegacyItemRegistry::LegacyItemFactoryBase*) ptr)->props.iconIndex;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_util_ItemFactoryHelper_nativeFactoryGetStack
    (JNIEnv*, jclass, jlong ptr) {
        return ((LegacyItemRegistry::LegacyItemFactoryBase*) ptr)->props.stack;
    }
}