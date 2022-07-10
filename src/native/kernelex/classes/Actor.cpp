#include <jni.h>

#include <innercore/id_conversion_map.h>
#include <innercore/item_extra.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>

#include <commontypes.hpp>

#include <ActorUniqueID.hpp>
#include <Attribute.hpp>
#include <Player.hpp>
#include <BreathableComponent.hpp>
#include <Enchant.hpp>
#include <ItemEnchants.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>
#include <MobEffect.hpp>
#include <MobEffectInstance.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_Actor_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    JNIEXPORT jlong JNICALL Java_vsdum_kex_natives_Actor_wrap
    (JNIEnv*, jclass, jlong uid) {
        Actor* actor = Actor::wrap(uid);
        if(actor != nullptr) {
            return (jlong) actor;
        }
        return 0;
    }
    __EXPORT__(jboolean, IsBreakingObstruction) {
        return ((Actor*) ptr)->isBreakingObstruction();
    }
    __EXPORT__(void, SetBreakingObstruction, jboolean breaking) {
        ((Actor*) ptr)->setBreakingObstruction(breaking);
    }
    __EXPORT__(jboolean, IsDancing) {
        return ((Actor*) ptr)->isDancing();
    }
    __EXPORT__(void, SetDancing, jboolean dancing) {
        ((Actor*) ptr)->setDancing(dancing);
    }
    __EXPORT__(void, HealEffects, jint value) {
        ((Actor*) ptr)->healEffects(value);
    }
    __EXPORT__(jint, GetColor) {
        return ((Actor*) ptr)->getColor();
    }
    __EXPORT__(void, SetColor, jint color) {
        ((Actor*) ptr)->setColor((PaletteColor) color);
    }
    __EXPORT__(jint, GetColor2) {
        return ((Actor*) ptr)->getColor2();
    }
    __EXPORT__(void, SetColor2, jint color) {
        ((Actor*) ptr)->setColor2((PaletteColor) color);
    }
    __EXPORT__(jboolean, IsInClouds) {
        return ((Actor*) ptr)->isInClouds();
    }
    __EXPORT__(jboolean, HasUniqueID) {
        return ((Actor*) ptr)->hasUniqueID();
    }
    __EXPORT__(jlong, GetUniqueID) {
        ActorUniqueID* uid = ((Actor*) ptr)->getUniqueID();
        if(uid == nullptr) return 0;
        return uid->id;
    }
    __EXPORT__(jint, GetHurtDir) {
        return ((Actor*) ptr)->getHurtDir();
    }
    __EXPORT__(void, SetHurtDir, jint dir) {
        ((Actor*) ptr)->setHurtDir(dir);
    }
    __EXPORT__(jboolean, IsEnchanted) {
        VTABLE_FIND_OFFSET(Actor_isEnchanted, _ZTV5Actor, _ZNK5Actor11isEnchantedEv);
        return VTABLE_CALL<bool>(Actor_isEnchanted, (Actor*) ptr);
    }
    __EXPORT__(void, SetEnchanted, jboolean enchanted) {
        ((Actor*) ptr)->setEnchanted(enchanted);
    }
    __EXPORT__(jint, GetMarkVariant) {
        return ((Actor*) ptr)->getMarkVariant();
    }
    __EXPORT__(void, SetMarkVariant, jint variant) {
        ((Actor*) ptr)->setMarkVariant(variant);
    }
    __EXPORT__(jboolean, HasDimension) {
        return ((Actor*) ptr)->hasDimension();
    }
    __EXPORT__(jboolean, CanChangeDimensions) {
        VTABLE_FIND_OFFSET(Actor_canChangeDimensions, _ZTV5Actor, _ZNK5Actor19canChangeDimensionsEv);
        return VTABLE_CALL<bool>(Actor_canChangeDimensions, (Actor*) ptr);
    }
    __EXPORT__(jint, GetDimensionId) {
        VTABLE_FIND_OFFSET(Actor_getDimensionId, _ZTV5Actor, _ZNK5Actor14getDimensionIdEv);
        return VTABLE_CALL<int>(Actor_getDimensionId, (Actor*) ptr);
    }
    __EXPORT__(jlong, GetDimension) {
        Dimension* dim = ((Actor*) ptr)->getDimension();
        if(dim == nullptr) return 0;
        return (jlong) dim;
    }
    __EXPORT__(jboolean, WasLastHitByPlayer) {
        return ((Actor*) ptr)->wasLastHitByPlayer();
    }
    __EXPORT__(jboolean, HasSaddle) {
        return ((Actor*) ptr)->hasSaddle();
    }
    __EXPORT__(void, SetSaddle, jboolean saddle) {
        ((Actor*) ptr)->setSaddle(saddle);
    }
    __EXPORT__(jboolean, IsDelayedAttacking) {
        return ((Actor*) ptr)->isDelayedAttacking();
    }
    __EXPORT__(void, SetDelayedAttacking, jboolean delayed) {
        ((Actor*) ptr)->setDelayedAttacking(delayed);
    }
    __EXPORT__(jboolean, CanBeginOrContinueClimbingLadder) {
        return ((Actor*) ptr)->canBeginOrContinueClimbingLadder();
    }
    __EXPORT__(jint, GetStructuralIntegrity) {
        return ((Actor*) ptr)->getStructuralIntegrity();
    }
    __EXPORT__(void, SetStructuralIntegrity, jint integrity) {
        ((Actor*) ptr)->setStructuralIntegrity(integrity);
    }
    __EXPORT__(jboolean, HasLevel) {
        return ((Actor*) ptr)->hasLevel();
    }
    __EXPORT__(jlong, GetLevel) {
        Level* level = ((Actor*) ptr)->getLevel();
        if(level == nullptr) return 0;
        return (jlong) level;
    }
    __EXPORT__(jfloat, GetCameraDistance) {
        return ((Actor*) ptr)->getCameraDistance();
    }
    __EXPORT__(void, SetCameraDistance, jfloat distance) {
        ((Actor*) ptr)->setCameraDistance(distance);
    }
    __EXPORT__(jboolean, IsDoorOpener) {
        return ((Actor*) ptr)->isDoorOpener();
    }
    __EXPORT__(void, SetDoorOpener, jboolean opener) {
        ((Actor*) ptr)->setDoorOpener(opener);
    }
    __EXPORT__(jboolean, HasType, jint type) {
        return ((Actor*) ptr)->hasType((ActorType) type);
    }
    __EXPORT__(jboolean, IsType, jint type) {
        return ((Actor*) ptr)->isType((ActorType) type);
    }
    __EXPORT__(void, RemoveEffectNoUpdate, jint effectId) {
        ((Actor*) ptr)->removeEffectNoUpdate(effectId);
    }
    __EXPORT__(jlong, GetEffect__JJ, jlong mobEffect) {
        MobEffectInstance* effect = ((Actor*) ptr)->getEffect(*(MobEffect*) mobEffect);
        if(effect == nullptr) return 0;
        return (jlong) effect;
    }
    __EXPORT__(jlong, GetEffect__JI, jint effectId) {
        MobEffect* effect = MobEffect::getById(effectId);
        if(effect != nullptr) {
            MobEffectInstance* instance = ((Actor*) ptr)->getEffect(*effect);
            if(effect != nullptr) return (jlong) effect;
        }
        return 0;
    }
    __EXPORT__(jint, GetActiveEffectCount) {
        return ((Actor*) ptr)->getActiveEffectCount();
    }
    __EXPORT__(jboolean, HasEffect__JJ, jlong mobEffect) {
        return ((Actor*) ptr)->hasEffect(*(MobEffect*) mobEffect);
    }
    __EXPORT__(jboolean, HasEffect__JI, jint id) {
        MobEffect* effect = MobEffect::getById(id);
        if(effect != nullptr) {
            return ((Actor*) ptr)->hasEffect(*effect);
        }
        return false;
    }
    __EXPORT__(jboolean, HasAnyVisibleEffects) {
        return ((Actor*) ptr)->hasAnyVisibleEffects();
    }
    __EXPORT__(void, RemoveEffect, jint id) {
        ((Actor*) ptr)->removeEffect(id);
    }
    __EXPORT__(jboolean, HasAnyEffects) {
        return ((Actor*) ptr)->hasAnyEffects();
    }
    __EXPORT__(void, RemoveAllEffects) {
        ((Actor*) ptr)->removeAllEffects();
    }
    __EXPORT__(void, AddEffect, jlong instancePtr) {
        ((Actor*) ptr)->addEffect(*(MobEffectInstance*) instancePtr);
    }
    __EXPORT__(void, RemoveEffects, jboolean harmful, jboolean harmless) {
        Actor* actor = (Actor*) ptr;
        if(actor != nullptr) {
            auto& effects = actor->getAllEffects();
            for(const auto& ieffect : effects) {
                int id = ieffect.getId();
                MobEffect* effect = MobEffect::getById(id);
                if(effect != nullptr) {
                    bool eharmful = effect->isHarmful();
                    if((eharmful && harmful) || (!eharmful && harmless)) {
                        actor->removeEffect(id);
                    }
                }
            }
        }
    }
    __EXPORT__(jboolean, IsInSnow) {
        return ((Actor*) ptr)->isInSnow();
    }
    __EXPORT__(jboolean, CanMate, jlong mate) {
        return ((Actor*) ptr)->canMate(*(Actor*) mate);
    }
    __EXPORT__(jboolean, HasTickingArea) {
        return ((Actor*) ptr)->hasTickingArea();
    }
    __EXPORT__(jlong, GetTickingArea) {
        TickingArea* area = ((Actor*) ptr)->getTickingArea();
        if(area == nullptr) return 0;
        return (jlong) area;
    }
    __EXPORT__(jboolean, GetIsOnScreen) {
        return ((Actor*) ptr)->getIsOnScreen();
    }
    __EXPORT__(void, SetIsOnScreen, jboolean onScreen) {
        ((Actor*) ptr)->setIsOnScreen(onScreen);
    }
    __EXPORT__(jboolean, IsOverScaffolding) {
        return ((Actor*) ptr)->isOverScaffolding();
    }
    __EXPORT__(jboolean, IsInScaffolding) {
        return ((Actor*) ptr)->isInScaffolding();
    }
    __EXPORT__(jboolean, ShouldOrphan, jlong bsptr) {
        return ((Actor*) ptr)->shouldOrphan(*(BlockSource*) bsptr);
    }
    __EXPORT__(jboolean, IsOrphan) {
        return ((Actor*) ptr)->isOrphan();
    }
    __EXPORT__(jboolean, IsPredictedMovementEnabled) {
        return ((Actor*) ptr)->isPredictedMovementEnabled();
    }
    __EXPORT__(jboolean, IsInRain) {
        return ((Actor*) ptr)->isInRain();
    }
    __EXPORT__(jboolean, IsWASDControlled) {
        return ((Actor*) ptr)->isWASDControlled();
    }
    __EXPORT__(void, SetWASDControlled, jboolean wasd) {
        ((Actor*) ptr)->setWASDControlled(wasd);
    }
    __EXPORT__(jboolean, HasPriorityAmmunition) {
        return ((Actor*) ptr)->hasPriorityAmmunition();
    }
    __EXPORT__(jboolean, HasRuntimeID) {
        return ((Actor*) ptr)->hasRuntimeID();
    }
    __EXPORT__(jint, GetVariant) {
        return ((Actor*) ptr)->getVariant();
    }
    __EXPORT__(void, SetVariant, jint variant) {
        ((Actor*) ptr)->setVariant(variant);
    }
    __EXPORT__(jboolean, IsRiding__JJ, jlong ridden) {
        return ((Actor*) ptr)->isRiding((Actor*) ridden);
    }
    __EXPORT__(jboolean, IsRider, jlong rider) {
        return ((Actor*) ptr)->isRider(*(Actor*) rider);
    }
    __EXPORT__(void, RemoveAllRiders, jboolean b1, jboolean b2) {
        ((Actor*) ptr)->removeAllRiders(b1, b2);
    }
    __EXPORT__(jboolean, HasPlayerRider) {
        return ((Actor*) ptr)->hasPlayerRider();
    }
    __EXPORT__(jboolean, IsRiding__J) {
        return ((Actor*) ptr)->isRiding();
    }
    __EXPORT__(jlong, GetRide) {
        Actor* ride = ((Actor*) ptr)->getRide();
        if(ride == nullptr) return 0;
        return (jlong) ride;
    }
    __EXPORT__(jboolean, HasRider) {
        return ((Actor*) ptr)->hasRider();
    }
    __EXPORT__(jboolean, GetStatusFlag, jint flag) {
        return ((Actor*) ptr)->getStatusFlag((ActorFlags) flag);
    }
    __EXPORT__(jboolean, IsChested) {
        return ((Actor*) ptr)->isChested();
    }
    __EXPORT__(jboolean, IsStackable) {
        return ((Actor*) ptr)->isStackable();
    }
    __EXPORT__(jboolean, IsResting) {
        return ((Actor*) ptr)->isResting();
    }
    __EXPORT__(void, SetResting, jboolean resting) {
        ((Actor*) ptr)->setResting(resting);
    }
    __EXPORT__(jfloat, GetHealth) {
        return ((Actor*) ptr)->getHealth();
    }
    __EXPORT__(jfloat, GetMaxHealth) {
        return ((Actor*) ptr)->getMaxHealth();
    }
    __EXPORT__(jint, GetControllingSeat) {
        return ((Actor*) ptr)->getControllingSeat();
    }
    __EXPORT__(void, SetControllingSeat, jint seat) {
        ((Actor*) ptr)->setControllingSeat(seat);
    }
    __EXPORT__(jboolean, IsInsidePortal) {
        return ((Actor*) ptr)->isInsidePortal();
    }
    __EXPORT__(jboolean, HasTeleported) {
        return ((Actor*) ptr)->hasTeleported();
    }
    __EXPORT__(void, MoveRelative, jfloat strafe, jfloat up, jfloat forward, jfloat friction) {
        ((Actor*) ptr)->moveRelative(strafe, up, forward, friction);
    }
    __EXPORT__(jlong, GetRegion) {
        BlockSource* region = ((Actor*) ptr)->getRegion();
        if(region == nullptr) return 0;
        return (jlong) region;
    }
    __EXPORT__(jboolean, IsTame) {
        return ((Actor*) ptr)->isTame();
    }
    __EXPORT__(jboolean, IsLeashed) {
        return ((Actor*) ptr)->isLeashed();
    }
    __EXPORT__(jboolean, IsLeashableType) {
        VTABLE_FIND_OFFSET(Actor_isLeashableType, _ZTV5Actor, _ZNK5Actor15isLeashableTypeEv);
        return VTABLE_CALL<bool>(Actor_isLeashableType, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsMoving) {
        return ((Actor*) ptr)->isMoving();
    }
    __EXPORT__(void, SetMoving, jboolean moving) {
        ((Actor*) ptr)->setMoving(moving);
    }
    __EXPORT__(jboolean, HasTotemEquipped) {
        return ((Actor*) ptr)->hasTotemEquipped();
    }
    __EXPORT__(jboolean, IsAutonomous) {
        return ((Actor*) ptr)->isAutonomous();
    }
    __EXPORT__(void, SetAutonomous, jboolean autonomous) {
        ((Actor*) ptr)->setAutonomous(autonomous);
    }
    __EXPORT__(jboolean, IsPersistent) {
        return ((Actor*) ptr)->isPersistent();
    }
    __EXPORT__(void, RemoveEntity) {
        ((Actor*) ptr)->removeEntity();
    }
    __EXPORT__(void, SetCollidableMob, jboolean collidable) {
        ((Actor*) ptr)->setCollidableMob(collidable);
    }
    __EXPORT__(jboolean, GetCollidableMobNear) {
        return ((Actor*) ptr)->getCollidableMobNear();
    }
    __EXPORT__(void, SetCollidableMobNear, jboolean collidable) {
        ((Actor*) ptr)->setCollidableMobNear(collidable);
    }
    __EXPORT__(jboolean, HasFishingHook) {
        return ((Actor*) ptr)->hasFishingHook();
    }
    __EXPORT__(jboolean, GetChainedDamageEffects) {
        return ((Actor*) ptr)->getChainedDamageEffects();
    }
    __EXPORT__(void, SetChainedDamageEffects, jboolean chained) {
        ((Actor*) ptr)->setChainedDamageEffects(chained);
    }
    __EXPORT__(jboolean, IsPacified) {
        return ((Actor*) ptr)->isPacified();
    }
    __EXPORT__(jfloat, DistanceTo__JJ, jlong actor) {
        return ((Actor*) ptr)->distanceTo(*(Actor*) actor);
    }
    __EXPORT__(jfloat, DistanceTo_JFFF, jfloat x, jfloat y, jfloat z) {
        return ((Actor*) ptr)->distanceTo(Vec3(x, y, z));
    }
    __EXPORT__(jboolean, CanCurrentlySwim) {
        return ((Actor*) ptr)->canCurrentlySwim();
    }
    __EXPORT__(jboolean, IsSwimming) {
        return ((Actor*) ptr)->isSwimming();
    }
    __EXPORT__(jboolean, IsSwimmer) {
        return ((Actor*) ptr)->isSwimmer();
    }
    __EXPORT__(void, SetSwimmer, jboolean swimmer) {
        ((Actor*) ptr)->setSwimmer(swimmer);
    }
    __EXPORT__(jboolean, HasFamily, jstring family) {
        const char* cfamily = env->GetStringUTFChars(family, 0);
        HashedString hfamily(cfamily);
        env->ReleaseStringUTFChars(family, cfamily);
        return ((Actor*) ptr)->hasFamily(hfamily);
    }
    __EXPORT__(jboolean, HasAttributeBuff, jint buffType) {
        return ((Actor*) ptr)->hasAttributeBuff((AttributeBuffType) buffType);
    }
    __EXPORT__(jboolean, IsClientSide) {
        return ((Actor*) ptr)->isClientSide();
    }
    __EXPORT__(jboolean, IsControlledByLocalInstance) {
        return ((Actor*) ptr)->isControlledByLocalInstance();
    }
    __EXPORT__(jboolean, IsClimbing) {
        return ((Actor*) ptr)->isClimbing();
    }
    __EXPORT__(void, SetClimbing, jboolean climbing) {
        ((Actor*) ptr)->setClimbing(climbing);
    }
    __EXPORT__(jboolean, CanClimb) {
        return ((Actor*) ptr)->canClimb();
    }
    __EXPORT__(void, SetCanClimb, jboolean canClimb) {
        ((Actor*) ptr)->setCanClimb(canClimb);
    }
    __EXPORT__(jint, GetSkinID) {
        return ((Actor*) ptr)->getSkinID();
    }
    __EXPORT__(void, SetSkinID, jint skinID) {
        ((Actor*) ptr)->setSkinID(skinID);
    }
    __EXPORT__(jfloat, GetSpeedInMetersPerSecond) {
        return ((Actor*) ptr)->getSpeedInMetersPerSecond();
    }
    __EXPORT__(jint, GetStrength) {
        return ((Actor*) ptr)->getStrength();
    }
    __EXPORT__(void, SetStrength, jint strength) {
        ((Actor*) ptr)->setStrength(strength);
    }
    __EXPORT__(jint, GetStrengthMax) {
        return ((Actor*) ptr)->getStrengthMax();
    }
    __EXPORT__(void, SetStrengthMax, jint strength) {
        ((Actor*) ptr)->setStrengthMax(strength);
    }
    __EXPORT__(jboolean, GetDamageNearbyMobs) {
        return ((Actor*) ptr)->getDamageNearbyMobs();
    }
    __EXPORT__(void, SetDamageNearbyMobs, jboolean damage) {
        VTABLE_FIND_OFFSET(Actor_setDamageNearbyMobs, _ZTV5Actor, _ZN5Actor19setDamageNearbyMobsEb);
        VTABLE_CALL<void>(Actor_setDamageNearbyMobs, (Actor*) ptr, damage);
    }
    __EXPORT__(jboolean, IsLayingDown) {
        return ((Actor*) ptr)->isLayingDown();
    }
    __EXPORT__(void, SetLayingDown, jboolean laying) {
        ((Actor*) ptr)->setLayingDown(laying);
    }
    __EXPORT__(jboolean, GetTempted) {
        return ((Actor*) ptr)->getTempted();
    }
    __EXPORT__(void, SetTempted, jboolean tempted) {
        ((Actor*) ptr)->setTempted(tempted);
    }
    __EXPORT__(void, DropTowards, jint id, jint count, jint data, jlong extra, jfloat x, jfloat y, jfloat z) {
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item != nullptr && count > 0) {
            ItemStack stack(*item, count, data);
            if(extra != 0) {
                ((ItemInstanceExtra*) extra)->apply(&stack);
            }
            ((Actor*) ptr)->dropTowards(stack, Vec3(x, y, z));
        }
    }
    __EXPORT__(jboolean, IsTrading) {
        return ((Actor*) ptr)->isTrading();
    }
    __EXPORT__(jboolean, InDownwardFlowingLiquid) {
        return ((Actor*) ptr)->inDownwardFlowingLiquid();
    }
    __EXPORT__(jint, GetJumpDuration) {
        return ((Actor*) ptr)->getJumpDuration();
    }
    __EXPORT__(void, SetJumpDuration, jint dur) {
        ((Actor*) ptr)->setJumpDuration(dur);
    }
    __EXPORT__(jboolean, IsScared) {
        return ((Actor*) ptr)->isScared();
    }
    __EXPORT__(void, SetScared, jboolean scared) {
        ((Actor*) ptr)->setScared(scared);
    }
    __EXPORT__(jboolean, IsSitting) {
        return ((Actor*) ptr)->isSitting();
    }
    __EXPORT__(void, SetSitting, jboolean sitting) {
        VTABLE_FIND_OFFSET(Actor_setSitting, _ZTV5Actor, _ZN5Actor10setSittingEb);
        VTABLE_CALL<void>(Actor_setSitting, (Actor*) ptr, sitting);
    }
    __EXPORT__(jboolean, IsBaby) {
        return ((Actor*) ptr)->isBaby();
    }
    __EXPORT__(jboolean, IsIgnited) {
        return ((Actor*) ptr)->isIgnited();
    }
    __EXPORT__(jint, GetLifeSpan) {
        VTABLE_FIND_OFFSET(Actor_getLifeSpan, _ZTV5Actor, _ZNK5Actor11getLifeSpanEv);
        return VTABLE_CALL<int>(Actor_getLifeSpan, (Actor*) ptr);
    }
    __EXPORT__(void, SetLimitedLife, jint life) {
        ((Actor*) ptr)->setLimitedLife(life);
    }
    __EXPORT__(jboolean, IsInvisible) {
        VTABLE_FIND_OFFSET(Actor_isInvisible, _ZTV5Actor, _ZNK5Actor11isInvisibleEv);
        return VTABLE_CALL<bool>(Actor_isInvisible, (Actor*) ptr);
    }
    __EXPORT__(void, SetInvisible, jboolean invisible) {
        ((Actor*) ptr)->setInvisible(invisible);
    }
    __EXPORT__(jboolean, IsInWorld) {
        return ((Actor*) ptr)->isInWorld();
    }
    __EXPORT__(jboolean, IsInLove) {
        return ((Actor*) ptr)->isInLove();
    }
    __EXPORT__(void, SetInLove, jlong loverptr) {
        ((Actor*) ptr)->setInLove((Actor*) loverptr);
    }
    __EXPORT__(jboolean, IsDoorBreaker) {
        return ((Actor*) ptr)->isDoorBreaker();
    }
    __EXPORT__(void, SetDoorBreaker, jboolean breaker) {
        ((Actor*) ptr)->setDoorBreaker(breaker);
    }
    __EXPORT__(jboolean, IsWalker) {
        return ((Actor*) ptr)->isWalker();
    }
    __EXPORT__(void, SetWalker, jboolean walker) {
        ((Actor*) ptr)->setWalker(walker);
    }
    __EXPORT__(jboolean, IsCharged) {
        return ((Actor*) ptr)->isCharged();
    }
    __EXPORT__(void, SetCharged, jboolean charged) {
        ((Actor*) ptr)->setCharged(charged);
    }
    __EXPORT__(jboolean, CanFly) {
        return ((Actor*) ptr)->canFly();
    }
    __EXPORT__(void, SetCanFly, jboolean canFly) {
        ((Actor*) ptr)->setCanFly(canFly);
    }
    __EXPORT__(jboolean, IsInPrecipitation) {
        return ((Actor*) ptr)->isInPrecipitation();
    }
    __EXPORT__(void, SetAABB, jfloat x1, jfloat y1, jfloat z1, jfloat x2, jfloat y2, jfloat z2) {
        ((Actor*) ptr)->setAABB(AABB(x1, y1, z1, x2, y2, z2));
    }
    __EXPORT__(jboolean, IsSafeToSleepNear) {
        return ((Actor*) ptr)->isSafeToSleepNear();
    }
    __EXPORT__(void, SetBlockTarget, jint x, jint y, jint z) {
        return ((Actor*) ptr)->setBlockTarget(BlockPos(x, y, z));
    }
    __EXPORT__(jboolean, IsAngry) {
        return ((Actor*) ptr)->isAngry();
    }
    __EXPORT__(jboolean, IsPowered) {
        return ((Actor*) ptr)->isPowered();
    }
    __EXPORT__(void, SetPowered, jboolean powered) {
        ((Actor*) ptr)->setPowered(powered);
    }
    __EXPORT__(jboolean, IsSheared) {
        return ((Actor*) ptr)->isSheared();
    }
    __EXPORT__(jboolean, IsOutOfControl) {
        return ((Actor*) ptr)->isOutOfControl();
    }
    __EXPORT__(jboolean, IsSneaking) {
        return ((Actor*) ptr)->isSneaking();
    }
    __EXPORT__(void, SetSneaking, jboolean sneaking) {
        VTABLE_FIND_OFFSET(Actor_setSneaking, _ZTV5Actor, _ZNK5Actor11setSneakingEb);
        VTABLE_CALL<void>(Actor_setSneaking, (Actor*) ptr, sneaking);
    }
    __EXPORT__(jlong, GetTarget) {
        Actor* target = ((Actor*) ptr)->getTarget();
        if(target == nullptr) return 0;
        return (jlong) target;
    }
    __EXPORT__(void, SetTarget, jlong targetptr) {
        VTABLE_FIND_OFFSET(Actor_setTarget, _ZTV5Actor, _ZN5Actor9setTargetEP5Actor);
        VTABLE_CALL<void>(Actor_setTarget, (Actor*) ptr, (Actor*) targetptr);
    }
    __EXPORT__(void, SetStunned, jboolean stunned) {
        ((Actor*) ptr)->setStunned(stunned);
    }
    __EXPORT__(jshort, GetTotalAirSupply) {
        return ((Actor*) ptr)->getTotalAirSupply();
    }
    __EXPORT__(jshort, GetAirSupply) {
        return ((Actor*) ptr)->getAirSupply();
    }
    __EXPORT__(jboolean, IsInThunderstorm) {
        return ((Actor*) ptr)->isInThunderstorm();
    }
    __EXPORT__(jboolean, IsBribed) {
        return ((Actor*) ptr)->isBribed();
    }
    __EXPORT__(jboolean, IsStanding) {
        return ((Actor*) ptr)->isStanding();
    }
    __EXPORT__(void, SetStanding, jboolean standing) {
        VTABLE_FIND_OFFSET(Actor_setStanding, _ZTV5Actor, _ZN5Actor11setStandingEb);
        VTABLE_CALL<void>(Actor_setStanding, (Actor*) ptr, standing);
    }
    __EXPORT__(jint, GetShakeTime) {
        return ((Actor*) ptr)->getShakeTime();
    }
    __EXPORT__(void, SetShakeTime, jint time) {
        ((Actor*) ptr)->setShakeTime(time);
    }
    __EXPORT__(jboolean, HasCategory, jint category) {
        return ((Actor*) ptr)->hasCategory((ActorCategory) category);
    }
    __EXPORT__(jfloat, GetVerticalSpeedInMetersPerSecond) {
        return ((Actor*) ptr)->getVerticalSpeedInMetersPerSecond();
    }
    __EXPORT__(jboolean, IsTrusting) {
        return ((Actor*) ptr)->isTrusting();
    }
    __EXPORT__(jfloat, GetRadius) {
        return ((Actor*) ptr)->getRadius();
    }
    __EXPORT__(jboolean, HasComponent, jstring component) {
        const char* ccomponent = env->GetStringUTFChars(component, 0);
        HashedString hcomponent(ccomponent);
        env->ReleaseStringUTFChars(component, ccomponent);
        VTABLE_FIND_OFFSET(Actor_hasComponent, _ZTV5Actor, _ZNK5Actor12hasComponentERK12HashedString);
        return VTABLE_CALL<bool>(Actor_hasComponent, (Actor*) ptr, hcomponent);
    }
    __EXPORT__(jint, GetOnDeathExperience) {
        VTABLE_FIND_OFFSET(Actor_getOnDeathExperience, _ZTV5Actor, _ZN5Actor20getOnDeathExperienceEv);
        return VTABLE_CALL<int>(Actor_getOnDeathExperience, (Actor*) ptr);
    }
    // TODO getInterpolatedRidingPosition, getInterpolatedBodyRot, getInterpolatedHeadRot
    __EXPORT__(jfloat, GetInterpolatedBodyYaw, jfloat partialTicks) {
        VTABLE_FIND_OFFSET(Actor_getInterpolatedBodyYaw, _ZTV5Actor, _ZNK5Actor22getInterpolatedBodyYawEf);
        return VTABLE_CALL<float>(Actor_getInterpolatedBodyYaw, (Actor*) ptr, partialTicks);
    }
    __EXPORT__(jfloat, GetYawSpeedInDegreesPerSecond) {
        VTABLE_FIND_OFFSET(Actor_getYawSpeedInDegreesPerSecond, _ZTV5Actor, _ZNK5Actor29getYawSpeedInDegreesPerSecondEv);
        return VTABLE_CALL<float>(Actor_getYawSpeedInDegreesPerSecond, (Actor*) ptr);
    }
    __EXPORT__(jfloat, GetInterpolatedWalkAnimSpeed, jfloat partialTicks) {
        VTABLE_FIND_OFFSET(Actor_getInterpolatedWalkAnimSpeed, _ZTV5Actor, _ZNK5Actor28getInterpolatedWalkAnimSpeedEf);
        return VTABLE_CALL<float>(Actor_getInterpolatedWalkAnimSpeed, (Actor*) ptr, partialTicks);
    }
    // TODO getInterpolatedRidingOffset
    __EXPORT__(jboolean, IsFireImmune) {
        VTABLE_FIND_OFFSET(Actor_isFireImmune, _ZTV5Actor, _ZNK5Actor12isFireImmuneEv);
        return VTABLE_CALL<bool>(Actor_isFireImmune, (Actor*) ptr);
    }
    __EXPORT__(jboolean, BreaksFallingBlocks) {
        VTABLE_FIND_OFFSET(Actor_breaksFallingBlocks, _ZTV5Actor, _ZNK5Actor19breaksFallingBlocksEv);
        return VTABLE_CALL<bool>(Actor_breaksFallingBlocks, (Actor*) ptr);
    }
    // TODO blockedByShield, teleportTo
    __EXPORT__(void, ChorusFruitTeleport, jfloat x, jfloat y, jfloat z) {
        VTABLE_FIND_OFFSET(Actor_chorusFruitTeleport, _ZTV5Actor, _ZN5Actor19chorusFruitTeleportER4Vec3);
        VTABLE_CALL<void>(Actor_chorusFruitTeleport, (Actor*) ptr, Vec3(x, y, z));
    }
    __EXPORT__(void, LerpTo, jdouble x, jdouble y, jdouble z, jfloat rotX, jfloat rotY) {
        VTABLE_FIND_OFFSET(Actor_lerpTo, _ZTV5Actor, _ZN5Actor6lerpToERK4Vec3RK4Vec2i);
        VTABLE_CALL<void>(Actor_lerpTo, (Actor*) ptr, Vec3(x, y, z), Vec2(rotX, rotY), 0);
    }
    __EXPORT__(void, LerpMotion, jdouble x, jdouble y, jdouble z) {
        VTABLE_FIND_OFFSET(Actor_lerpMotion, _ZTV5Actor, _ZN5Actor10lerpMotionERK4Vec3);
        VTABLE_CALL<void>(Actor_lerpMotion, (Actor*) ptr, Vec3(x, y, z));
    }
    __EXPORT__(jfloat, GetRidingHeight) {
        VTABLE_FIND_OFFSET(Actor_getRidingHeight, _ZTV5Actor, _ZN5Actor15getRidingHeightEv);
        return VTABLE_CALL<float>(Actor_getRidingHeight, (Actor*) ptr);
    }
    __EXPORT__(void, StartRiding, jlong riddenPtr) {
        VTABLE_FIND_OFFSET(Actor_startRiding, _ZTV5Actor, _ZN5Actor11startRidingER5Actor);
        VTABLE_CALL<void>(Actor_startRiding, (Actor*) ptr, (Actor*) riddenPtr);
    }
    __EXPORT__(void, AddRider, jlong riderPtr) {
        VTABLE_FIND_OFFSET(Actor_addRider, _ZTV5Actor, _ZN5Actor8addRiderER5Actor);
        VTABLE_CALL<void>(Actor_addRider, (Actor*) ptr, (Actor*) riderPtr);
    }
    __EXPORT__(jboolean, Intersects, jfloat x1, jfloat y1, jfloat z1, jfloat x2, jfloat y2, jfloat z2) {
        VTABLE_FIND_OFFSET(Actor_intersects, _ZTV5Actor, _ZNK5Actor10intersectsERK4Vec3S2_);
        return VTABLE_CALL<bool>(Actor_intersects, (Actor*) ptr, Vec3(x1, y1, z1), Vec3(x2, y2, z2));
    }
    __EXPORT__(jboolean, IsFree__JFFF, jfloat x, jfloat y, jfloat z) {
        VTABLE_FIND_OFFSET(Actor_isFree, _ZTV5Actor, _ZN5Actor6isFreeERK4Vec3);
        return VTABLE_CALL<bool>(Actor_isFree, (Actor*) ptr, Vec3(x, y, z));
    }
    __EXPORT__(jboolean, IsFree_JFFFF, jfloat x, jfloat y, jfloat z, jfloat someFloat) {
        VTABLE_FIND_OFFSET(Actor_isFreeConst, _ZTV5Actor, _ZNK5Actor6isFreeERK4Vec3f);
        return VTABLE_CALL<bool>(Actor_isFreeConst, (Actor*) ptr, Vec3(x, y, z), someFloat);
    }
    __EXPORT__(jboolean, IsInWall) {
        VTABLE_FIND_OFFSET(Actor_isInWall, _ZTV5Actor, _ZNK5Actor8isInWallEv);
        return VTABLE_CALL<bool>(Actor_isInWall, (Actor*) ptr);
    }
    __EXPORT__(jboolean, CanShowNameTag) {
        VTABLE_FIND_OFFSET(Actor_canShowNameTag, _ZTV5Actor, _ZNK5Actor14canShowNameTagEv);
        return VTABLE_CALL<bool>(Actor_canShowNameTag, (Actor*) ptr);
    }
    __EXPORT__(jboolean, CanExistInPeaceful) {
        VTABLE_FIND_OFFSET(Actor_canExistInPeaceful, _ZTV5Actor, _ZNK5Actor18canExistInPeacefulEv);
        return VTABLE_CALL<bool>(Actor_canExistInPeaceful, (Actor*) ptr);
    }
    __EXPORT__(void, SetNameTagVisible, jboolean visible) {
        VTABLE_FIND_OFFSET(Actor_setNameTagVisible, _ZTV5Actor, _ZN5Actor17setNameTagVisibleEb);
        VTABLE_CALL<void>(Actor_setNameTagVisible, (Actor*) ptr, visible);
    }
    __EXPORT__(jboolean, GetAlwaysShowNameTag) {
        VTABLE_FIND_OFFSET(Actor_getAlwaysShowNameTag, _ZTV5Actor, _ZNK5Actor20getAlwaysShowNameTagEv);
        return VTABLE_CALL<bool>(Actor_getAlwaysShowNameTag, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsInWater) {
        VTABLE_FIND_OFFSET(Actor_isInWater, _ZTV5Actor, _ZNK5Actor9isInWaterEv);
        return VTABLE_CALL<bool>(Actor_isInWater, (Actor*) ptr);
    }
    __EXPORT__(jboolean, HasEnteredWater) {
        VTABLE_FIND_OFFSET(Actor_hasEnteredWater, _ZTV5Actor, _ZNK5Actor15hasEnteredWaterEv);
        return VTABLE_CALL<bool>(Actor_hasEnteredWater, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsImmersedInWater) {
        VTABLE_FIND_OFFSET(Actor_isImmersedInWater, _ZTV5Actor, _ZNK5Actor17isImmersedInWaterEv);
        return VTABLE_CALL<bool>(Actor_isImmersedInWater, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsInWaterOrRain) {
        VTABLE_FIND_OFFSET(Actor_isInWaterOrRain, _ZTV5Actor, _ZNK5Actor15isInWaterOrRainEv);
        return VTABLE_CALL<bool>(Actor_isInWaterOrRain, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsInLava) {
        VTABLE_FIND_OFFSET(Actor_isInLava, _ZTV5Actor, _ZNK5Actor8isInLavaEv);
        return VTABLE_CALL<bool>(Actor_isInLava, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsUnderLiquid, jint materialType) {
        VTABLE_FIND_OFFSET(Actor_isUnderLiquid, _ZTV5Actor, _ZNK5Actor13isUnderLiquidE12MaterialType);
        return VTABLE_CALL<bool>(Actor_isUnderLiquid, (Actor*) ptr, (MaterialType) materialType);
    }
    __EXPORT__(jboolean, IsOverWater) {
        VTABLE_FIND_OFFSET(Actor_isOverWater, _ZTV5Actor, _ZNK5Actor11isOverWaterEv);
        return VTABLE_CALL<bool>(Actor_isOverWater, (Actor*) ptr);
    }
    __EXPORT__(jfloat, GetShadowRadius) {
        VTABLE_FIND_OFFSET(Actor_getShadowRadius, _ZTV5Actor, _ZNK5Actor15getShadowRadiusEv);
        return VTABLE_CALL<float>(Actor_getShadowRadius, (Actor*) ptr);
    }
    __EXPORT__(jboolean, CanSeeInvisible) {
        VTABLE_FIND_OFFSET(Actor_canSeeInvisible, _ZTV5Actor, _ZNK5Actor15canSeeInvisibleEv);
        return VTABLE_CALL<bool>(Actor_canSeeInvisible, (Actor*) ptr);
    }
    __EXPORT__(jboolean, CanSee__JJ, jlong actorptr) {
        VTABLE_FIND_OFFSET(Actor_canSeeActor, _ZTV5Actor, _ZNK5Actor6canSeeERK5Actor);
        return VTABLE_CALL<bool>(Actor_canSeeActor, (Actor*) ptr, (Actor*) actorptr);
    }
    __EXPORT__(jboolean, CanSee__JFFF, jfloat x, jfloat y, jfloat z) {
        VTABLE_FIND_OFFSET(Actor_canSeeVec, _ZTV5Actor, _ZNK5Actor6canSeeERK4Vec3);
        return VTABLE_CALL<bool>(Actor_canSeeVec, (Actor*) ptr, Vec3(x, y, z));
    }
    __EXPORT__(jboolean, IsImmobile) {
        VTABLE_FIND_OFFSET(Actor_isImmobile, _ZTV5Actor, _ZNK5Actor10isImmobileEv);
        return VTABLE_CALL<bool>(Actor_isImmobile, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsSilent) {
        VTABLE_FIND_OFFSET(Actor_isSilent, _ZTV5Actor, _ZNK5Actor8isSilentEv);
        return VTABLE_CALL<bool>(Actor_isSilent, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsPickable) {
        VTABLE_FIND_OFFSET(Actor_isPickable, _ZTV5Actor, _ZNK5Actor10isPickableEv);
        return VTABLE_CALL<bool>(Actor_isPickable, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsFishable) {
        VTABLE_FIND_OFFSET(Actor_isFishable, _ZTV5Actor, _ZNK5Actor10isFishableEv);
        return VTABLE_CALL<bool>(Actor_isFishable, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsSleeping) {
        VTABLE_FIND_OFFSET(Actor_isSleeping, _ZTV5Actor, _ZNK5Actor10isSleepingEv);
        return VTABLE_CALL<bool>(Actor_isSleeping, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsShootable) {
        VTABLE_FIND_OFFSET(Actor_isShootable, _ZTV5Actor, _ZNK5Actor11isShootableEv);
        return VTABLE_CALL<bool>(Actor_isShootable, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsBlocking) {
        VTABLE_FIND_OFFSET(Actor_isBlocking, _ZTV5Actor, _ZNK5Actor10isBlockingEv);
        return VTABLE_CALL<bool>(Actor_isBlocking, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsAlive) {
        VTABLE_FIND_OFFSET(Actor_isAlive, _ZTV5Actor, _ZNK5Actor7isAliveEv);
        return VTABLE_CALL<bool>(Actor_isAlive, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsOnFire) {
        VTABLE_FIND_OFFSET(Actor_isOnFire, _ZTV5Actor, _ZNK5Actor8isOnFireEv);
        return VTABLE_CALL<bool>(Actor_isOnFire, (Actor*) ptr);
    }
    __EXPORT__(void, SetOnFire, jint fireTicks) {
        VTABLE_FIND_OFFSET(Actor_setOnFire, _ZTV5Actor, _ZN5Actor9setOnFireEi);
        VTABLE_CALL<void>(Actor_setOnFire, (Actor*) ptr, fireTicks);
    }
    __EXPORT__(jboolean, IsOnHotBlock) {
        VTABLE_FIND_OFFSET(Actor_isOnHotBlock, _ZTV5Actor, _ZNK5Actor12isOnHotBlockEv);
        return VTABLE_CALL<bool>(Actor_isOnHotBlock, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsCreativeModeAllowed) {
        VTABLE_FIND_OFFSET(Actor_isCreativeModeAllowed, _ZTV5Actor, _ZNK5Actor21isCreativeModeAllowedEv);
        return VTABLE_CALL<bool>(Actor_isCreativeModeAllowed, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsSurfaceMob) {
        VTABLE_FIND_OFFSET(Actor_isSurfaceMob, _ZTV5Actor, _ZNK5Actor12isSurfaceMobEv);
        return VTABLE_CALL<bool>(Actor_isSurfaceMob, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsTargetable) {
        VTABLE_FIND_OFFSET(Actor_isTargetable, _ZTV5Actor, _ZNK5Actor12isTargetableEv);
        return VTABLE_CALL<bool>(Actor_isTargetable, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsLocalPlayer) {
        VTABLE_FIND_OFFSET(Actor_isLocalPlayer, _ZTV5Actor, _ZNK5Actor13isLocalPlayerEv);
        return VTABLE_CALL<bool>(Actor_isLocalPlayer, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsPlayer) {
        VTABLE_FIND_OFFSET(Actor_isPlayer, _ZTV5Actor, _ZNK5Actor8isPlayerEv);
        return VTABLE_CALL<bool>(Actor_isPlayer, (Actor*) ptr);
    }
    __EXPORT__(jboolean, CanAttack, jlong victim, jboolean someBool) {
        VTABLE_FIND_OFFSET(Actor_canAttack, _ZTV5Actor, _ZNK5Actor9canAttackEP5Actorb);
        return VTABLE_CALL<bool>(Actor_canAttack, (Actor*) ptr, (Actor*) victim, someBool);
    }
    __EXPORT__(jboolean, IsValidTarget, jlong potentialTarget) {
        VTABLE_FIND_OFFSET(Actor_isValidTarget, _ZTV5Actor, _ZNK5Actor13isValidTargetEP5Actor);
        return VTABLE_CALL<bool>(Actor_isValidTarget, (Actor*) ptr, (Actor*) potentialTarget);
    }
    __EXPORT__(void, Attack, jlong victim) {
        VTABLE_FIND_OFFSET(Actor_attack, _ZTV5Actor, _ZN5Actor6attackER5Actor);
        VTABLE_CALL<void>(Actor_attack, (Actor*) ptr, (Actor*) victim);
    }
    __EXPORT__(void, PerformRangedAttack, jlong victim, jfloat distanceFactor) {
        VTABLE_FIND_OFFSET(Actor_performRangedAttack, _ZTV5Actor, _ZN5Actor19performRangedAttackER5Actorf);
        VTABLE_CALL<void>(Actor_performRangedAttack, (Actor*) ptr, (Actor*) victim, distanceFactor);
    }
    __EXPORT__(jint, GetEquipmentCount) {
        VTABLE_FIND_OFFSET(Actor_getEquipmentCount, _ZTV5Actor, _ZNK5Actor17getEquipmentCountEv);
        return VTABLE_CALL<int>(Actor_getEquipmentCount, (Actor*) ptr);
    }
    __EXPORT__(jint, GetInventorySize) {
        VTABLE_FIND_OFFSET(Actor_getInventorySize, _ZTV5Actor, _ZN5Actor16getInventorySizeEv);
        return VTABLE_CALL<int>(Actor_getInventorySize, (Actor*) ptr);
    }
    __EXPORT__(jint, GetEquipSlots) {
        VTABLE_FIND_OFFSET(Actor_getEquipSlots, _ZTV5Actor, _ZNK5Actor13getEquipSlotsEv);
        return VTABLE_CALL<int>(Actor_getEquipSlots, (Actor*) ptr);
    }
    __EXPORT__(jint, GetChestSlots) {
        VTABLE_FIND_OFFSET(Actor_getChestSlots, _ZTV5Actor, _ZNK5Actor13getChestSlotsEv);
        return VTABLE_CALL<int>(Actor_getChestSlots, (Actor*) ptr);
    }
    __EXPORT__(jboolean, CanPowerJump) {
        VTABLE_FIND_OFFSET(Actor_canPowerJump, _ZTV5Actor, _ZNK5Actor12canPowerJumpEv);
        return VTABLE_CALL<bool>(Actor_canPowerJump, (Actor*) ptr);
    }
    __EXPORT__(void, SetCanPowerJump, jboolean canPowerJump) {
        VTABLE_FIND_OFFSET(Actor_setCanPowerJump, _ZTV5Actor, _ZNK5Actor15setCanPowerJumpEb);
        VTABLE_CALL<void>(Actor_setCanPowerJump, (Actor*) ptr, canPowerJump);
    }
    __EXPORT__(jboolean, IsJumping) {
        VTABLE_FIND_OFFSET(Actor_isJumping, _ZTV5Actor, _ZNK5Actor9isJumpingEv);
        return VTABLE_CALL<bool>(Actor_isJumping, (Actor*) ptr);
    }
    __EXPORT__(void, DoFireHurt, jint amount) {
        VTABLE_FIND_OFFSET(Actor_doFireHurt, _ZTV5Actor, _ZN5Actor10doFireHurtEi);
        VTABLE_CALL<void>(Actor_doFireHurt, (Actor*) ptr, amount);
    }
    __EXPORT__(void, OnLightningHit) {
        VTABLE_FIND_OFFSET(Actor_onLightningHit, _ZTV5Actor, _ZN5Actor14onLightningHitEv);
        VTABLE_CALL<void>(Actor_onLightningHit, (Actor*) ptr);
    }
    __EXPORT__(void, Feed, jint amount) {
        VTABLE_FIND_OFFSET(Actor_feed, _ZTV5Actor, _ZN5Actor4feedEi);
        VTABLE_CALL<void>(Actor_feed, (Actor*) ptr, amount);
    }
    __EXPORT__(jfloat, GetPickRadius) {
        VTABLE_FIND_OFFSET(Actor_getPickRadius, _ZTV5Actor, _ZNK5Actor13getPickRadiusEv);
        return VTABLE_CALL<float>(Actor_getPickRadius, (Actor*) ptr);
    }
    __EXPORT__(jlong, GetArmor, jint slot) {
        VTABLE_FIND_OFFSET(Actor_getArmor, _ZTV5Actor, _ZNK5Actor8getArmorE9ArmorSlot);
        ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getArmor, (Actor*) ptr, (ArmorSlot) slot);
        if(stack == nullptr) return 0;
        return (jlong) stack;
    }
    __EXPORT__(void, SetArmor, jint slot, jint id, jint count, jint data, jlong extra) {
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item != nullptr && count > 0) {
            ItemStack stack(*item, count, data);
            if(extra != 0) {
                ((ItemInstanceExtra*) extra)->apply(&stack);
            }
            VTABLE_FIND_OFFSET(Actor_setArmor, _ZTV5Actor, _ZN5Actor8setArmorE9ArmorSlotRK9ItemStack);
            VTABLE_CALL<void>(Actor_setArmor, (Actor*) ptr, slot, &stack);
        }
    }
    __EXPORT__(jint, GetArmorMaterialTypeInSlot, jint slot) {
        VTABLE_FIND_OFFSET(Actor_getArmorMaterialTypeInSlot, _ZTV5Actor, _ZNK5Actor26getArmorMaterialTypeInSlotE9ArmorSlot);
        return VTABLE_CALL<int>(Actor_getArmorMaterialTypeInSlot, (Actor*) ptr, (ArmorSlot) slot);
    }
    __EXPORT__(jint, GetArmorMaterialTextureTypeInSlot, jint slot) {
        VTABLE_FIND_OFFSET(Actor_getArmorMaterialTextureTypeInSlot, _ZTV5Actor, _ZNK5Actor33getArmorMaterialTextureTypeInSlotE9ArmorSlot);
        return VTABLE_CALL<int>(Actor_getArmorMaterialTextureTypeInSlot, (Actor*) ptr, (ArmorSlot) slot);
    }
    __EXPORT__(jlong, GetEquippedSlot, jint slot) {
        VTABLE_FIND_OFFSET(Actor_getEquippedSlot, _ZTV5Actor, _ZNK5Actor15getEquippedSlotE13EquipmentSlot);
        ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getEquippedSlot, (Actor*) ptr, (EquipmentSlot) slot);
        if(stack == nullptr) return 0;
        return (jlong) stack;
    }
    __EXPORT__(void, SetEquippedSlot, jint slot, jint id, jint count, jint data, jlong extra) {
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item != nullptr && count > 0) {
            ItemStack stack(*item, count, data);
            if(extra != 0) {
                ((ItemInstanceExtra*) extra)->apply(&stack);
            }
            VTABLE_FIND_OFFSET(Actor_setEquippedSlot, _ZTV5Actor, _ZN5Actor15setEquippedSlotE13EquipmentSlotRK9ItemStack);
            VTABLE_CALL<void>(Actor_setEquippedSlot, (Actor*) ptr, slot, &stack);
        }
    }
    __EXPORT__(jlong, GetCarriedItem) {
        VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
        ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, (Actor*) ptr);
        if(stack == nullptr) return 0;
        return (jlong) stack;
    }
    __EXPORT__(void, SetCarriedItem, jint id, jint count, jint data, jlong extra) {
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item != nullptr && count > 0) {
            ItemStack stack(*item, count, data);
            if(extra != 0) {
                ((ItemInstanceExtra*) extra)->apply(&stack);
            }
            VTABLE_FIND_OFFSET(Actor_setCarriedItem, _ZTV5Actor, _ZN5Actor14setCarriedItemERK9ItemStack);
            VTABLE_CALL<void>(Actor_setCarriedItem, (Actor*) ptr, &stack);
        }
    }
    __EXPORT__(void, SetOffhandSlot, jint id, jint count, jint data, jlong extra) {
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item != nullptr && count > 0) {
            ItemStack stack(*item, count, data);
            if(extra != 0) {
                ((ItemInstanceExtra*) extra)->apply(&stack);
            }
            VTABLE_FIND_OFFSET(Actor_setOffhandSlot, _ZTV5Actor, _ZN5Actor14setOffhandSlotERK9ItemStack);
            VTABLE_CALL<void>(Actor_setOffhandSlot, (Actor*) ptr, &stack);
        }
    }
    __EXPORT__(void, ConsumeTotem) {
        VTABLE_FIND_OFFSET(Actor_consumeTotem, _ZTV5Actor, _ZN5Actor12consumeTotemEv);
        VTABLE_CALL<void>(Actor_consumeTotem, (Actor*) ptr);
    }
    __EXPORT__(jint, GetEntityTypeId) {
        VTABLE_FIND_OFFSET(Actor_getEntityTypeId, _ZTV5Actor, _ZNK5Actor15getEntityTypeIdEv);
        return (int) VTABLE_CALL<int>(Actor_getEntityTypeId, (Actor*) ptr);
    }
    __EXPORT__(jint, GetPortalCooldown) {
        VTABLE_FIND_OFFSET(Actor_getPortalCooldown, _ZTV5Actor, _ZNK5Actor17getPortalCooldownEv);
        return VTABLE_CALL<int>(Actor_getPortalCooldown, (Actor*) ptr);
    }
    __EXPORT__(jint, GetPortalWaitTime) {
        VTABLE_FIND_OFFSET(Actor_getPortalWaitTime, _ZTV5Actor, _ZNK5Actor17getPortalWaitTimeEv);
        return VTABLE_CALL<int>(Actor_getPortalWaitTime, (Actor*) ptr);
    }
    __EXPORT__(jboolean, CanBePulledIntoVehicle) {
        VTABLE_FIND_OFFSET(Actor_canBePulledIntoVehicle, _ZTV5Actor, _ZNK5Actor22canBePulledIntoVehicleEv);
        return VTABLE_CALL<bool>(Actor_canBePulledIntoVehicle, (Actor*) ptr);
    }
    __EXPORT__(jboolean, InCaravan) {
        VTABLE_FIND_OFFSET(Actor_inCaravan, _ZTV5Actor, _ZNK5Actor9inCaravanEv);
        return VTABLE_CALL<bool>(Actor_inCaravan, (Actor*) ptr);
    }
    __EXPORT__(void, Heal, jint amount) {
        VTABLE_FIND_OFFSET(Actor_heal, _ZTV5Actor, _ZN5Actor4healEi);
        VTABLE_CALL<void>(Actor_heal, (Actor*) ptr, amount);
    }
    __EXPORT__(jboolean, IsInvertedHealAndHarm) {
        VTABLE_FIND_OFFSET(Actor_isInvertedHealAndHarm, _ZTV5Actor, _ZNK5Actor21isInvertedHealAndHarmEv);
        return VTABLE_CALL<bool>(Actor_isInvertedHealAndHarm, (Actor*) ptr);
    }
    __EXPORT__(jboolean, CanBeAffected__JI, jint effectId) {
        VTABLE_FIND_OFFSET(Actor_canBeAffectedI, _ZTV5Actor, _ZNK5Actor13canBeAffectedEi);
        return VTABLE_CALL<bool>(Actor_canBeAffectedI, (Actor*) ptr, effectId);
    }
    __EXPORT__(jboolean, CanBeAffected__JJ, jlong mei) {
        VTABLE_FIND_OFFSET(Actor_canBeAffectedMEI, _ZTV5Actor, _ZNK5Actor13canBeAffectedERK17MobEffectInstance);
        return VTABLE_CALL<bool>(Actor_canBeAffectedMEI, (Actor*) ptr, (MobEffectInstance*) mei);
    }
    __EXPORT__(jboolean, CanBeAffectedByArrow, jlong mei) {
        VTABLE_FIND_OFFSET(Actor_canBeAffectedByArrow, _ZTV5Actor, _ZNK5Actor20canBeAffectedByArrowERK17MobEffectInstance);
        return VTABLE_CALL<bool>(Actor_canBeAffectedByArrow, (Actor*) ptr, (MobEffectInstance*) mei);
    }
    __EXPORT__(void, Swing) {
        VTABLE_FIND_OFFSET(Actor_swing, _ZTV5Actor, _ZN5Actor5swingEv);
        VTABLE_CALL<void>(Actor_swing, (Actor*) ptr);
    }
    __EXPORT__(jboolean, HasOutputSignal, jshort sig) {
        VTABLE_FIND_OFFSET(Actor_hasOutputSignal, _ZTV5Actor, _ZNK5ActorhasOutputSignalEh);
        return VTABLE_CALL<bool>(Actor_hasOutputSignal, (Actor*) ptr, (unsigned char) sig);
    }
    __EXPORT__(jshort, GetOutputSignal) {
        VTABLE_FIND_OFFSET(Actor_getOutputSignal, _ZTV5Actor, _ZNK5Actor15getOutputSignalEv);
        return (jshort) VTABLE_CALL<unsigned char>(Actor_getOutputSignal, (Actor*) ptr);
    }
    __EXPORT__(jfloat, GetRiderYRotation, jlong rider) {
        VTABLE_FIND_OFFSET(Actor_getRiderYRotation, _ZTV5Actor, _ZNK5Actor17getRiderYRotationERK5Actor);
        return VTABLE_CALL<float>(Actor_getRiderYRotation, (Actor*) ptr, (Actor*) rider);
    }
    __EXPORT__(jboolean, IsWorldBuilder) {
        VTABLE_FIND_OFFSET(Actor_isWorldBuilder, _ZTV5Actor, _ZNK5Actor14isWorldBuilderEv);
        return VTABLE_CALL<bool>(Actor_isWorldBuilder, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsCreative) {
        VTABLE_FIND_OFFSET(Actor_isCreative, _ZTV5Actor, _ZNK5Actor10isCreativeEv);
        return VTABLE_CALL<bool>(Actor_isCreative, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsAdventure) {
        VTABLE_FIND_OFFSET(Actor_isAdventure, _ZTV5Actor, _ZNK5Actor11isAdventureEv);
        return VTABLE_CALL<bool>(Actor_isAdventure, (Actor*) ptr);
    }
    __EXPORT__(void, Add, jint id, jint count, jint data, jlong extra) {
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item != nullptr && count > 0) {
            ItemStack stack(*item, count, data);
            if(extra != 0) {
                ((ItemInstanceExtra*) extra)->apply(&stack);
            }
            VTABLE_FIND_OFFSET(Actor_add, _ZTV5Actor, _ZN5Actor3addER9ItemStack);
            VTABLE_CALL<void>(Actor_add, (Actor*) ptr, &stack);
        }
    }
    __EXPORT__(void, Drop, jint id, jint count, jint data, jlong extra, jboolean someBool) {
        Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
        if(item != nullptr && count > 0) {
            ItemStack stack(*item, count, data);
            if(extra != 0) {
                ((ItemInstanceExtra*) extra)->apply(&stack);
            }
            VTABLE_FIND_OFFSET(Actor_drop, _ZTV5Actor, _ZN5Actor4dropERK9ItemStackb);
            VTABLE_CALL<void>(Actor_drop, (Actor*) ptr, &stack, someBool);
        }
    }
    __EXPORT__(void, SetAuxValue, jint value) {
        VTABLE_FIND_OFFSET(Actor_setAuxValue, _ZTV5Actor, _ZN5Actor11setAuxValueEi);
        VTABLE_CALL<void>(Actor_setAuxValue, (Actor*) ptr, value);
    }
    __EXPORT__(void, Wobble) {
        VTABLE_FIND_OFFSET(Actor_wobble, _ZTV5Actor, _ZN5Actor6wobbleEv);
        VTABLE_CALL<void>(Actor_wobble, (Actor*) ptr);
    }
    __EXPORT__(jboolean, HasHurt) {
        VTABLE_FIND_OFFSET(Actor_wasHurt, _ZTV5Actor, _ZN5Actor7wasHurtEv);
        return VTABLE_CALL<bool>(Actor_wasHurt, (Actor*) ptr);
    }
    __EXPORT__(void, StartSpinAttack) {
        VTABLE_FIND_OFFSET(Actor_startSpinAttack, _ZTV5Actor, _ZN5Actor15startSpinAttackEv);
        VTABLE_CALL<void>(Actor_startSpinAttack, (Actor*) ptr);
    }
    __EXPORT__(void, StopSpinAttack) {
        VTABLE_FIND_OFFSET(Actor_stopSpinAttack, _ZTV5Actor, _ZN5Actor14stopSpinAttackEv);
        VTABLE_CALL<void>(Actor_stopSpinAttack, (Actor*) ptr);
    }
    __EXPORT__(void, Kill) {
        VTABLE_FIND_OFFSET(Actor_kill, _ZTV5Actor, _ZN5Actor4killEv);
        VTABLE_CALL<void>(Actor_kill, (Actor*) ptr);
    }
    __EXPORT__(jboolean, ShouldTryMakeStepSound) {
        VTABLE_FIND_OFFSET(Actor_shouldTryMakeStepSound, _ZTV5Actor, _ZN5Actor22shouldTryMakeStepSoundEv);
        return VTABLE_CALL<bool>(Actor_shouldTryMakeStepSound, (Actor*) ptr);
    }
    __EXPORT__(jboolean, CanMakeStepSound) {
        VTABLE_FIND_OFFSET(Actor_canMakeStepSound, _ZTV5Actor, _ZNK5Actor16canMakeStepSoundEv);
        return VTABLE_CALL<bool>(Actor_canMakeStepSound, (Actor*) ptr);
    }
    __EXPORT__(jboolean, OutOfWorld) {
        VTABLE_FIND_OFFSET(Actor_outOfWorld, _ZTV5Actor, _ZN5Actor10outOfWorldEv);
        return VTABLE_CALL<bool>(Actor_outOfWorld, (Actor*) ptr);
    }
    __EXPORT__(void, PushOutOfBlocks, jfloat x, jfloat y, jfloat z) {
        VTABLE_FIND_OFFSET(Actor_pushOutOfBlocks, _ZTV5Actor, _ZN5Actor15pushOutOfBlocksERK4Vec3);
        VTABLE_CALL<void>(Actor_pushOutOfBlocks, (Actor*) ptr, Vec3(x, y, z));
    }
    __EXPORT__(void, DoWaterSplashEffect) {
        VTABLE_FIND_OFFSET(Actor_doWaterSplashEffect, _ZTV5Actor, _ZN5Actor19doWaterSplashEffectEv);
        VTABLE_CALL<void>(Actor_doWaterSplashEffect, (Actor*) ptr);
    }
    __EXPORT__(void, SpawnTrailBubbles) {
        VTABLE_FIND_OFFSET(Actor_spawnTrailBubbles, _ZTV5Actor, _ZN5Actor17spawnTrailBubblesEv);
        VTABLE_CALL<void>(Actor_spawnTrailBubbles, (Actor*) ptr);
    }
    __EXPORT__(jboolean, IsOnGround) {
        return ((Actor*) ptr)->onGround;
    }
    __EXPORT__(jint, CalculateAttackDamage, jint id, jint count, jint data, jlong extra, jlong victimUID, jboolean useCarriedIfNotSpecified) {
        auto actor = (Actor*) ptr;
        VTABLE_FIND_OFFSET(Actor_getAttribute, _ZTV5Actor, _ZNK5Actor12getAttributeERK9Attribute);
        auto attackDamage = VTABLE_CALL<AttributeInstance*>(Actor_getAttribute, actor, &SharedAttributes::ATTACK_DAMAGE);
        int result = (int) attackDamage->getCurrentValue();
        ItemStack* stack = nullptr;
        bool toDelete = false;
        if(id == 0 || count <= 0) {
            if(useCarriedIfNotSpecified) {
                VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
                stack = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, actor);
            }
        } else {
            auto item = ItemRegistry::getItemById(IdConversion::staticToDynamic(id, IdConversion::ITEM));
            if(item != nullptr) {
                stack = new ItemStack(*item, count, data);
                if(extra != 0) {
                    ((ItemInstanceExtra*) extra)->apply(stack);
                }
                toDelete = true;
            }
        }
        if(stack != nullptr) result += stack->getAttackDamage();
        VTABLE_FIND_OFFSET(Actor_adjustDamageAmount, _ZTV5Actor, _ZNK5Actor18adjustDamageAmountERi);
        VTABLE_CALL<void>(Actor_adjustDamageAmount, actor, &result);
        auto damageBoost = MobEffect::getById(5);
        auto weakness = MobEffect::getById(18);
        if(damageBoost != nullptr && actor->hasEffect(*damageBoost)) {
            int amplifier = actor->getEffect(*damageBoost)->getAmplifier() + 1;
            for(int i = 0; i < amplifier; i++) result = (int) (((float) result * 1.3f) + 1.0f);
        }
        if(weakness != nullptr && actor->hasEffect(*weakness)) {
            int amplifier = actor->getEffect(*weakness)->getAmplifier() + 1;
            for(int i = 0; i < amplifier; i++) result = (int) (((float) result * 0.8f) - 0.5f);
        }
        auto victim = Actor::wrap(victimUID);
        if(victim != nullptr) {
            bool someCheck = *((bool*) victim + 292); // idk what's this
            if(!someCheck && stack != nullptr && stack && stack->isEnchanted()) {
                auto enchants = stack->constructItemEnchantsFromUserData();
                auto enchantsVector = enchants.getAllEnchants();
                VTABLE_FIND_OFFSET(Enchant_getDamageBonus, _ZTV7Enchant, _ZNK7Enchant14getDamageBonusEiRK5Actor);
                for(const auto& instance : enchantsVector) {
                    result += (int) VTABLE_CALL<float>(Enchant_getDamageBonus, Enchant::mEnchants.at((unsigned char) instance.type).get(), instance.level, victim);
                }
            }
        }
        if(stack != nullptr && toDelete) delete stack;
        return result;
    }

    #define GET_BREATHABLE BreathableComponent* b = ((Actor*) ptr)->tryGetComponent<BreathableComponent>();
    #define RET_DEFAULT(RET) if(b == nullptr) return RET;

    __EXPORT__(jboolean, CanBreatheAir) {
        GET_BREATHABLE RET_DEFAULT(false) return b->canBreatheAir();
    }
    __EXPORT__(jboolean, CanBreatheWater) {
        GET_BREATHABLE RET_DEFAULT(false) return b->canBreatheWater();
    }
    __EXPORT__(jboolean, CanBreatheLava) {
        GET_BREATHABLE RET_DEFAULT(false) return b->canBreatheLava();
    }
    __EXPORT__(jboolean, CanBreatheSolids) {
        GET_BREATHABLE RET_DEFAULT(false) return b->canBreathSolids();
    }
    __EXPORT__(jboolean, GeneratesBubbles) {
        GET_BREATHABLE RET_DEFAULT(false) return b->generatesBubbles();
    }
    __EXPORT__(jint, GetInhaleTime) {
        GET_BREATHABLE RET_DEFAULT(0) return b->getInhaleTime();
    }
    __EXPORT__(jint, GetSuffocateTime) {
        GET_BREATHABLE RET_DEFAULT(0) return b->getSuffocateTime();
    }
    __EXPORT__(void, SetAirSupply, jshort supply) {
        GET_BREATHABLE if(b != nullptr) b->setAirSupply(supply);
    }
    __EXPORT__(jshort, GetMaxAirSupply) {
        GET_BREATHABLE RET_DEFAULT(0) return b->getMaxAirSupply();
    }
    __EXPORT__(void, SetMaxAirSupply, jshort supply) {
        GET_BREATHABLE if(b != nullptr) b->setMaxAirSupply(supply);
    }
    __EXPORT__(jshort, GetAirRegenPerTick) {
        GET_BREATHABLE RET_DEFAULT(0) return b->getAirRegenPerTick();
    }

    #undef GET_BREATHABLE
    #undef RET_DEFAULT

    __EXPORT__(jboolean, IsMob) {
        Actor* actor = (Actor*) ptr;
        VTABLE_FIND_OFFSET(Actor_getEntityTypeId, _ZTV5Actor, _ZNK5Actor15getEntityTypeIdEv);
        ActorType type = VTABLE_CALL<ActorType>(Actor_getEntityTypeId, (Actor*) ptr);
        return ActorClassTree::isMob(type);
    }
}


#undef __EXPORT__