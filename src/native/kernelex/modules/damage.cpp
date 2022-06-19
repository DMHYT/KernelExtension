#include <jni.h>

#include <hook.h>
#include <symbol.h>

#include <commontypes.hpp>

#include <BlockSource.hpp>
#include <ActorUniqueID.hpp>
#include <Actor.hpp>

#include "../utils/java_utils.hpp"
#include "damage.hpp"


std::unordered_map<int, std::string> KEXDamageModule::causeToCauseName {
    { -1, "none" },
    { 0, "override" },
    { 1, "contact" },
    { 2, "entity_attack" },
    { 3, "projectile" },
    { 4, "suffocation" },
    { 5, "fall" },
    { 6, "fire" },
    { 7, "fire_tick" },
    { 8, "lava" },
    { 9, "drowning" },
    { 10, "block_explosion" },
    { 11, "entity_explosion" },
    { 12, "void" },
    { 13, "suicide" },
    { 14, "magic" },
    { 15, "wither" },
    { 16, "starve" },
    { 17, "anvil" },
    { 18, "thorns" },
    { 19, "falling_block" },
    { 20, "piston" },
    { 21, "fly_into_wall" },
    { 22, "magma" },
    { 23, "fireworks" },
    { 24, "lightning" },
    { 25, "charging" },
    { 26, "temperature" },
    { 31, "all" }
};

std::unordered_map<std::string, int> KEXDamageModule::causeNameToCause {
    { "none", -1 },
    { "override", 0 },
    { "contact", 1 },
    { "entity_attack", 2 },
    { "projectile", 3 },
    { "suffocation", 4 },
    { "fall", 5 },
    { "fire", 6 },
    { "fire_tick", 7 },
    { "lava", 8 },
    { "drowning", 9 },
    { "block_explosion", 10 },
    { "entity_explosion", 11 },
    { "void", 12 },
    { "suicide", 13 },
    { "magic", 14 },
    { "wither", 15 },
    { "starve", 16 },
    { "anvil", 17 },
    { "thorns", 18 },
    { "falling_block", 19 },
    { "piston", 20 },
    { "fly_into_wall", 21 },
    { "magma", 22 },
    { "fireworks", 23 },
    { "lightning", 24 },
    { "charging", 25 },
    { "temperature", 26 },
    { "all", 31 }
};

std::unordered_set<int> KEXDamageModule::fireCauses { 6, 7, 8, 22 };
std::unordered_set<int> KEXDamageModule::customTranslationCallbacks;
int KEXDamageModule::nextCustomCauseId = 100;

#include <logger.h>

void KEXDamageModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    HookManager::addCallback(SYMBOL("mcpe", "_ZN17ActorDamageSource11lookupCauseERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE"), LAMBDA((HookManager::CallbackController* controller, const std::__ndk1::string& causeName), {
        controller->replace();
        auto found = causeNameToCause.find(causeName.c_str());
        if(found == causeNameToCause.end()) return -1;
        return found->second;
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN17ActorDamageSource15lookupCauseNameE16ActorDamageCause"), LAMBDA((HookManager::CallbackController* controller, std::__ndk1::string* result, int cause), {
        controller->replace();
        auto found = causeToCauseName.find(cause);
        if(found == causeToCauseName.end()) *result = "none";
        *result = found->second.c_str();
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK17ActorDamageSource6isFireEv"), LAMBDA((HookManager::CallbackController* controller, ActorDamageSource* source), {
        controller->replace();
        return fireCauses.find((int) source->getCause()) != fireCauses.end();
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZNK17ActorDamageSource15getDeathMessageENSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEP5Actor"), LAMBDA((std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>>* result, ActorDamageSource* source, std::__ndk1::string str, Actor* actor), {
        int cause = (int) source->getCause();
        if(cause >= 100) {
            if(customTranslationCallbacks.find(cause) != customTranslationCallbacks.end()) {
                JNIEnv* env = KEXJavaUtils::attach();
                jstring output = KEXJavaBridge::DamageModule::getDeathMessage((jlong) source, str.c_str(), (jlong) actor->getUniqueID()->id);
                const char* cOutput = env->GetStringUTFChars(output, 0);
                result->first = cOutput;
                env->ReleaseStringUTFChars(output, cOutput);
                env->DeleteLocalRef(output);
            } else {
                result->first = "death.kex." + ActorDamageSource::lookupCauseName((ActorDamageCause) cause);
            }
        }
    }, ), HookManager::RETURN | HookManager::LISTENER);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN4I18n3getERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKNS0_6vectorIS6_NS4_IS6_EEEE"), LAMBDA((std::__ndk1::string* result, const std::__ndk1::string& key, std::__ndk1::vector<std::__ndk1::string> const& values), {
        if(key.rfind("death.kex.", 0) == 0 && *result == key) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring output = KEXJavaBridge::DamageModule::translateAndFormatDeathMessage(key.substr(10).c_str(), values);
            const char* cOutput = env->GetStringUTFChars(output, 0);
            *result = cOutput;
            env->ReleaseStringUTFChars(output, cOutput);
            env->DeleteLocalRef(output);
        }
    }, ), HookManager::RETURN | HookManager::LISTENER);
}


extern "C" {
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_DamageModule_nativeNewCause
    (JNIEnv* env, jclass, jstring name) {
        const char* cName = env->GetStringUTFChars(name, 0);
        std::string cppName(cName);
        env->ReleaseStringUTFChars(name, cName);
        if(KEXDamageModule::causeNameToCause.find(cppName) != KEXDamageModule::causeNameToCause.end()) return -1;
        int id = KEXDamageModule::nextCustomCauseId++;
        KEXDamageModule::causeNameToCause.emplace(cppName, id);
        KEXDamageModule::causeToCauseName.emplace(id, cppName);
        return id;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_DamageModule_nativeSetFire
    (JNIEnv*, jclass, jint id) {
        if(KEXDamageModule::fireCauses.find(id) == KEXDamageModule::fireCauses.end()) {
            KEXDamageModule::fireCauses.emplace(id);
        }
    }
    JNIEXPORT jboolean JNICALL Java_vsdum_kex_modules_DamageModule_isFire
    (JNIEnv*, jclass, jint id) {
        return KEXDamageModule::fireCauses.find(id) != KEXDamageModule::fireCauses.end();
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_DamageModule_nativeEnableCustomTranslationCallbackFor
    (JNIEnv*, jclass, jint id) {
        if(KEXDamageModule::customTranslationCallbacks.find(id) == KEXDamageModule::customTranslationCallbacks.end()) {
            KEXDamageModule::customTranslationCallbacks.emplace(id);
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_DamageModule_nativeDamageEntityCommon
    (JNIEnv*, jclass, jlong entity, jint damage, jint cause, jboolean b1, jboolean b2) {
        Actor* actor = Actor::wrap(entity);
        if(actor != nullptr) {
            actor->hurt(ActorDamageSource((ActorDamageCause) cause), damage, b1, b2);
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_DamageModule_nativeDamageEntityActor
    (JNIEnv*, jclass, jlong entity, jint damage, jint cause, jboolean b1, jboolean b2, jlong attacker) {
        Actor* actor = Actor::wrap(entity);
        Actor* attackingActor = Actor::wrap(attacker);
        if(actor != nullptr) {
            if(attackingActor != nullptr) {
                actor->hurt(ActorDamageByActorSource(*attackingActor, (ActorDamageCause) cause), damage, b1, b2);
            } else {
                actor->hurt(ActorDamageSource((ActorDamageCause) cause), damage, b1, b2);
            }
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_DamageModule_nativeDamageEntityWorld
    (JNIEnv*, jclass, jlong entity, jint damage, jint cause, jboolean b1, jboolean b2, jlong bsptr) {
        Actor* actor = Actor::wrap(entity);
        if(actor != nullptr) {
            BlockSource* world = (BlockSource*) bsptr;
            actor->hurt(ActorDamageByActorSource(*world, (ActorDamageCause) cause), damage, b1, b2);
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_DamageModule_nativeDamageEntityBlock
    (JNIEnv*, jclass, jlong entity, jint damage, jint cause, jboolean b1, jboolean b2, jlong bsptr, jint x, jint y, jint z) {
        Actor* actor = Actor::wrap(entity);
        if(actor != nullptr) {
            BlockSource* world = (BlockSource*) bsptr;
            Block* block = world->getBlock(BlockPos(x, y, z));
            if(block != nullptr) {
                actor->hurt(ActorDamageByBlockSource(*block, (ActorDamageCause) cause), damage, b1, b2);
            } else {
                actor->hurt(ActorDamageSource((ActorDamageCause) cause), damage, b1, b2);
            }
        }
    }
}