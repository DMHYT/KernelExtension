#include <jni.h>
#include <string>

#include <I18n.hpp>


extern "C" JNIEXPORT jstring JNICALL Java_vsdum_kex_natives_I18n_translate
(JNIEnv* env, jclass, jstring key) {
    const char* cKey = env->GetStringUTFChars(key, 0);
    auto translated = I18n::get(cKey);
    env->ReleaseStringUTFChars(key, cKey);
    return env->NewStringUTF(translated.c_str());
}