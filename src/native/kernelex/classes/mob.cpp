#include <jni.h>
#include <innercore/vtable.h>
#include <static_symbol.hpp>
#include <Mob.hpp>
#include <Player.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_Mob_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(void, SetSleeping, jboolean sleeping) {
        VTABLE_FIND_OFFSET(Mob_setSleeping, _ZTV3Mob, _ZN3Mob11setSleepingEb);
        VTABLE_CALL<void>(Mob_setSleeping, (Mob*) ptr, sleeping);
    }
    __EXPORT__(jboolean, IsSprinting) {
        return ((Mob*) ptr)->isSprinting();
    }
    __EXPORT__(void, SetSprinting, jboolean sprinting) {
        VTABLE_FIND_OFFSET(Mob_setSprinting, _ZTV3Mob, _ZN3Mob12setSprintingEb);
        VTABLE_CALL<void>(Mob_setSprinting, (Mob*) ptr, sprinting);
    }
    __EXPORT__(jfloat, GetSpeed) {
        VTABLE_FIND_OFFSET(Mob_getSpeed, _ZTV3Mob, _ZNK3Mob8getSpeedEv);
        return VTABLE_CALL<float>(Mob_getSpeed, (Mob*) ptr);
    }
    __EXPORT__(void, SetSpeed, jfloat speed) {
        VTABLE_FIND_OFFSET(Mob_setSpeed, _ZTV3Mob, _ZN3Mob8setSpeedEf);
        VTABLE_CALL<void>(Mob_setSpeed, (Mob*) ptr, speed);
    }
    __EXPORT__(jfloat, GetJumpPower) {
        VTABLE_FIND_OFFSET(Mob_getJumpPower, _ZTV3Mob, _ZNK3Mob12getJumpPowerEv);
        return VTABLE_CALL<float>(Mob_getJumpPower, (Mob*) ptr);
    }
    __EXPORT__(jint, GetMeleeWeaponDamageBonus, jlong mobptr) {
        VTABLE_FIND_OFFSET(Mob_getMeleeWeaponDamageBonus, _ZTV3Mob, _ZN3Mob25getMeleeWeaponDamageBonusEP3Mob);
        return VTABLE_CALL<int>(Mob_getMeleeWeaponDamageBonus, (Mob*) ptr, (Mob*) mobptr);
    }
    __EXPORT__(jfloat, GetMeleeKnockbackBonus) {
        VTABLE_FIND_OFFSET(Mob_getMeleeKnockbackBonus, _ZTV3Mob, _ZN3Mob22getMeleeKnockbackBonusEv);
        return VTABLE_CALL<float>(Mob_getMeleeKnockbackBonus, (Mob*) ptr);
    }
    __EXPORT__(void, Travel, jfloat strafe, jfloat vertical, jfloat forward) {
        VTABLE_FIND_OFFSET(Mob_travel__fff, _ZTV3Mob, _ZN3Mob6travelEfff);
        VTABLE_CALL<void>(Mob_travel__fff, (Mob*) ptr, strafe, vertical, forward);
    }
    __EXPORT__(void, ApplyFinalFriction, jfloat friction, jboolean discardFriction) {
        VTABLE_FIND_OFFSET(Mob_applyFinalFriction, _ZTV3Mob, _ZN3Mob18applyFinalFrictionEfb);
        VTABLE_CALL<void>(Mob_applyFinalFriction, (Mob*) ptr, friction, discardFriction);
    }
    __EXPORT__(jboolean, IsLookingAtAnEntity) {
        VTABLE_FIND_OFFSET(Mob_isLookingAtAnEntity, _ZTV3Mob, _ZN3Mob19isLookingAtAnEntityEv);
        return VTABLE_CALL<bool>(Mob_isLookingAtAnEntity, (Mob*) ptr);
    }
    __EXPORT__(jint, GetItemUseDuration) {
        VTABLE_FIND_OFFSET(Mob_getItemUseDuration, _ZTV3Mob, _ZN3Mob18getItemUseDurationEv);
        return VTABLE_CALL<int>(Mob_getItemUseDuration, (Mob*) ptr);
    }
    __EXPORT__(jfloat, GetItemUseStartupProgress) {
        VTABLE_FIND_OFFSET(Mob_getItemUseStartupProgress, _ZTV3Mob, _ZN3Mob25getItemUseStartupProgressEv);
        return VTABLE_CALL<float>(Mob_getItemUseStartupProgress, (Mob*) ptr);
    }
    __EXPORT__(jfloat, GetItemUseIntervalProgress) {
        VTABLE_FIND_OFFSET(Mob_getItemUseIntervalProgress, _ZTV3Mob, _ZN3Mob26getItemUseIntervalProgressEv);
        return VTABLE_CALL<float>(Mob_getItemUseIntervalProgress, (Mob*) ptr);
    }
    __EXPORT__(jfloat, GetMaxHeadXRot) {
        VTABLE_FIND_OFFSET(Mob_getMaxHeadXRot, _ZTV3Mob, _ZN3Mob14getMaxHeadXRotEv);
        return VTABLE_CALL<float>(Mob_getMaxHeadXRot, (Mob*) ptr);
    }
    __EXPORT__(jlong, GetLastHurtByMob) {
        VTABLE_FIND_OFFSET(Mob_getLastHurtByMob, _ZTV3Mob, _ZN3Mob16getLastHurtByMobEv);
        Mob* result = VTABLE_CALL<Mob*>(Mob_getLastHurtByMob, (Mob*) ptr);
        if(result == nullptr) return 0;
        return (jlong) result;
    }
    __EXPORT__(void, SetLastHurtByMob, jlong mobptr) {
        VTABLE_FIND_OFFSET(Mob_setLastHurtByMob, _ZTV3Mob, _ZN3Mob16setLastHurtByMobEP3Mob);
        VTABLE_CALL<void>(Mob_setLastHurtByMob, (Mob*) ptr, (Mob*) mobptr);
    }
    __EXPORT__(jlong, GetLastHurtByPlayer) {
        VTABLE_FIND_OFFSET(Mob_getLastHurtByPlayer, _ZTV3Mob, _ZN3Mob19getLastHurtByPlayerEv);
        Player* result = VTABLE_CALL<Player*>(Mob_getLastHurtByPlayer, (Mob*) ptr);
        if(result == nullptr) return 0;
        return (jlong) result;
    }
    __EXPORT__(void, SetLastHurtByPlayer, jlong playerptr) {
        VTABLE_FIND_OFFSET(Mob_setLastHurtByPlayer, _ZTV3Mob, _ZN3Mob19setLastHurtByPlayerEP6Player);
        VTABLE_CALL<void>(Mob_setLastHurtByPlayer, (Mob*) ptr, (Player*) playerptr);
    }
    __EXPORT__(jlong, GetLastHurtMob) {
        VTABLE_FIND_OFFSET(Mob_getLastHurtMob, _ZTV3Mob, _ZN3Mob14getLastHurtMobEv);
        Actor* result = VTABLE_CALL<Actor*>(Mob_getLastHurtMob, (Mob*) ptr);
        if(result == nullptr) return 0;
        return (jlong) result;
    }
    __EXPORT__(void, SetLastHurtMob, jlong actorptr) {
        VTABLE_FIND_OFFSET(Mob_setLastHurtMob, _ZTV3Mob, _ZN3Mob14setLastHurtMobEP5Actor);
        VTABLE_CALL<void>(Mob_setLastHurtMob, (Mob*) ptr, (Actor*) actorptr);
    }
    __EXPORT__(jboolean, IsAlliedTo, jlong mobptr) {
        VTABLE_FIND_OFFSET(Mob_isAlliedTo, _ZTV3Mob, _ZN3Mob10isAlliedToEP3Mob);
        return VTABLE_CALL<bool>(Mob_isAlliedTo, (Mob*) ptr, (Mob*) mobptr);
    }
    __EXPORT__(jboolean, CanBeControlledByRider) {
        VTABLE_FIND_OFFSET(Mob_canBeControlledByRider, _ZTV3Mob, _ZN3Mob22canBeControlledByRiderEv);
        return VTABLE_CALL<bool>(Mob_canBeControlledByRider, (Mob*) ptr);
    }
    __EXPORT__(void, LeaveCaravan) {
        VTABLE_FIND_OFFSET(Mob_leaveCaravan, _ZTV3Mob, _ZN3Mob12leaveCaravanEv);
        VTABLE_CALL<void>(Mob_leaveCaravan, (Mob*) ptr);
    }
    __EXPORT__(void, JoinCaravan, jlong mobptr) {
        VTABLE_FIND_OFFSET(Mob_joinCaravan, _ZTV3Mob, _ZN3Mob11joinCaravanEv);
        VTABLE_CALL<void>(Mob_joinCaravan, (Mob*) ptr, (Mob*) mobptr);
    }
    __EXPORT__(jboolean, HasCaravanTail) {
        VTABLE_FIND_OFFSET(Mob_hasCaravanTail, _ZTV3Mob, _ZNK3Mob14hasCaravanTailEv);
        return VTABLE_CALL<bool>(Mob_hasCaravanTail, (Mob*) ptr);
    }
    __EXPORT__(jlong, GetCaravanHead) {
        VTABLE_FIND_OFFSET(Mob_getCaravanHead, _ZTV3Mob, _ZNK3Mob14getCaravanHeadEv);
        Mob* result = VTABLE_CALL<Mob*>(Mob_getCaravanHead, (Mob*) ptr);
        if(result == nullptr) return 0;
        return (jlong) result;
    }
    __EXPORT__(jint, GetArmorValue) {
        VTABLE_FIND_OFFSET(Mob_getArmorValue, _ZTV3Mob, _ZN3Mob13getArmorValueEv);
        return VTABLE_CALL<int>(Mob_getArmorValue, (Mob*) ptr);
    }
    __EXPORT__(jfloat, GetArmorCoverPercentage) {
        VTABLE_FIND_OFFSET(Mob_getArmorCoverPercentage, _ZTV3Mob, _ZNK3Mob23getArmorCoverPercentageEv);
        return VTABLE_CALL<float>(Mob_getArmorCoverPercentage, (Mob*) ptr);
    }
    __EXPORT__(jlong, GetItemSlot, jint slot) {
        ItemStack* stack = ((Mob*) ptr)->getItemSlot((EquipmentSlot) slot);
        if(stack == nullptr || stack->isNull()) return 0;
        return (jlong) stack;
    }
    __EXPORT__(void, SetItemSlot, jint slot, jlong stackptr) {
        VTABLE_FIND_OFFSET(Mob_setItemSlot, _ZTV3Mob, _ZN3Mob11setItemSlotE13EquipmentSlotRK9ItemStack);
        ItemStack* stack = (ItemStack*) stackptr;
        VTABLE_CALL<void>(Mob_setItemSlot, (Mob*) ptr, (EquipmentSlot) slot, *stack);
    }
    __EXPORT__(jboolean, IsTransitioningSitting) {
        return ((Mob*) ptr)->isTransitioningSitting();
    }
    __EXPORT__(void, SetTransitioningSitting, jboolean transitioningSitting) {
        VTABLE_FIND_OFFSET(Mob_setTransitioningSitting, _ZTV3Mob, _ZN3Mob23setTransitioningSittingEb);
        VTABLE_CALL<void>(Mob_setTransitioningSitting, (Mob*) ptr, transitioningSitting);
    }
    __EXPORT__(jboolean, CanExistWhenDisallowMob) {
        VTABLE_FIND_OFFSET(Mob_canExistWhenDisallowMob, _ZTV3Mob, _ZNK3Mob23canExistWhenDisallowMobEv);
        return VTABLE_CALL<bool>(Mob_canExistWhenDisallowMob, (Mob*) ptr);
    }
    __EXPORT__(void, JumpFromGround) {
        VTABLE_FIND_OFFSET(Mob_jumpFromGround, _ZTV3Mob, _ZN3Mob14jumpFromGroundEv);
        VTABLE_CALL<void>(Mob_jumpFromGround, (Mob*) ptr);
    }
    __EXPORT__(jint, GetNoActionTime) {
        return ((Mob*) ptr)->getNoActionTime();
    }
    __EXPORT__(void, ResetNoActionTime) {
        ((Mob*) ptr)->resetNoActionTime();
    }
    __EXPORT__(jboolean, WantsToBeJockey) {
        return ((Mob*) ptr)->wantsToBeJockey();
    }
    __EXPORT__(void, SetWantsToBeJockey, jboolean wants) {
        ((Mob*) ptr)->setWantsToBeJockey(wants);
    }
    __EXPORT__(jboolean, IsLayingEgg) {
        return ((Mob*) ptr)->isLayingEgg();
    }
    __EXPORT__(void, SetIsLayingEgg, jboolean laying) {
        ((Mob*) ptr)->setIsLayingEgg(laying);
    }
    __EXPORT__(jint, GetGlidingTicks) {
        return ((Mob*) ptr)->getGlidingTicks();
    }
    __EXPORT__(jfloat, GetFrictionModifier) {
        return ((Mob*) ptr)->getFrictionModifier();
    }
    __EXPORT__(void, SetFrictionModifier, jfloat frictionModifier) {
        ((Mob*) ptr)->setFrictionModifier(frictionModifier);
    }
    __EXPORT__(void, SnapToYBodyRot, jfloat rot) {
        ((Mob*) ptr)->snapToYBodyRot(rot);
    }
    __EXPORT__(void, SnapToYHeadRot, jfloat rot) {
        ((Mob*) ptr)->snapToYHeadRot(rot);
    }
    __EXPORT__(void, IncrementArrowCount, jint incr) {
        ((Mob*) ptr)->incrementArrowCount(incr);
    }
    __EXPORT__(jboolean, CanPickUpLoot, jlong stackptr) {
        return ((Mob*) ptr)->canPickUpLoot(*((ItemStack*) stackptr));
    }
    __EXPORT__(jfloat, GetJumpMultiplier) {
        return ((Mob*) ptr)->getJumpMultiplier();
    }
    __EXPORT__(jboolean, HasBeenHurtByMobInLastTicks, int ticks) {
        return ((Mob*) ptr)->hasBeenHurtByMobInLastTicks(ticks);
    }
    __EXPORT__(jboolean, IsHeadInWater) {
        return ((Mob*) ptr)->_isHeadInWater();
    }
    __EXPORT__(jfloat, GetMovementComponentCurrentSpeed) {
        return ((Mob*) ptr)->getMovementComponentCurrentSpeed();
    }
    __EXPORT__(void, SetMovementComponentCurrentSpeed, jfloat speed) {
        ((Mob*) ptr)->setMovementComponentCurrentSpeed(speed);
    }
    __EXPORT__(jfloat, GetFlightSpeed) {
        return ((Mob*) ptr)->getFlightSpeed();
    }
    __EXPORT__(void, SetFlightSpeed, jfloat speed) {
        ((Mob*) ptr)->setFlightSpeed(speed);
    }
    __EXPORT__(jboolean, IsInterpolationActive) {
        return ((Mob*) ptr)->isInterpolationActive();
    }
    __EXPORT__(void, SetInterpolationActive, jboolean interpolationActive) {
        ((Mob*) ptr)->setInterpolation(interpolationActive);
    }
    __EXPORT__(void, SetYHeadRot, jfloat rot) {
        ((Mob*) ptr)->setYHeadRot(rot);
    }
    __EXPORT__(jfloat, GetRiderRotLimit) {
        return ((Mob*) ptr)->getRiderRotLimit();
    }
    __EXPORT__(void, SetRiderRotLimit, jfloat lim) {
        return ((Mob*) ptr)->setRiderRotLimit(lim);
    }
    __EXPORT__(jint, GetRollCounter) {
        return ((Mob*) ptr)->getRollCounter();
    }
    __EXPORT__(jboolean, IsRolling) {
        return ((Mob*) ptr)->isRolling();
    }
    __EXPORT__(void, SetRolling, jboolean rolling) {
        ((Mob*) ptr)->setRolling(rolling);
    }
    __EXPORT__(jint, GetSpawnMethod) {
        return (int) ((Mob*) ptr)->getSpawnMethod();
    }
    __EXPORT__(void, SetSpawnMethod, jint method) {
        ((Mob*) ptr)->setSpawnMethod((MobSpawnMethod) method);
    }
    __EXPORT__(jfloat, GetXxa) {
        return ((Mob*) ptr)->getXxa();
    }
    __EXPORT__(void, SetXxa, jfloat xxa) {
        ((Mob*) ptr)->setXxa(xxa);
    }
    __EXPORT__(jfloat, GetYya) {
        return ((Mob*) ptr)->getYya();
    }
    __EXPORT__(void, SetYya, jfloat yya) {
        ((Mob*) ptr)->setYya(yya);
    }
    __EXPORT__(jfloat, GetZza) {
        return ((Mob*) ptr)->getZza();
    }
    __EXPORT__(void, SetZza, jfloat zza) {
        ((Mob*) ptr)->setZza(zza);
    }
    __EXPORT__(jint, GetTravelType) {
        return (int) ((Mob*) ptr)->getTravelType();
    }
    __EXPORT__(void, SetSurfaceMob, jboolean isSurfaceMob) {
        ((Mob*) ptr)->setSurfaceMob(isSurfaceMob);
    }
    __EXPORT__(jboolean, IsPregnant) {
        return ((Mob*) ptr)->isPregnant();
    }
    __EXPORT__(void, SetIsPregnant, jboolean pregnant) {
        ((Mob*) ptr)->setIsPregnant(pregnant);
    }
    __EXPORT__(jboolean, IsNaturallySpawned) {
        return ((Mob*) ptr)->isNaturallySpawned();
    }
    __EXPORT__(void, SetNaturallySpawned, jboolean naturallySpawned) {
        ((Mob*) ptr)->setNaturallySpawned(naturallySpawned);
    }
    __EXPORT__(jfloat, GetRiderLockedBodyRot) {
        return ((Mob*) ptr)->getRiderLockedBodyRot();
    }
    __EXPORT__(void, SetRiderLockedBodyRot, jfloat bodyRot) {
        ((Mob*) ptr)->setRiderLockedBodyRot(bodyRot);
    }
    __EXPORT__(jboolean, IsFrostWalking) {
        return ((Mob*) ptr)->isFrostWalking();
    }
    __EXPORT__(void, SetJumpVelRedux, jboolean redux) {
        ((Mob*) ptr)->setJumpVelRedux(redux);
    }
    __EXPORT__(jfloat, CalcMoveRelativeSpeed, jint travelType) {
        return ((Mob*) ptr)->calcMoveRelativeSpeed((TravelType) travelType);
    }
    __EXPORT__(jboolean, IsEating) {
        return ((Mob*) ptr)->isEating();
    }
    __EXPORT__(void, SetEating, jboolean eating) {
        ((Mob*) ptr)->setEating(eating);
    }
    __EXPORT__(jint, GetEatCounter) {
        return ((Mob*) ptr)->getEatCounter();
    }
    __EXPORT__(void, SetEatCounter, jint eatCounter) {
        ((Mob*) ptr)->setEatCounter(eatCounter);
    }
    __EXPORT__(jboolean, HasBoundOrigin) {
        return ((Mob*) ptr)->hasBoundOrigin();
    }
    // TODO get/set BoundOrigin
    __EXPORT__(jint, GetCaravanSize) {
        return ((Mob*) ptr)->getCaravanSize();
    }
    __EXPORT__(jboolean, ShouldApplyWaterGravity) {
        return ((Mob*) ptr)->shouldApplyWaterGravity();
    }
    __EXPORT__(jboolean, IsGliding) {
        return ((Mob*) ptr)->isGliding();
    }
    __EXPORT__(jlong, GetFirstCaravanHead) {
        Mob* result = ((Mob*) ptr)->getFirstCaravanHead();
        if(result == nullptr) return 0;
        return (jlong) result;
    }
    __EXPORT__(jfloat, GetYRotA) {
        return ((Mob*) ptr)->getYRotA();
    }
    __EXPORT__(void, SetYRotA, jfloat yrota) {
        ((Mob*) ptr)->setYRotA(yrota);
    }
    __EXPORT__(void, SetJumping, jboolean jumping) {
        ((Mob*) ptr)->setJumping(jumping);
    }
    __EXPORT__(void, SetSpeedModifier, jfloat speedMod) {
        ((Mob*) ptr)->setSpeedModifier(speedMod);
    }
    __EXPORT__(jint, GetCurrentSwingDuration) {
        return ((Mob*) ptr)->getCurrentSwingDuration();
    }
    __EXPORT__(jboolean, IsSwinging) {
        return ((Mob*) ptr)->isSwinging();
    }
    __EXPORT__(jint, CalculateJumpImpulse) {
        return ((Mob*) ptr)->calculateJumpImpulse();
    }
    __EXPORT__(jboolean, IsSlime) {
        Mob* mob = (Mob*) ptr;
        void** vtable = *(void***) mob;
        STATIC_VTABLE_SYMBOL(Slime_table, "_ZTV5Slime");
        STATIC_VTABLE_SYMBOL(LavaSlime_table, "_ZTV9LavaSlime");
        return vtable == Slime_table || vtable == LavaSlime_table;
    }
}


#undef __EXPORT__