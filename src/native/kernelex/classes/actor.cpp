#include <jni.h>
#include <innercore/vtable.h>
#include <commontypes.hpp>
#include <ActorUniqueID.hpp>
#include <Actor.hpp>
#include <MobEffect.hpp>


extern "C" {



JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_wrap
(JNIEnv*, jclass, jlong uid) {
    Actor* actor = Actor::wrap(uid);
    if(actor != nullptr) {
        return (jlong) actor;
    }
    return 0;
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsBreakingObstruction
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isBreakingObstruction();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetBreakingObstruction
(JNIEnv*, jclass, jlong ptr, jboolean breaking) {
    ((Actor*) ptr)->setBreakingObstruction(breaking);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsDancing
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isDancing();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetDancing
(JNIEnv*, jclass, jlong ptr, jboolean dancing) {
    ((Actor*) ptr)->setDancing(dancing);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeHealEffects
(JNIEnv*, jclass, jlong ptr, jint value) {
    ((Actor*) ptr)->healEffects(value);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetColor
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getColor();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetColor
(JNIEnv*, jclass, jlong ptr, jint color) {
    ((Actor*) ptr)->setColor((PaletteColor) color);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetColor2
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getColor2();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetColor2
(JNIEnv*, jclass, jlong ptr, jint color) {
    ((Actor*) ptr)->setColor2((PaletteColor) color);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInClouds
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isInClouds();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasUniqueID
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasUniqueID();
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetUniqueID
(JNIEnv*, jclass, jlong ptr) {
    ActorUniqueID* uid = ((Actor*) ptr)->getUniqueID();
    if(uid == nullptr) return 0;
    return uid->id;
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetHurtDir
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getHurtDir();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetHurtDir
(JNIEnv*, jclass, jlong ptr, jint dir) {
    ((Actor*) ptr)->setHurtDir(dir);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsEnchanted
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isEnchanted, _ZTV5Actor, _ZNK5Actor11isEnchantedEv);
    return VTABLE_CALL<bool>(Actor_isEnchanted, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetEnchanted
(JNIEnv*, jclass, jlong ptr, jboolean enchanted) {
    ((Actor*) ptr)->setEnchanted(enchanted);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetMarkVariant
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getMarkVariant();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetMarkVariant
(JNIEnv*, jclass, jlong ptr, jint variant) {
    ((Actor*) ptr)->setMarkVariant(variant);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasDimension
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasDimension();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanChangeDimensions
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_canChangeDimensions, _ZTV5Actor, _ZNK5Actor19canChangeDimensionsEv);
    return VTABLE_CALL<bool>(Actor_canChangeDimensions, (Actor*) ptr);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetDimensionId
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getDimensionId, _ZTV5Actor, _ZNK5Actor14getDimensionIdEv);
    return VTABLE_CALL<int>(Actor_getDimensionId, (Actor*) ptr);
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetDimension
(JNIEnv*, jclass, jlong ptr) {
    Dimension* dim = ((Actor*) ptr)->getDimension();
    if(dim == nullptr) return 0;
    return (jlong) dim;
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeWasLastHitByPlayer
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->wasLastHitByPlayer();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasSaddle
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasSaddle();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetSaddle
(JNIEnv*, jclass, jlong ptr, jboolean saddle) {
    ((Actor*) ptr)->setSaddle(saddle);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsDelayedAttacking
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isDelayedAttacking();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetDelayedAttacking
(JNIEnv*, jclass, jlong ptr, jboolean delayed) {
    ((Actor*) ptr)->setDelayedAttacking(delayed);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanBeginOrContinueClimbingLadder
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->canBeginOrContinueClimbingLadder();
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetStructuralIntegrity
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getStructuralIntegrity();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetStructuralIntegrity
(JNIEnv*, jclass, jlong ptr, int integrity) {
    ((Actor*) ptr)->setStructuralIntegrity(integrity);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasLevel
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasLevel();
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetLevel
(JNIEnv*, jclass, jlong ptr) {
    Level* level = ((Actor*) ptr)->getLevel();
    if(level == nullptr) return 0;
    return (jlong) level;
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetCameraDistance
(JNIEnv*, jclass, jlong ptr) {
     return ((Actor*) ptr)->getCameraDistance();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetCameraDistance
(JNIEnv*, jclass, jlong ptr, jfloat distance) {
    ((Actor*) ptr)->setCameraDistance(distance);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsDoorOpener
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isDoorOpener();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetDoorOpener
(JNIEnv*, jclass, jlong ptr, jboolean opener) {
    ((Actor*) ptr)->setDoorOpener(opener);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasType
(JNIEnv*, jclass, jlong ptr, jint type) {
    return ((Actor*) ptr)->hasType((ActorType) type);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsType
(JNIEnv*, jclass, jlong ptr, jint type) {
    return ((Actor*) ptr)->isType((ActorType) type);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeRemoveEffectNoUpdate
(JNIEnv*, jclass, jlong ptr, jint effectId) {
    ((Actor*) ptr)->removeEffectNoUpdate(effectId);
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetEffect__JJ
(JNIEnv*, jclass, jlong ptr, jlong mobEffect) {
    MobEffectInstance* effect = ((Actor*) ptr)->getEffect(*((MobEffect*) mobEffect));
    if(effect == nullptr) return 0;
    return (jlong) effect;
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetEffect__JI
(JNIEnv*, jclass, jlong ptr, jint effectId) {
    MobEffect* effect = MobEffect::getById(effectId);
    if(effect != nullptr) {
        MobEffectInstance* instance = ((Actor*) ptr)->getEffect(*effect);
        if(effect != nullptr) return (jlong) effect;
    }
    return 0;
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetActiveEffectCount
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getActiveEffectCount();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasEffect__JJ
(JNIEnv*, jclass, jlong ptr, jlong mobEffect) {
    return ((Actor*) ptr)->hasEffect(*((MobEffect*) mobEffect));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasEffect__JI
(JNIEnv*, jclass, jlong ptr, jint id) {
    MobEffect* effect = MobEffect::getById(id);
    if(effect != nullptr) {
        return ((Actor*) ptr)->hasEffect(*effect);
    }
    return false;
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasAnyVisibleEffects
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasAnyVisibleEffects();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeRemoveEffect
(JNIEnv*, jclass, jlong ptr, jint id) {
    ((Actor*) ptr)->removeEffect(id);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasAnyEffects
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasAnyEffects();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeRemoveAllEffects
(JNIEnv*, jclass, jlong ptr) {
    ((Actor*) ptr)->removeAllEffects();
}
//getAllEffects TODO
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeAddEffect
(JNIEnv*, jclass, jlong ptr, jlong instancePtr) {
    ((Actor*) ptr)->addEffect(*((MobEffectInstance*) instancePtr));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInSnow
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isInSnow();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanMate
(JNIEnv*, jclass, jlong ptr, jlong mate) {
    return ((Actor*) ptr)->canMate((*(Actor*) mate));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasTickingArea
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasTickingArea();
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetTickingArea
(JNIEnv*, jclass, jlong ptr) {
    TickingArea* area = ((Actor*) ptr)->getTickingArea();
    if(area == nullptr) return 0;
    return (jlong) area;
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeGetIsOnScreen
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getIsOnScreen();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetIsOnScreen
(JNIEnv*, jclass, jlong ptr, jboolean onScreen) {
    ((Actor*) ptr)->setIsOnScreen(onScreen);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsOverScaffolding
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isOverScaffolding();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInScaffolding
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isInScaffolding();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeShouldOrphan
(JNIEnv*, jclass, jlong ptr, jlong bsptr) {
    return ((Actor*) ptr)->shouldOrphan(*((BlockSource*) bsptr));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsOrphan
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isOrphan();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsPredictedMovementEnabled
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isPredictedMovementEnabled();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInRain
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isInRain();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsWASDControlled
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isWASDControlled();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetWASDControlled
(JNIEnv*, jclass, jlong ptr, jboolean wasd) {
    ((Actor*) ptr)->setWASDControlled(wasd);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasPriorityAmmunition
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasPriorityAmmunition();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasRuntimeID
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasRuntimeID();
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetVariant
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getVariant();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetVariant
(JNIEnv*, jclass, jlong ptr, jint variant) {
    ((Actor*) ptr)->setVariant(variant);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsRiding__JJ
(JNIEnv*, jclass, jlong ptr, jlong ridden) {
    return ((Actor*) ptr)->isRiding((Actor*) ridden);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsRider
(JNIEnv*, jclass, jlong ptr, jlong rider) {
    return ((Actor*) ptr)->isRider(*((Actor*) rider));
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeRemoveAllRiders
(JNIEnv*, jclass, jlong ptr, jboolean someBool1, jboolean someBool2) {
    ((Actor*) ptr)->removeAllRiders(someBool1, someBool2);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasPlayerRider
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasPlayerRider();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsRiding__J
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isRiding();
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetRide
(JNIEnv*, jclass, jlong ptr) {
    Actor* ride = ((Actor*) ptr)->getRide();
    if(ride == nullptr) return 0;
    return (jlong) ride;
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasRider
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasRider();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeGetStatusFlag
(JNIEnv*, jclass, jlong ptr, jint flag) {
    return ((Actor*) ptr)->getStatusFlag((ActorFlags) flag);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsChested
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isChested();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsStackable
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isStackable();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsResting
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isResting();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetResting
(JNIEnv*, jclass, jlong ptr, jboolean resting) {
    ((Actor*) ptr)->setResting(resting);
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetHealth
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getHealth();
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetMaxHealth
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getMaxHealth();
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetControllingSeat
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getControllingSeat();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetControllingSeat
(JNIEnv*, jclass, jlong ptr, jint seat) {
    ((Actor*) ptr)->setControllingSeat(seat);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInsidePortal
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isInsidePortal();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasTeleported
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasTeleported();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeMoveRelative
(JNIEnv*, jclass, jlong ptr, jfloat strafe, jfloat up, jfloat forward, jfloat friction) {
    ((Actor*) ptr)->moveRelative(strafe, up, forward, friction);
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetRegion
(JNIEnv*, jclass, jlong ptr) {
    BlockSource* region = ((Actor*) ptr)->getRegion();
    if(region == nullptr) return 0;
    return (jlong) region;
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsTame
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isTame();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsLeashed
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isLeashed();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsLeashableType
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isLeashableType, _ZTV5Actor, _ZNK5Actor15isLeashableTypeEv);
    return VTABLE_CALL<bool>(Actor_isLeashableType, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsMoving
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isMoving();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetMoving
(JNIEnv*, jclass, jlong ptr, jboolean moving) {
    ((Actor*) ptr)->setMoving(moving);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasTotemEquipped
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasTotemEquipped();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsAutonomous
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isAutonomous();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetAutonomous
(JNIEnv*, jclass, jlong ptr, jboolean autonomous) {
    ((Actor*) ptr)->setAutonomous(autonomous);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsPersistent
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isPersistent();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeRemoveEntity
(JNIEnv*, jclass, jlong ptr) {
    ((Actor*) ptr)->removeEntity();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetCollidableMob
(JNIEnv*, jclass, jlong ptr, jboolean collidable) {
    ((Actor*) ptr)->setCollidableMob(collidable);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeGetCollidableMobNear
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getCollidableMobNear();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetCollidableMobNear
(JNIEnv*, jclass, jlong ptr, jboolean collidable) {
    ((Actor*) ptr)->setCollidableMobNear(collidable);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasFishingHook
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->hasFishingHook();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeGetChainedDamageEffects
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getChainedDamageEffects();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetChainedDamageEffects
(JNIEnv*, jclass, jlong ptr, jboolean chained) {
    ((Actor*) ptr)->setChainedDamageEffects(chained);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsPacified
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isPacified();
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeDistanceTo__JJ
(JNIEnv*, jclass, jlong ptr, jlong actor) {
    return ((Actor*) ptr)->distanceTo(*((Actor*) actor));
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeDistanceTo__JFFF
(JNIEnv*, jclass, jlong ptr, jfloat x, jfloat y, jfloat z) {
    return ((Actor*) ptr)->distanceTo(Vec3(x, y, z));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanCurrentlySwim
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->canCurrentlySwim();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsSwimming
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isSwimming();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsSwimmer
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isSwimmer();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetSwimmer
(JNIEnv*, jclass, jlong ptr, jboolean swimmer) {
    ((Actor*) ptr)->setSwimmer(swimmer);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasFamily
(JNIEnv* env, jclass, jlong ptr, jstring family) {
    const char* cfamily = env->GetStringUTFChars(family, 0);
    HashedString hfamily(cfamily);
    env->ReleaseStringUTFChars(family, cfamily);
    return ((Actor*) ptr)->hasFamily(hfamily);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasAttributeBuff
(JNIEnv*, jclass, jlong ptr, jint buffType) {
    return ((Actor*) ptr)->hasAttributeBuff((AttributeBuffType) buffType);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsClientSide
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isClientSide();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsControlledByLocalInstance
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isControlledByLocalInstance();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsClimbing
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isClimbing();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetClimbing
(JNIEnv*, jclass, jlong ptr, jboolean climbing) {
    ((Actor*) ptr)->setClimbing(climbing);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanClimb
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->canClimb();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetCanClimb
(JNIEnv*, jclass, jlong ptr, jboolean canClimb) {
    ((Actor*) ptr)->setCanClimb(canClimb);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetSkinID
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getSkinID();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetSkinID
(JNIEnv*, jclass, jlong ptr, jint skinID) {
    ((Actor*) ptr)->setSkinID(skinID);
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetSpeedInMetersPerSecond
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getSpeedInMetersPerSecond();
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetStrength
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getStrength();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetStrength
(JNIEnv*, jclass, jlong ptr, jint strength) {
    ((Actor*) ptr)->setStrength(strength);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetStrengthMax
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getStrengthMax();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetStrengthMax
(JNIEnv*, jclass, jlong ptr, jint strength) {
    ((Actor*) ptr)->setStrengthMax(strength);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeGetDamageNearbyMobs
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getDamageNearbyMobs();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetDamageNearbyMobs
(JNIEnv*, jclass, jlong ptr, jboolean damage) {
    VTABLE_FIND_OFFSET(Actor_setDamageNearbyMobs, _ZTV5Actor, _ZN5Actor19setDamageNearbyMobsEb);
    VTABLE_CALL<void>(Actor_setDamageNearbyMobs, (Actor*) ptr, damage);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsLayingDown
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isLayingDown();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetLayingDown
(JNIEnv*, jclass, jlong ptr, jboolean laying) {
    ((Actor*) ptr)->setLayingDown(laying);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeGetTempted
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getTempted();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetTempted
(JNIEnv*, jclass, jlong ptr, jboolean tempted) {
    ((Actor*) ptr)->setTempted(tempted);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeDropTowards
(JNIEnv*, jclass, jlong ptr, jlong stackptr, jfloat x, jfloat y, jfloat z) {
    ((Actor*) ptr)->dropTowards(*((ItemStack*) stackptr), Vec3(x, y, z));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsTrading
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isTrading();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsDownwardFlowingLiquid
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isDownwardFlowingLiquid();
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetJumpDuration
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getJumpDuration();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetJumpDuration
(JNIEnv*, jclass, jlong ptr, jint dur) {
    ((Actor*) ptr)->setJumpDuration(dur);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsScared
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isScared();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetScared
(JNIEnv*, jclass, jlong ptr, jboolean scared) {
    ((Actor*) ptr)->setScared(scared);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsSitting
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isSitting();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetSitting
(JNIEnv*, jclass, jlong ptr, jboolean sitting) {
    VTABLE_FIND_OFFSET(Actor_setSitting, _ZTV5Actor, _ZN5Actor10setSittingEb);
    VTABLE_CALL<void>(Actor_setSitting, (Actor*) ptr, sitting);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsBaby
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isBaby();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsIgnited
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isIgnited();
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetLifeSpan
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getLifeSpan, _ZTV5Actor, _ZNK5Actor11getLifeSpanEv);
    return VTABLE_CALL<int>(Actor_getLifeSpan, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetLimitedLife
(JNIEnv*, jclass, jlong ptr, jint life) {
    ((Actor*) ptr)->setLimitedLife(life);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInvisible
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isInvisible, _ZTV5Actor, _ZNK5Actor11isInvisibleEv);
    return VTABLE_CALL<bool>(Actor_isInvisible, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetInvisible
(JNIEnv*, jclass, jlong ptr, jboolean invisible) {
    ((Actor*) ptr)->setInvisible(invisible);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInWorld
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isInWorld();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInLove
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isInLove();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetInLove
(JNIEnv*, jclass, jlong ptr, jlong loverptr) {
    ((Actor*) ptr)->setInLove((Actor*) loverptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsDoorBreaker
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isDoorBreaker();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetDoorBreaker
(JNIEnv*, jclass, jlong ptr, jboolean breaker) {
    ((Actor*) ptr)->setDoorBreaker(breaker);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsWalker
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isWalker();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetWalker
(JNIEnv*, jclass, jlong ptr, jboolean walker) {
    ((Actor*) ptr)->setWalker(walker);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsCharged
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isCharged();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetCharged
(JNIEnv*, jclass, jlong ptr, jboolean charged) {
    ((Actor*) ptr)->setCharged(charged);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanFly
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->canFly();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetCanFly
(JNIEnv*, jclass, jlong ptr, jboolean canFly) {
    ((Actor*) ptr)->setCanFly(canFly);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInPrecipitation
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isInPrecipitation();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetAABB
(JNIEnv*, jclass, jlong ptr, jfloat x1, jfloat y1, jfloat z1, jfloat x2, jfloat y2, jfloat z2) {
    ((Actor*) ptr)->setAABB(AABB(x1, y1, z1, x2, y2, z2));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsSafeToSleepNear
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isSafeToSleepNear();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetBlockTarget
(JNIEnv*, jclass, jlong ptr, jint x, jint y, jint z) {
    return ((Actor*) ptr)->setBlockTarget(BlockPos(x, y, z));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsAngry
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isAngry();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsPowered
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isPowered();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetPowered
(JNIEnv*, jclass, jlong ptr, jboolean powered) {
    ((Actor*) ptr)->setPowered(powered);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsSheared
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isSheared();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsOutOfControl
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isOutOfControl();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsSneaking
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isSneaking();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetSneaking
(JNIEnv*, jclass, jlong ptr, jboolean sneaking) {
    VTABLE_FIND_OFFSET(Actor_setSneaking, _ZTV5Actor, _ZNK5Actor11setSneakingEb);
    VTABLE_CALL<void>(Actor_setSneaking, (Actor*) ptr, sneaking);
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetTarget
(JNIEnv*, jclass, jlong ptr) {
    Actor* target = ((Actor*) ptr)->getTarget();
    if(target == nullptr) return 0;
    return (jlong) target;
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetTarget
(JNIEnv*, jclass, jlong ptr, jlong targetptr) {
    VTABLE_FIND_OFFSET(Actor_setTarget, _ZTV5Actor, _ZN5Actor9setTargetEP5Actor);
    VTABLE_CALL<void>(Actor_setTarget, (Actor*) ptr, (Actor*) targetptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetStunned
(JNIEnv*, jclass, jlong ptr, jboolean stunned) {
    ((Actor*) ptr)->setStunned(stunned);
}
JNIEXPORT jshort JNICALL Java_vsdum_kex_natives_Actor_nativeGetTotalAirSupply
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getTotalAirSupply();
}
JNIEXPORT jshort JNICALL Java_vsdum_kex_natives_Actor_nativeGetAirSupply
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getAirSupply();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInThunderstorm
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isInThunderstorm();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsBribed
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isBribed();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsStanding
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isStanding();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetStanding
(JNIEnv*, jclass, jlong ptr, jboolean standing) {
    VTABLE_FIND_OFFSET(Actor_setStanding, _ZTV5Actor, _ZN5Actor11setStandingEb);
    VTABLE_CALL<void>(Actor_setStanding, (Actor*) ptr, standing);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetShakeTime
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getShakeTime();
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetShakeTime
(JNIEnv*, jclass, jlong ptr, jint time) {
    ((Actor*) ptr)->setShakeTime(time);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasCategory
(JNIEnv*, jclass, jlong ptr, jint category) {
    return ((Actor*) ptr)->hasCategory((ActorCategory) category);
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetVerticalSpeedInMetersPerSecond
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getVerticalSpeedInMetersPerSecond();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsTrusting
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->isTrusting();
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetRadius
(JNIEnv*, jclass, jlong ptr) {
    return ((Actor*) ptr)->getRadius();
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasComponent
(JNIEnv* env, jclass, jlong ptr, jstring component) {
    const char* ccomponent = env->GetStringUTFChars(component, 0);
    HashedString hcomponent(ccomponent);
    env->ReleaseStringUTFChars(component, ccomponent);
    VTABLE_FIND_OFFSET(Actor_hasComponent, _ZTV5Actor, _ZNK5Actor12hasComponentERK12HashedString);
    return VTABLE_CALL<bool>(Actor_hasComponent, (Actor*) ptr, hcomponent);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetOnDeathExperience
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getOnDeathExperience, _ZTV5Actor, _ZN5Actor20getOnDeathExperienceEv);
    return VTABLE_CALL<int>(Actor_getOnDeathExperience, (Actor*) ptr);
}
// TODO getInterpolatedRidingPosition, getInterpolatedBodyRot, getInterpolatedHeadRot
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetInterpolatedBodyYaw
(JNIEnv*, jclass, jlong ptr, jfloat partialTicks) {
    VTABLE_FIND_OFFSET(Actor_getInterpolatedBodyYaw, _ZTV5Actor, _ZNK5Actor22getInterpolatedBodyYawEf);
    return VTABLE_CALL<float>(Actor_getInterpolatedBodyYaw, (Actor*) ptr, partialTicks);
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetYawSpeedInDegreesPerSecond
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getYawSpeedInDegreesPerSecond, _ZTV5Actor, _ZNK5Actor29getYawSpeedInDegreesPerSecondEv);
    return VTABLE_CALL<float>(Actor_getYawSpeedInDegreesPerSecond, (Actor*) ptr);
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetInterpolatedWalkAnimSpeed
(JNIEnv*, jclass, jlong ptr, jfloat partialTicks) {
    VTABLE_FIND_OFFSET(Actor_getInterpolatedWalkAnimSpeed, _ZTV5Actor, _ZNK5Actor28getInterpolatedWalkAnimSpeedEf);
    return VTABLE_CALL<float>(Actor_getInterpolatedWalkAnimSpeed, (Actor*) ptr, partialTicks);
}
// TODO getInterpolatedRidingOffset
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsFireImmune
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isFireImmune, _ZTV5Actor, _ZNK5Actor12isFireImmuneEv);
    return VTABLE_CALL<bool>(Actor_isFireImmune, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeBreaksFallingBlocks
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_breaksFallingBlocks, _ZTV5Actor, _ZNK5Actor19breaksFallingBlocksEv);
    return VTABLE_CALL<bool>(Actor_breaksFallingBlocks, (Actor*) ptr);
}
// TODO blockedByShield, teleportTo
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeChorusFruitTeleport
(JNIEnv*, jclass, jlong ptr, jfloat x, jfloat y, jfloat z) {
    VTABLE_FIND_OFFSET(Actor_chorusFruitTeleport, _ZTV5Actor, _ZN5Actor19chorusFruitTeleportER4Vec3);
    VTABLE_CALL<void>(Actor_chorusFruitTeleport, (Actor*) ptr, Vec3(x, y, z));
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeLerpTo
(JNIEnv*, jclass, jlong ptr, jdouble x, jdouble y, jdouble z, jfloat rotX, jfloat rotY) {
    VTABLE_FIND_OFFSET(Actor_lerpTo, _ZTV5Actor, _ZN5Actor6lerpToERK4Vec3RK4Vec2i);
    VTABLE_CALL<void>(Actor_lerpTo, (Actor*) ptr, Vec3(x, y, z), Vec2(rotX, rotY), 0);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeLerpMotion
(JNIEnv*, jclass, jlong ptr, jdouble x, jdouble y, jdouble z) {
    VTABLE_FIND_OFFSET(Actor_lerpMotion, _ZTV5Actor, _ZN5Actor10lerpMotionERK4Vec3);
    VTABLE_CALL<void>(Actor_lerpMotion, (Actor*) ptr, Vec3(x, y, z));
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetRidingHeight
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getRidingHeight, _ZTV5Actor, _ZN5Actor15getRidingHeightEv);
    return VTABLE_CALL<float>(Actor_getRidingHeight, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeStartRiding
(JNIEnv*, jclass, jlong ptr, jlong riddenPtr) {
    VTABLE_FIND_OFFSET(Actor_startRiding, _ZTV5Actor, _ZN5Actor11startRidingER5Actor);
    VTABLE_CALL<void>(Actor_startRiding, (Actor*) ptr, *((Actor*) riddenPtr));
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeAddRider
(JNIEnv*, jclass, jlong ptr, jlong riderPtr) {
    VTABLE_FIND_OFFSET(Actor_addRider, _ZTV5Actor, _ZN5Actor8addRiderER5Actor);
    VTABLE_CALL<void>(Actor_addRider, (Actor*) ptr, *((Actor*) riderPtr));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIntersects
(JNIEnv*, jclass, jlong ptr, jfloat x1, jfloat y1, jfloat z1, jfloat x2, jfloat y2, jfloat z2) {
    VTABLE_FIND_OFFSET(Actor_intersects, _ZTV5Actor, _ZNK5Actor10intersectsERK4Vec3S2_);
    return VTABLE_CALL<bool>(Actor_intersects, (Actor*) ptr, Vec3(x1, y1, z1), Vec3(x2, y2, z2));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsFree__JFFF
(JNIEnv*, jclass, jlong ptr, jfloat x, jfloat y, jfloat z) {
    VTABLE_FIND_OFFSET(Actor_isFree, _ZTV5Actor, _ZN5Actor6isFreeERK4Vec3);
    return VTABLE_CALL<bool>(Actor_isFree, (Actor*) ptr, Vec3(x, y, z));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsFree_JFFFF
(JNIEnv*, jclass, jlong ptr, jfloat x, jfloat y, jfloat z, jfloat someFloat) {
    VTABLE_FIND_OFFSET(Actor_isFreeConst, _ZTV5Actor, _ZNK5Actor6isFreeERK4Vec3f);
    return VTABLE_CALL<bool>(Actor_isFreeConst, (Actor*) ptr, Vec3(x, y, z), someFloat);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInWall
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isInWall, _ZTV5Actor, _ZNK5Actor8isInWallEv);
    return VTABLE_CALL<bool>(Actor_isInWall, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanShowNameTag
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_canShowNameTag, _ZTV5Actor, _ZNK5Actor14canShowNameTagEv);
    return VTABLE_CALL<bool>(Actor_canShowNameTag, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanExistInPeaceful
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_canExistInPeaceful, _ZTV5Actor, _ZNK5Actor18canExistInPeacefulEv);
    return VTABLE_CALL<bool>(Actor_canExistInPeaceful, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetNameTagVisible
(JNIEnv*, jclass, jlong ptr, jboolean visible) {
    VTABLE_FIND_OFFSET(Actor_setNameTagVisible, _ZTV5Actor, _ZN5Actor17setNameTagVisibleEb);
    VTABLE_CALL<void>(Actor_setNameTagVisible, (Actor*) ptr, visible);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeGetAlwaysShowNameTag
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getAlwaysShowNameTag, _ZTV5Actor, _ZNK5Actor20getAlwaysShowNameTagEv);
    return VTABLE_CALL<bool>(Actor_getAlwaysShowNameTag, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInWater
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isInWater, _ZTV5Actor, _ZNK5Actor9isInWaterEv);
    return VTABLE_CALL<bool>(Actor_isInWater, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasEnteredWater
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_hasEnteredWater, _ZTV5Actor, _ZNK5Actor15hasEnteredWaterEv);
    return VTABLE_CALL<bool>(Actor_hasEnteredWater, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsImmersedInWater
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isImmersedInWater, _ZTV5Actor, _ZNK5Actor17isImmersedInWaterEv);
    return VTABLE_CALL<bool>(Actor_isImmersedInWater, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInWaterOrRain
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isInWaterOrRain, _ZTV5Actor, _ZNK5Actor15isInWaterOrRainEv);
    return VTABLE_CALL<bool>(Actor_isInWaterOrRain, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInLava
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isInLava, _ZTV5Actor, _ZNK5Actor8isInLavaEv);
    return VTABLE_CALL<bool>(Actor_isInLava, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsUnderLiquid
(JNIEnv*, jclass, jlong ptr, jint materialType) {
    VTABLE_FIND_OFFSET(Actor_isUnderLiquid, _ZTV5Actor, _ZNK5Actor13isUnderLiquidE12MaterialType);
    return VTABLE_CALL<bool>(Actor_isUnderLiquid, (Actor*) ptr, (MaterialType) materialType);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsOverWater
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isOverWater, _ZTV5Actor, _ZNK5Actor11isOverWaterEv);
    return VTABLE_CALL<bool>(Actor_isOverWater, (Actor*) ptr);
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetShadowRadius
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getShadowRadius, _ZTV5Actor, _ZNK5Actor15getShadowRadiusEv);
    return VTABLE_CALL<float>(Actor_getShadowRadius, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanSeeInvisible
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_canSeeInvisible, _ZTV5Actor, _ZNK5Actor15canSeeInvisibleEv);
    return VTABLE_CALL<bool>(Actor_canSeeInvisible, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanSee__JJ
(JNIEnv*, jclass, jlong ptr, jlong actorptr) {
    VTABLE_FIND_OFFSET(Actor_canSeeActor, _ZTV5Actor, _ZNK5Actor6canSeeERK5Actor);
    return VTABLE_CALL<bool>(Actor_canSeeActor, (Actor*) ptr, (Actor*) actorptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanSee__JFFF
(JNIEnv*, jclass, jlong ptr, jfloat x, jfloat y, jfloat z) {
    VTABLE_FIND_OFFSET(Actor_canSeeVec, _ZTV5Actor, _ZNK5Actor6canSeeERK4Vec3);
    return VTABLE_CALL<bool>(Actor_canSeeVec, (Actor*) ptr, Vec3(x, y, z));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsImmobile
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isImmobile, _ZTV5Actor, _ZNK5Actor10isImmobileEv);
    return VTABLE_CALL<bool>(Actor_isImmobile, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsSilent
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isSilent, _ZTV5Actor, _ZNK5Actor8isSilentEv);
    return VTABLE_CALL<bool>(Actor_isSilent, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsPickable
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isPickable, _ZTV5Actor, _ZNK5Actor10isPickableEv);
    return VTABLE_CALL<bool>(Actor_isPickable, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsFishable
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isFishable, _ZTV5Actor, _ZNK5Actor10isFishableEv);
    return VTABLE_CALL<bool>(Actor_isFishable, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsSleeping
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isSleeping, _ZTV5Actor, _ZNK5Actor10isSleepingEv);
    return VTABLE_CALL<bool>(Actor_isSleeping, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsShootable
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isShootable, _ZTV5Actor, _ZNK5Actor11isShootableEv);
    return VTABLE_CALL<bool>(Actor_isShootable, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsBlocking
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isBlocking, _ZTV5Actor, _ZNK5Actor10isBlockingEv);
    return VTABLE_CALL<bool>(Actor_isBlocking, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsAlive
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isAlive, _ZTV5Actor, _ZNK5Actor7isAliveEv);
    return VTABLE_CALL<bool>(Actor_isAlive, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsOnFire
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isOnFire, _ZTV5Actor, _ZNK5Actor8isOnFireEv);
    return VTABLE_CALL<bool>(Actor_isOnFire, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetOnFire
(JNIEnv*, jclass, jlong ptr, jint fireTicks) {
    VTABLE_FIND_OFFSET(Actor_setOnFire, _ZTV5Actor, _ZN5Actor9setOnFireEi);
    VTABLE_CALL<void>(Actor_setOnFire, (Actor*) ptr, fireTicks);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsOnHotBlock
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isOnHotBlock, _ZTV5Actor, _ZNK5Actor12isOnHotBlockEv);
    return VTABLE_CALL<bool>(Actor_isOnHotBlock, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsCreativeModeAllowed
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isCreativeModeAllowed, _ZTV5Actor, _ZNK5Actor21isCreativeModeAllowedEv);
    return VTABLE_CALL<bool>(Actor_isCreativeModeAllowed, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsSurfaceMob
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isSurfaceMob, _ZTV5Actor, _ZNK5Actor12isSurfaceMobEv);
    return VTABLE_CALL<bool>(Actor_isSurfaceMob, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsTargetable
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isTargetable, _ZTV5Actor, _ZNK5Actor12isTargetableEv);
    return VTABLE_CALL<bool>(Actor_isTargetable, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsLocalPlayer
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isLocalPlayer, _ZTV5Actor, _ZNK5Actor13isLocalPlayerEv);
    return VTABLE_CALL<bool>(Actor_isLocalPlayer, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsPlayer
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isPlayer, _ZTV5Actor, _ZNK5Actor8isPlayerEv);
    return VTABLE_CALL<bool>(Actor_isPlayer, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanAttack
(JNIEnv*, jclass, jlong ptr, jlong victim, jboolean someBool) {
    VTABLE_FIND_OFFSET(Actor_canAttack, _ZTV5Actor, _ZNK5Actor9canAttackEP5Actorb);
    return VTABLE_CALL<bool>(Actor_canAttack, (Actor*) ptr, (Actor*) victim, someBool);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsValidTarget
(JNIEnv*, jclass, jlong ptr, jlong potentialTarget) {
    VTABLE_FIND_OFFSET(Actor_isValidTarget, _ZTV5Actor, _ZNK5Actor13isValidTargetEP5Actor);
    return VTABLE_CALL<bool>(Actor_isValidTarget, (Actor*) ptr, (Actor*) potentialTarget);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeAttack
(JNIEnv*, jclass, jlong ptr, jlong victim) {
    VTABLE_FIND_OFFSET(Actor_attack, _ZTV5Actor, _ZN5Actor6attackER5Actor);
    VTABLE_CALL<void>(Actor_attack, (Actor*) ptr, *((Actor*) victim));
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativePerformRangedAttack
(JNIEnv*, jclass, jlong ptr, jlong victim, jfloat distanceFactor) {
    VTABLE_FIND_OFFSET(Actor_performRangedAttack, _ZTV5Actor, _ZN5Actor19performRangedAttackER5Actorf);
    VTABLE_CALL<void>(Actor_performRangedAttack, (Actor*) ptr, *((Actor*) victim), distanceFactor);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetEquipmentCount
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getEquipmentCount, _ZTV5Actor, _ZNK5Actor17getEquipmentCountEv);
    return VTABLE_CALL<int>(Actor_getEquipmentCount, (Actor*) ptr);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetInventorySize
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getInventorySize, _ZTV5Actor, _ZN5Actor16getInventorySizeEv);
    return VTABLE_CALL<int>(Actor_getInventorySize, (Actor*) ptr);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetEquipSlots
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getEquipSlots, _ZTV5Actor, _ZNK5Actor13getEquipSlotsEv);
    return VTABLE_CALL<int>(Actor_getEquipSlots, (Actor*) ptr);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetChestSlots
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getChestSlots, _ZTV5Actor, _ZNK5Actor13getChestSlotsEv);
    return VTABLE_CALL<int>(Actor_getChestSlots, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanPowerJump
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_canPowerJump, _ZTV5Actor, _ZNK5Actor12canPowerJumpEv);
    return VTABLE_CALL<bool>(Actor_canPowerJump, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetCanPowerJump
(JNIEnv*, jclass, jlong ptr, jboolean canPowerJump) {
    VTABLE_FIND_OFFSET(Actor_setCanPowerJump, _ZTV5Actor, _ZNK5Actor15setCanPowerJumpEb);
    VTABLE_CALL<void>(Actor_setCanPowerJump, (Actor*) ptr, canPowerJump);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsJumping
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isJumping, _ZTV5Actor, _ZNK5Actor9isJumpingEv);
    return VTABLE_CALL<bool>(Actor_isJumping, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeDoFireHurt
(JNIEnv*, jclass, jlong ptr, jint amount) {
    VTABLE_FIND_OFFSET(Actor_doFireHurt, _ZTV5Actor, _ZN5Actor10doFireHurtEi);
    VTABLE_CALL<void>(Actor_doFireHurt, (Actor*) ptr, amount);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeOnLightningHit
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_onLightningHit, _ZTV5Actor, _ZN5Actor14onLightningHitEv);
    VTABLE_CALL<void>(Actor_onLightningHit, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeFeed
(JNIEnv*, jclass, jlong ptr, jint amount) {
    VTABLE_FIND_OFFSET(Actor_feed, _ZTV5Actor, _ZN5Actor4feedEi);
    VTABLE_CALL<void>(Actor_feed, (Actor*) ptr, amount);
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetPickRadius
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getPickRadius, _ZTV5Actor, _ZNK5Actor13getPickRadiusEv);
    return VTABLE_CALL<float>(Actor_getPickRadius, (Actor*) ptr);
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetArmor
(JNIEnv*, jclass, jlong ptr, jint slot) {
    VTABLE_FIND_OFFSET(Actor_getArmor, _ZTV5Actor, _ZNK5Actor8getArmorE9ArmorSlot);
    ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getArmor, (Actor*) ptr, (ArmorSlot) slot);
    if(stack == nullptr) return 0;
    return (jlong) stack;
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetArmor
(JNIEnv*, jclass, jlong ptr, jint slot, jlong stack) {
    VTABLE_FIND_OFFSET(Actor_setArmor, _ZTV5Actor, _ZN5Actor8setArmorE9ArmorSlotRK9ItemStack);
    VTABLE_CALL<void, ArmorSlot, ItemStack const&>(Actor_setArmor, (Actor*) ptr, (ArmorSlot) slot, *((ItemStack*) stack));
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetArmorMaterialTypeInSlot
(JNIEnv*, jclass, jlong ptr, jint slot) {
    VTABLE_FIND_OFFSET(Actor_getArmorMaterialTypeInSlot, _ZTV5Actor, _ZNK5Actor26getArmorMaterialTypeInSlotE9ArmorSlot);
    return VTABLE_CALL<MaterialType>(Actor_getArmorMaterialTypeInSlot, (Actor*) ptr, (ArmorSlot) slot);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetArmorMaterialTextureTypeInSlot
(JNIEnv*, jclass, jlong ptr, jint slot) {
    VTABLE_FIND_OFFSET(Actor_getArmorMaterialTextureTypeInSlot, _ZTV5Actor, _ZNK5Actor33getArmorMaterialTextureTypeInSlotE9ArmorSlot);
    return VTABLE_CALL<ArmorTextureType>(Actor_getArmorMaterialTextureTypeInSlot, (Actor*) ptr, (ArmorSlot) slot);
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetEquippedSlot
(JNIEnv*, jclass, jlong ptr, jint slot) {
    VTABLE_FIND_OFFSET(Actor_getEquippedSlot, _ZTV5Actor, _ZNK5Actor15getEquippedSlotE13EquipmentSlot);
    ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getEquippedSlot, (Actor*) ptr, (EquipmentSlot) slot);
    if(stack == nullptr) return 0;
    return (jlong) stack;
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetEquippedSlot
(JNIEnv*, jclass, jlong ptr, jint slot, jlong stack) {
    VTABLE_FIND_OFFSET(Actor_setEquippedSlot, _ZTV5Actor, _ZN5Actor15setEquippedSlotE13EquipmentSlotRK9ItemStack);
    VTABLE_CALL<void, EquipmentSlot, ItemStack const&>(Actor_setEquippedSlot, (Actor*) ptr, (EquipmentSlot) slot, *((ItemStack*) stack));
}
JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_nativeGetCarriedItem
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
    ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, (Actor*) ptr);
    if(stack == nullptr) return 0;
    return (jlong) stack;
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetCarriedItem
(JNIEnv*, jclass, jlong ptr, jlong stackptr) {
    VTABLE_FIND_OFFSET(Actor_setCarriedItem, _ZTV5Actor, _ZN5Actor14setCarriedItemERK9ItemStack);
    VTABLE_CALL<void, ItemStack const&>(Actor_setCarriedItem, (Actor*) ptr, *((ItemStack*) stackptr));
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetOffhandSlot
(JNIEnv*, jclass, jlong ptr, jlong stackptr) {
    VTABLE_FIND_OFFSET(Actor_setOffhandSlot, _ZTV5Actor, _ZN5Actor14setOffhandSlotERK9ItemStack);
    VTABLE_CALL<void, ItemStack const&>(Actor_setOffhandSlot, (Actor*) ptr, *((ItemStack*) stackptr));
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeConsumeTotem
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_consumeTotem, _ZTV5Actor, _ZN5Actor12consumeTotemEv);
    VTABLE_CALL<void>(Actor_consumeTotem, (Actor*) ptr);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetPortalCooldown
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getPortalCooldown, _ZTV5Actor, _ZNK5Actor17getPortalCooldownEv);
    return VTABLE_CALL<int>(Actor_getPortalCooldown, (Actor*) ptr);
}
JNIEXPORT jint JNICALL Java_vsdum_kex_natives_Actor_nativeGetPortalWaitTime
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getPortalWaitTime, _ZTV5Actor, _ZNK5Actor17getPortalWaitTimeEv);
    return VTABLE_CALL<int>(Actor_getPortalWaitTime, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanBePulledIntoVehicle
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_canBePulledIntoVehicle, _ZTV5Actor, _ZNK5Actor22canBePulledIntoVehicleEv);
    return VTABLE_CALL<bool>(Actor_canBePulledIntoVehicle, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeInCaravan
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_inCaravan, _ZTV5Actor, _ZNK5Actor9inCaravanEv);
    return VTABLE_CALL<bool>(Actor_inCaravan, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeHeal
(JNIEnv*, jclass, jlong ptr, jint amount) {
    VTABLE_FIND_OFFSET(Actor_heal, _ZTV5Actor, _ZN5Actor4healEi);
    VTABLE_CALL<void>(Actor_heal, (Actor*) ptr, amount);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsInvertedHealAndHarm
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isInvertedHealAndHarm, _ZTV5Actor, _ZNK5Actor21isInvertedHealAndHarmEv);
    return VTABLE_CALL<bool>(Actor_isInvertedHealAndHarm, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanBeAffected__JI
(JNIEnv*, jclass, jlong ptr, jint effectId) {
    VTABLE_FIND_OFFSET(Actor_canBeAffectedI, _ZTV5Actor, _ZNK5Actor13canBeAffectedEi);
    return VTABLE_CALL<bool>(Actor_canBeAffectedI, (Actor*) ptr, effectId);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanBeAffected__JJ
(JNIEnv*, jclass, jlong ptr, jlong mei) {
    VTABLE_FIND_OFFSET(Actor_canBeAffectedMEI, _ZTV5Actor, _ZNK5Actor13canBeAffectedERK17MobEffectInstance);
    return VTABLE_CALL<bool, MobEffectInstance const&>(Actor_canBeAffectedMEI, (Actor*) ptr, *((MobEffectInstance*) mei));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanBeAffectedByArrow
(JNIEnv*, jclass, jlong ptr, jlong mei) {
    VTABLE_FIND_OFFSET(Actor_canBeAffectedByArrow, _ZTV5Actor, _ZNK5Actor20canBeAffectedByArrowERK17MobEffectInstance);
    return VTABLE_CALL<bool, MobEffectInstance const&>(Actor_canBeAffectedByArrow, (Actor*) ptr, *((MobEffectInstance*) mei));
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSwing
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_swing, _ZTV5Actor, _ZN5Actor5swingEv);
    VTABLE_CALL<void>(Actor_swing, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasOutputSignal
(JNIEnv*, jclass, jlong ptr, jshort signal) {
    VTABLE_FIND_OFFSET(Actor_hasOutputSignal, _ZTV5Actor, _ZNK5ActorhasOutputSignalEh);
    return VTABLE_CALL<bool>(Actor_hasOutputSignal, (Actor*) ptr, (unsigned char) signal);
}
JNIEXPORT jshort JNICALL Java_vsdum_kex_natives_Actor_nativeGetOutputSignal
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_getOutputSignal, _ZTV5Actor, _ZNK5Actor15getOutputSignalEv);
    return (jshort) VTABLE_CALL<unsigned char>(Actor_getOutputSignal, (Actor*) ptr);
}
JNIEXPORT jfloat JNICALL Java_vsdum_kex_natives_Actor_nativeGetRiderYRotation
(JNIEnv*, jclass, jlong ptr, jlong rider) {
    VTABLE_FIND_OFFSET(Actor_getRiderYRotation, _ZTV5Actor, _ZNK5Actor17getRiderYRotationERK5Actor);
    return VTABLE_CALL<float>(Actor_getRiderYRotation, (Actor*) ptr, *((Actor*) rider));
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsWorldBuilder
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isWorldBuilder, _ZTV5Actor, _ZNK5Actor14isWorldBuilderEv);
    return VTABLE_CALL<bool>(Actor_isWorldBuilder, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsCreative
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isCreative, _ZTV5Actor, _ZNK5Actor10isCreativeEv);
    return VTABLE_CALL<bool>(Actor_isCreative, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeIsAdventure
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_isAdventure, _ZTV5Actor, _ZNK5Actor11isAdventureEv);
    return VTABLE_CALL<bool>(Actor_isAdventure, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeAdd
(JNIEnv*, jclass, jlong ptr, jlong stackptr) {
    VTABLE_FIND_OFFSET(Actor_add, _ZTV5Actor, _ZN5Actor3addER9ItemStack);
    VTABLE_CALL<void, ItemStack&>(Actor_add, (Actor*) ptr, *((ItemStack*) stackptr));
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeDrop
(JNIEnv*, jclass, jlong ptr, jlong stackptr, jboolean someBool) {
    VTABLE_FIND_OFFSET(Actor_drop, _ZTV5Actor, _ZN5Actor4dropERK9ItemStackb);
    VTABLE_CALL<void, ItemStack const&, bool>(Actor_drop, (Actor*) ptr, *((ItemStack*) stackptr), someBool);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSetAuxValue
(JNIEnv*, jclass, jlong ptr, jint value) {
    VTABLE_FIND_OFFSET(Actor_setAuxValue, _ZTV5Actor, _ZN5Actor11setAuxValueEi);
    VTABLE_CALL<void>(Actor_setAuxValue, (Actor*) ptr, value);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeWobble
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_wobble, _ZTV5Actor, _ZN5Actor6wobbleEv);
    VTABLE_CALL<void>(Actor_wobble, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeHasHurt
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_wasHurt, _ZTV5Actor, _ZN5Actor7wasHurtEv);
    return VTABLE_CALL<bool>(Actor_wasHurt, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeStartSpinAttack
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_startSpinAttack, _ZTV5Actor, _ZN5Actor15startSpinAttackEv);
    VTABLE_CALL<void>(Actor_startSpinAttack, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeStopSpinAttack
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_stopSpinAttack, _ZTV5Actor, _ZN5Actor14stopSpinAttackEv);
    VTABLE_CALL<void>(Actor_stopSpinAttack, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeKill
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_kill, _ZTV5Actor, _ZN5Actor4killEv);
    VTABLE_CALL<void>(Actor_kill, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeShouldTryMakeStepSound
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_shouldTryMakeStepSound, _ZTV5Actor, _ZN5Actor22shouldTryMakeStepSoundEv);
    return VTABLE_CALL<bool>(Actor_shouldTryMakeStepSound, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeCanMakeStepSound
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_canMakeStepSound, _ZTV5Actor, _ZNK5Actor16canMakeStepSoundEv);
    return VTABLE_CALL<bool>(Actor_canMakeStepSound, (Actor*) ptr);
}
JNIEXPORT jboolean JNICALL Java_vsdum_kex_natives_Actor_nativeOutOfWorld
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_outOfWorld, _ZTV5Actor, _ZN5Actor10outOfWorldEv);
    return VTABLE_CALL<bool>(Actor_outOfWorld, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativePushOutOfBlocks
(JNIEnv*, jclass, jlong ptr, jfloat x, jfloat y, jfloat z) {
    VTABLE_FIND_OFFSET(Actor_pushOutOfBlocks, _ZTV5Actor, _ZN5Actor15pushOutOfBlocksERK4Vec3);
    VTABLE_CALL<void>(Actor_pushOutOfBlocks, (Actor*) ptr, Vec3(x, y, z));
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeDoWaterSplashEffect
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_doWaterSplashEffect, _ZTV5Actor, _ZN5Actor19doWaterSplashEffectEv);
    VTABLE_CALL<void>(Actor_doWaterSplashEffect, (Actor*) ptr);
}
JNIEXPORT void JNICALL Java_vsdum_kex_natives_Actor_nativeSpawnTrailBubbles
(JNIEnv*, jclass, jlong ptr) {
    VTABLE_FIND_OFFSET(Actor_spawnTrailBubbles, _ZTV5Actor, _ZN5Actor17spawnTrailBubblesEv);
    VTABLE_CALL<void>(Actor_spawnTrailBubbles, (Actor*) ptr);
}



}