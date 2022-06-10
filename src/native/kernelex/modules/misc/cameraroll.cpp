#include <hook.h>
#include <symbol.h>

#include <innercore/global_context.h>

#include <CameraDirector.hpp>

#include "cameraroll.hpp"


float KEXMiscCameraRollModule::CameraRollModifier::interpolate() {
    if(modifier == modifierToUse) return modifierToUse;
    if(!interpolationEnabled) return modifier;
    float alpha = GlobalContext::getMinecraft()->getTimer()->getAlpha();
    if(lastAlpha > alpha) {
        lastAlpha = alpha;
        lastModifier = modifierToUse;
        return modifierToUse;
    }
    lastAlpha = alpha;
    modifierToUse = (1.0f - smoothing) * modifier + smoothing * lastModifier;
    lastModifier = modifierToUse;
    return modifierToUse;
}


std::unordered_set<KEXMiscCameraRollModule::CameraRollModifier*> KEXMiscCameraRollModule::modifiers;


float KEXMiscCameraRollModule::apply(float defaultValue) {
    float result = defaultValue;
    for(auto iter = modifiers.begin(); iter != modifiers.end(); iter++) {
        if((*iter)->enabled) {
            result -= (*iter)->interpolate();
        }
    }
    return result;
}


void KEXMiscCameraRollModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    HookManager::addCallback(SYMBOL("mcpe", "_ZN14CameraDirector6updateER15IClientInstanceff"), LAMBDA((CameraDirector* director), {
        Camera* camera = director->getCamera();
        Vec3 angles = camera->getEulerAngles();
        camera->setOrientation(-angles.y, -angles.x, apply(angles.z));
    }, ), HookManager::RETURN | HookManager::LISTENER);
}


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_modules_misc_CameraRollModifier_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_misc_CameraRollModifier_nativeConstruct
    (JNIEnv*, jclass) {
        KEXMiscCameraRollModule::CameraRollModifier* mod = new KEXMiscCameraRollModule::CameraRollModifier();
        KEXMiscCameraRollModule::modifiers.emplace(mod);
        return (jlong) mod;
    }
    #define CONVERT ((KEXMiscCameraRollModule::CameraRollModifier*) ptr)
    __EXPORT__(void, SetModifier, jfloat modifier) {
        CONVERT->modifier = modifier;
    }
    __EXPORT__(void, SetInterpolationEnabled, jboolean enabled) {
        CONVERT->interpolationEnabled = enabled;
    }
    __EXPORT__(void, SetSmoothing, jfloat smoothing) {
        CONVERT->smoothing = smoothing;
    }
    __EXPORT__(void, Toggle, jboolean enable) {
        CONVERT->enabled = enable;
    }
    __EXPORT__(jfloat, GetModifier) {
        return CONVERT->modifier;
    }
    __EXPORT__(jboolean, IsInterpolationEnabled) {
        return CONVERT->interpolationEnabled;
    }
    __EXPORT__(jfloat, GetSmoothing) {
        return CONVERT->smoothing;
    }
    __EXPORT__(jboolean, IsActive) {
        return CONVERT->enabled;
    }
    #undef CONVERT
}


#undef __EXPORT__