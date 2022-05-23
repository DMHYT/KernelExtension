#include <hook.h>
#include <symbol.h>

#include "reachdist.hpp"


std::unordered_set<KEXMiscReachDistModule::ReachDistModifier*> KEXMiscReachDistModule::modifiers;
float KEXMiscReachDistModule::last = 7.0f;


float KEXMiscReachDistModule::apply(float defaultValue) {
    float result = defaultValue;
    for(auto iter = modifiers.begin(); iter != modifiers.end(); iter++) {
        if((*iter)->isActive()) {
            result += (*iter)->getModifier();
        } 
    }
    for(auto iter = modifiers.begin(); iter != modifiers.end(); iter++) {
        if((*iter)->isActive()) {
            result *= (*iter)->getMultiplier();
        }
    }
    return result;
}

#include <logger.h>

void KEXMiscReachDistModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    HookManager::addCallback(SYMBOL("mcpe", "_ZN8GameMode12getPickRangeERK9InputModeb"), LAMBDA((HookManager::CallbackController* controller, void* gamemode, void* inputmode, bool b), {
        float output = controller->callAndReplace<float>(gamemode, inputmode, b);
        float result = apply(output);
        last = result;
        return result;
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN8GameMode15getMaxPickRangeEv"), LAMBDA((HookManager::CallbackController* controller, void* gamemode), {
        controller->replace();
        return last + 1.0f;
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN8GameMode18getMaxPickRangeSqrEv"), LAMBDA((HookManager::CallbackController* controller, void* gamemode), {
        controller->replace();
        return last * last + 1.0f;
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
}


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_modules_misc_ReachDistanceModifier_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_misc_ReachDistanceModifier_nativeConstruct
    (JNIEnv*, jclass) {
        KEXMiscReachDistModule::ReachDistModifier* mod = new KEXMiscReachDistModule::ReachDistModifier();
        KEXMiscReachDistModule::modifiers.emplace(mod);
        return (jlong) mod;
    }
    __EXPORT__(void, SetModifier, jfloat modifier) {
        ((KEXMiscReachDistModule::ReachDistModifier*) ptr)->setModifier(modifier);
    }
    __EXPORT__(void, SetMultiplier, jfloat multiplier) {
        ((KEXMiscReachDistModule::ReachDistModifier*) ptr)->setMultiplier(multiplier);
    }
    __EXPORT__(void, Toggle, jboolean enable) {
        ((KEXMiscReachDistModule::ReachDistModifier*) ptr)->toggle(enable);
    }
    __EXPORT__(jfloat, GetModifier) {
        return ((KEXMiscReachDistModule::ReachDistModifier*) ptr)->getModifier();
    }
    __EXPORT__(jfloat, GetMultiplier) {
        return ((KEXMiscReachDistModule::ReachDistModifier*) ptr)->getMultiplier();
    }
    __EXPORT__(jboolean, IsActive) {
        return ((KEXMiscReachDistModule::ReachDistModifier*) ptr)->isActive();
    }
}


#undef __EXPORT__