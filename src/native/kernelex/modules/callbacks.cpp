#include <hook.h>
#include <innercore_callbacks.h>
#include <symbol.h>

#include <innercore/vtable.h>

#include <LocalPlayer.hpp>
#include <ActorUniqueID.hpp>
#include <ActorDamageSource.hpp>
#include <ItemInstance.hpp>

#include "../utils/java_utils.hpp"
#include "callbacks.hpp"


void KEXCallbacksModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN6Player14jumpFromGroundEv"),
        LAMBDA((Player* player), {
            KEXJavaBridge::CallbacksModule::onPlayerJump(player->getUniqueID()->id);
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN11LocalPlayer17setPlayerGameTypeE8GameType"),
        LAMBDA((LocalPlayer* player, GameType mode), {
            KEXJavaBridge::CallbacksModule::onGameModeChanged((int) mode);
        }, ),
        HookManager::RETURN | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN3Mob11hurtEffectsERK17ActorDamageSourceibb"),
        LAMBDA((HookManager::CallbackController* controller, Mob* mob, const ActorDamageSource& source, int value, bool b1, bool b2), {
            jlong victim = mob->getUniqueID()->id;
            VTABLE_FIND_OFFSET(ActorDamageSource_isEntitySource, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource14isEntitySourceEv);
            jlong attacker = VTABLE_CALL<bool>(ActorDamageSource_isEntitySource, (ActorDamageSource*) &source) ? ((ActorDamageByActorSource*) &source)->entityUid.id : -1ll;
            jint type = (int) source.getCause();
            JavaCallbacks::invokeControlledCallback("onEntityHurt", "(JJIIZZ)V", controller, JavaCallbacks::PREVENTABLE, victim, attacker, type, value, b1, b2);
            return false;
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN21ActorEventCoordinator27sendActorCarriedItemChangedER5ActorRK12ItemInstanceS4_8HandSlot"),
        LAMBDA((ActorEventCoordinator* coordinator, Actor& actor, const ItemInstance& oldItem, const ItemInstance& newItem, HandSlot hand), {
            JavaCallbacks::invokeCallback(KEXJavaBridge::Cache::CallbacksModule(), "onChangeCarriedItem", "(JJJB)V", actor.getUniqueID()->id, (jlong) &oldItem, (jlong) &newItem, (jbyte) hand);
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );

}