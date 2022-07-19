#include <hook.h>
#include <innercore_callbacks.h>
#include <symbol.h>

#include <innercore/vtable.h>

#include <Level.hpp>
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
            JavaCallbacks::invokeCallback(KEXJavaBridge::Cache::CallbacksModule(), "onPlayerJump", "(J)V", player->getUniqueID()->id);
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN11LocalPlayer17setPlayerGameTypeE8GameType"),
        LAMBDA((LocalPlayer* player, GameType mode), {
            JavaCallbacks::invokeCallback(KEXJavaBridge::Cache::CallbacksModule(), "onGameModeChanged", "(I)V", (int) mode);
        }, ),
        HookManager::RETURN | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN21ActorEventCoordinator27sendActorCarriedItemChangedER5ActorRK12ItemInstanceS4_8HandSlot"),
        LAMBDA((ActorEventCoordinator* coordinator, Actor& actor, const ItemInstance& oldItem, const ItemInstance& newItem, HandSlot hand), {
            JavaCallbacks::invokeCallback(KEXJavaBridge::Cache::CallbacksModule(), "onChangeCarriedItem", "(JJJB)V", actor.getUniqueID()->id, (jlong) &oldItem, (jlong) &newItem, (jbyte) hand);
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN21ActorEventCoordinator21sendActorSneakChangedER5Actorb"),
        LAMBDA((ActorEventCoordinator* coordinator, Actor& actor, bool sneaking), {
            if(!actor.isClientSide()) {
                JavaCallbacks::invokeCallback(KEXJavaBridge::Cache::CallbacksModule(), "onSneakChanged", "(JZ)V", actor.getUniqueID()->id, sneaking);
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );

}