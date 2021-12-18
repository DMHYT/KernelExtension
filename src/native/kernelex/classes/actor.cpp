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
JNIEXPORT jboolean JNICALL Java_vsdum_natives_Actor_nativeIsInsidePortal
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



}