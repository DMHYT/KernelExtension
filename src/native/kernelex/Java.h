#pragma once

#include <jni.h>

namespace Java {

    JNIEnv *attach();

    void init(JavaVM *javaVM);
    
}
