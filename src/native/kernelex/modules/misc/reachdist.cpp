#include <hook.h>
#include <symbol.h>

#include "reachdist.hpp"


std::unordered_set<KEXMiscReachDistModule::ReachDistModifier*> KEXMiscReachDistModule::modifiers;
float KEXMiscReachDistModule::last = 7.0f;


float KEXMiscReachDistModule::apply(float defaultValue) {
    float result = defaultValue;
    for(const auto& modifier : modifiers) {
        if(modifier->enabled) {
            result += modifier->modifier;
        }
    }
    for(const auto& modifier : modifiers) {
        if(modifier->enabled) {
            result *= modifier->multiplier;
        }
    }
    return result;
}

void KEXMiscReachDistModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN8GameMode12getPickRangeERK9InputModeb"),
        LAMBDA((HookManager::CallbackController* controller, void* gamemode, void* inputmode, bool b), {
            float output = controller->callAndReplace<float>(gamemode, inputmode, b);
            float result = apply(output);
            last = result;
            return result;
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN8GameMode15getMaxPickRangeEv"),
        LAMBDA((HookManager::CallbackController* controller, void* gamemode), {
            controller->replace();
            return last + 1.0f;
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN8GameMode18getMaxPickRangeSqrEv"),
        LAMBDA((HookManager::CallbackController* controller, void* gamemode), {
            controller->replace();
            return last * last + 1.0f;
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

}


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_modules_misc_ReachDistanceModifier_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_misc_ReachDistanceModifier_nativeConstruct
    (JNIEnv*, jclass) {
        auto mod = new KEXMiscReachDistModule::ReachDistModifier();
        KEXMiscReachDistModule::modifiers.emplace(mod);
        return (jlong) mod;
    }
    #define __CONVERT__ ((KEXMiscReachDistModule::ReachDistModifier*) ptr)
    __EXPORT__(void, SetModifier, jfloat modifier) {
        __CONVERT__->modifier = modifier;
    }
    __EXPORT__(void, SetMultiplier, jfloat multiplier) {
        __CONVERT__->multiplier = multiplier;
    }
    __EXPORT__(void, Toggle, jboolean enable) {
        __CONVERT__->enabled = enable;
    }
    __EXPORT__(jfloat, GetModifier) {
        return __CONVERT__->modifier;
    }
    __EXPORT__(jfloat, GetMultiplier) {
        return __CONVERT__->multiplier;
    }
    __EXPORT__(jboolean, IsActive) {
        return __CONVERT__->enabled;
    }
    #undef __CONVERT__
}


#undef __EXPORT__