#include "Java.h"

#include <cstdlib>

namespace Java {

    JavaVM *jvm = nullptr;

    JNIEnv *attach() {
        JNIEnv *env = nullptr;
        int attachStatus = jvm->GetEnv((void **) &env, JNI_VERSION_1_2);
        if (attachStatus == JNI_EDETACHED) {
            jvm->AttachCurrentThread(&env, nullptr);
        }
        return env;
    }

    void init(JavaVM *javaVM) {
        jvm = javaVM;
    }
    
}
