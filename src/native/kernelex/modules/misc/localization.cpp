#include <jni.h>

#include <hook.h>
#include <symbol.h>

#include <Localization.hpp>
#include <I18n.hpp>

#include "../../utils/java_utils.hpp"
#include "localization.hpp"


void KEXMiscLocalizationModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN4I18n14chooseLanguageERK12Localization"),
        LAMBDA((const Localization& loc), {
            KEXJavaBridge::I18n::onChooseLanguage((jlong) &loc, loc.getFullLanguageCode().c_str());
        }, ),
        HookManager::RETURN | HookManager::LISTENER
    );

}


extern "C" {
    JNIEXPORT jstring JNICALL Java_vsdum_kex_natives_I18n_translate
    (JNIEnv* env, jclass, jstring key) {
        const char* cKey = env->GetStringUTFChars(key, 0);
        auto translated = I18n::get(cKey);
        env->ReleaseStringUTFChars(key, cKey);
        return env->NewStringUTF(translated.c_str());
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_natives_I18n_append
    (JNIEnv* env, jclass, jlong localizationPtr, jstring content) {
        const char* cContent = env->GetStringUTFChars(content, 0);
        auto localization = (Localization*) localizationPtr;
        localization->appendTranslations(cContent, {}, {}, "");
        env->ReleaseStringUTFChars(content, cContent);
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_I18n_getCurrent
    (JNIEnv*, jclass) {
        auto current = I18n::getCurrentLanguage();
        if(current == nullptr) return 0;
        return (jlong) current;
    }
} 