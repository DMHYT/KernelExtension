#pragma once

#include <jni.h>

#include "Java.h"

namespace JavaBridge {
    namespace ToolsModule {

        bool onBroke(jlong stack);
        
    }
}