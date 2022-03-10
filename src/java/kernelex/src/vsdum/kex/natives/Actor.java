package vsdum.kex.natives;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.innercore.api.NativeItemInstance;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;

public class Actor implements INativeInterface {

    protected static native long wrap(long entityUid);
    protected static native boolean nativeIsBreakingObstruction(long ptr);
    protected static native void nativeSetBreakingObstruction(long ptr, boolean breaking);
    protected static native boolean nativeIsDancing(long ptr);
    protected static native void nativeSetDancing(long ptr, boolean dancing);
    protected static native void nativeHealEffects(long ptr, int value);
    protected static native int nativeGetColor(long ptr);
    protected static native void nativeSetColor(long ptr, int color);
    protected static native int nativeGetColor2(long ptr);
    protected static native void nativeSetColor2(long ptr, int color);
    protected static native boolean nativeIsInClouds(long ptr);
    protected static native boolean nativeHasUniqueID(long ptr);
    protected static native long nativeGetUniqueID(long ptr);
    protected static native int nativeGetHurtDir(long ptr);
    protected static native void nativeSetHurtDir(long ptr, int dir);
    protected static native boolean nativeIsEnchanted(long ptr);
    protected static native boolean nativeSetEnchanted(long ptr, boolean enchanted);
    protected static native int nativeGetMarkVariant(long ptr);
    protected static native void nativeSetMarkVariant(long ptr, int variant);
    protected static native boolean nativeHasDimension(long ptr);
    protected static native boolean nativeCanChangeDimensions(long ptr);
    protected static native int nativeGetDimensionId(long ptr);
    protected static native long nativeGetDimension(long ptr);
    protected static native boolean nativeWasLastHitByPlayer(long ptr);
    protected static native boolean nativeIsDelayedAttacking(long ptr);
    protected static native void nativeSetDelayedAttacking(long ptr, boolean delayed);
    protected static native boolean nativeCanBeginOrContinueClimbingLadder(long ptr);
    protected static native int nativeGetStructuralIntegrity(long ptr);
    protected static native void nativeSetStructuralIntegrity(long ptr, int integrity);
    protected static native boolean nativeHasLevel(long ptr);
    protected static native long nativeGetLevel(long ptr);
    protected static native float nativeGetCameraDistance(long ptr);
    protected static native void nativeSetCameraDistance(long ptr, float distance);
    protected static native boolean nativeIsDoorOpener(long ptr);
    protected static native void nativeSetDoorOpener(long ptr, boolean opener);
    protected static native boolean nativeHasType(long ptr, int type);
    protected static native boolean nativeIsType(long ptr, int type);
    protected static native void nativeRemoveEffectNoUpdate(long ptr, int effectId);
    protected static native long nativeGetEffect(long ptr, long effectPtr);
    protected static native long nativeGetEffect(long ptr, int effectId);
    protected static native int nativeGetActiveEffectCount(long ptr);
    protected static native boolean nativeHasEffect(long ptr, long effectPtr);
    protected static native boolean nativeHasEffect(long ptr, int effectId);
    protected static native boolean nativeHasAnyVisibleEffects(long ptr);
    protected static native void nativeRemoveEffect(long ptr, int id);
    protected static native boolean nativeHasAnyEffects(long ptr);
    protected static native void nativeRemoveAllEffects(long ptr);
    protected static native void nativeAddEffect(long ptr, long instancePtr);
    protected static native boolean nativeIsInSnow(long ptr);
    protected static native boolean nativeCanMate(long ptr, long matePtr);
    protected static native boolean nativeHasTickingArea(long ptr);
    protected static native long nativeGetTickingArea(long ptr);
    protected static native boolean nativeGetIsOnScreen(long ptr);
    protected static native void nativeSetIsOnScreen(long ptr, boolean onScreen);
    protected static native boolean nativeIsOverScaffolding(long ptr);
    protected static native boolean nativeIsInScaffolding(long ptr);
    protected static native boolean nativeShouldOrphan(long ptr, long bsptr);
    protected static native boolean nativeIsOrphan(long ptr);
    protected static native boolean nativeIsPredictedMovementEnabled(long ptr);
    protected static native boolean nativeIsInRain(long ptr);
    protected static native boolean nativeIsWASDControlled(long ptr);
    protected static native void nativeSetWASDControlled(long ptr, boolean wasd);
    protected static native boolean nativeHasPriorityAmmunition(long ptr);
    protected static native boolean nativeHasRuntimeID(long ptr);
    protected static native int nativeGetVariant(long ptr);
    protected static native void nativeSetVariant(long ptr, int variant);
    protected static native boolean nativeIsRiding(long ptr, long ridden);
    protected static native boolean nativeIsRider(long ptr, long rider);
    protected static native void nativeRemoveAllRiders(long ptr, boolean b1, boolean b2);
    protected static native boolean nativeHasPlayerRider(long ptr);
    protected static native boolean nativeIsRiding(long ptr);
    protected static native long nativeGetRide(long ptr);
    protected static native boolean nativeHasRider(long ptr);
    protected static native boolean nativeGetStatusFlag(long ptr, int flag);
    protected static native boolean nativeIsChested(long ptr);
    protected static native boolean nativeIsStackable(long ptr);
    protected static native boolean nativeIsResting(long ptr);
    protected static native void nativeSetIsResting(long ptr, boolean resting);
    protected static native float nativeGetHealth(long ptr);
    protected static native float nativeGetMaxHealth(long ptr);
    protected static native int nativeGetControllingSeat(long ptr);
    protected static native void nativeSetControllingSeat(long ptr, int seat);
    protected static native boolean nativeIsInsidePortal(long ptr);
    protected static native boolean nativeHasTeleported(long ptr);
    protected static native void nativeMoveRelative(long ptr, float strafe, float up, float forward, float friction);
    protected static native long nativeGetRegion(long ptr);
    protected static native boolean nativeIsTame(long ptr);
    protected static native boolean nativeIsLeashed(long ptr);
    protected static native boolean nativeIsLeashableType(long ptr);
    protected static native boolean nativeIsMoving(long ptr);
    protected static native void nativeSetMoving(long ptr, boolean moving);
    protected static native boolean nativeHasTotemEquipped(long ptr);
    protected static native boolean nativeIsAutonomous(long ptr);
    protected static native void nativeSetAutonomous(long ptr, boolean auto);
    protected static native boolean nativeIsPersistent(long ptr);
    protected static native void nativeRemoveEntity(long ptr);
    protected static native void nativeSetCollidableMob(long ptr, boolean collidable);
    protected static native boolean nativeGetCollidableMobNear(long ptr);
    protected static native void nativeSetCollidableMobNear(long ptr, boolean collidable);
    protected static native boolean nativeHasFishingHook(long ptr);
    protected static native boolean nativeGetChainedDamageEffects(long ptr);
    protected static native void nativeSetChainedDamageEffects(long ptr, boolean chained);
    protected static native boolean nativeIsPacified(long ptr);
    protected static native float nativeDistanceTo(long ptr, long actorptr);
    protected static native float nativeDistanceTo(long ptr, float x, float y, float z);
    protected static native boolean nativeCanCurrentlySwim(long ptr);
    protected static native boolean nativeIsSwimming(long ptr);
    protected static native boolean nativeIsSwimmer(long ptr);
    protected static native void nativeSetSwimmer(long ptr, boolean swimmer);
    protected static native boolean nativeHasFamily(long ptr, String family);
    protected static native boolean nativeHasAttributeBuff(long ptr, int buffType);
    protected static native boolean nativeIsClientSide(long ptr);
    protected static native boolean nativeIsControlledByLocalInstance(long ptr);
    protected static native boolean nativeIsClimbing(long ptr);
    protected static native void nativeSetClimbing(long ptr, boolean climbing);
    protected static native boolean nativeCanClimb(long ptr);
    protected static native void nativeSetCanClimb(long ptr, boolean canClimb);
    protected static native int nativeGetSkinID(long ptr);
    protected static native void nativeSetSkinID(long ptr, int id);
    protected static native float nativeGetSpeedInMetersPerSecond(long ptr);
    protected static native int nativeGetStrength(long ptr);
    protected static native void nativeSetStrength(long ptr, int strength);
    protected static native int nativeGetStrengthMax(long ptr);
    protected static native void nativeSetStrengthMax(long ptr, int strength);
    protected static native boolean nativeGetDamageNearbyMobs(long ptr);
    protected static native void nativeSetDamageNearbyMobs(long ptr, boolean damage);
    protected static native boolean nativeIsLayingDown(long ptr);
    protected static native void nativeSetLayingDown(long ptr, boolean laying);
    protected static native boolean nativeGetTempted(long ptr);
    protected static native void nativeSetTempted(long ptr, boolean tempted);
    protected static native void nativeDropTowards(long ptr, long stackptr, float x, float y, float z);
    protected static native boolean nativeIsTrading(long ptr);
    protected static native boolean nativeInDownwardFlowingLiquid(long ptr);
    protected static native int nativeGetJumpDuration(long ptr);
    protected static native void nativeSetJumpDuration(long ptr, int dur);
    protected static native boolean nativeIsScared(long ptr);
    protected static native void nativeSetScared(long ptr, boolean scared);
    protected static native boolean nativeIsSitting(long ptr);
    protected static native void nativeSetSitting(long ptr, boolean sitting);
    protected static native boolean nativeIsBaby(long ptr);
    protected static native boolean nativeIsIgnited(long ptr);
    protected static native int nativeGetLifeSpan(long ptr);
    protected static native void nativeSetLimitedLife(long ptr, int life);
    protected static native boolean nativeIsInvisible(long ptr);
    protected static native void nativeSetInvisible(long ptr, boolean invisible);
    protected static native boolean nativeIsInWorld(long ptr);
    protected static native boolean nativeIsInLove(long ptr);
    protected static native void nativeSetInLove(long ptr, long loverptr);
    protected static native boolean nativeIsDoorBreaker(long ptr);
    protected static native void nativeSetDoorBreaker(long ptr, boolean breaker);
    protected static native boolean nativeIsWalker(long ptr);
    protected static native void nativeSetWalker(long ptr, boolean walker);
    protected static native boolean nativeIsCharged(long ptr);
    protected static native void nativeSetCharged(long ptr, boolean charged);
    protected static native boolean nativeCanFly(long ptr);
    protected static native void nativeSetCanFly(long ptr, boolean canFly);
    protected static native boolean nativeIsInPrecipitation(long ptr);
    protected static native void nativeSetAABB(long ptr, float x1, float y1, float z1, float x2, float y2, float z2);
    protected static native boolean nativeIsSafeToSleepNear(long ptr);
    protected static native void nativeSetBlockTarget(long ptr, int x, int y, int z);
    protected static native boolean nativeIsAngry(long ptr);
    protected static native boolean nativeIsPowered(long ptr);
    protected static native void nativeSetPowered(long ptr, boolean powered);
    protected static native boolean nativeIsSheared(long ptr);
    protected static native boolean nativeIsOutOfControl(long ptr);
    protected static native boolean nativeIsSneaking(long ptr);
    protected static native void nativeSetSneaking(long ptr, boolean sneaking);
    protected static native long nativeGetTarget(long ptr);
    protected static native void nativeSetTarget(long ptr, long targetptr);
    protected static native void nativeSetStunned(long ptr, boolean stunned);
    protected static native short nativeGetTotalAirSupply(long ptr);
    protected static native short nativeGetAirSupply(long ptr);
    protected static native boolean nativeIsInThunderstorm(long ptr);
    protected static native boolean nativeIsBribed(long ptr);
    protected static native boolean nativeIsStanding(long ptr);
    protected static native void nativeSetStanding(long ptr, boolean standing);
    protected static native int nativeGetShakeTime(long ptr);
    protected static native void nativeSetShakeTime(long ptr, int time);
    protected static native boolean nativeHasCategory(long ptr, int category);
    protected static native float nativeGetVerticalSpeedInMetersPerSecond(long ptr);
    protected static native boolean nativeIsTrusting(long ptr);
    protected static native float nativeGetRadius(long ptr);
    protected static native boolean nativeHasComponent(long ptr, String component);
    protected static native int nativeGetOnDeathExperience(long ptr);
    protected static native float nativeGetInterpolatedBodyYaw(long ptr, float partialTicks);
    protected static native float nativeGetYawSpeedInDegreesPerSecond(long ptr);
    protected static native float nativeGetInterpolatedWalkAnimSpeed(long ptr, float partialTicks);
    protected static native boolean nativeIsFireImmune(long ptr);
    protected static native boolean nativeBreaksFallingBlocks(long ptr);
    protected static native void nativeChorusFruitTeleport(long ptr, float x, float y, float z);
    protected static native void nativeLerpTo(long ptr, double x, double y, double z, float rotX, float rotY);
    protected static native void nativeLerpMotion(long ptr, double x, double y, double z);
    protected static native float nativeGetRidingHeight(long ptr);
    protected static native void nativeStartRiding(long ptr, long riddenPtr);
    protected static native void nativeAddRider(long ptr, long riderPtr);
    protected static native boolean nativeIntersects(long ptr, float x1, float y1, float z1, float x2, float y2, float z2);
    protected static native boolean nativeIsFree(long ptr, float x, float y, float z);
    protected static native boolean nativeIsFree(long ptr, float x, float y, float z, float someFloat);
    protected static native boolean nativeIsInWall(long ptr);
    protected static native boolean nativeCanShowNameTag(long ptr);
    protected static native boolean nativeCanExistInPeaceful(long ptr);
    protected static native void nativeSetNameTagVisible(long ptr, boolean visible);
    protected static native boolean nativeGetAlwaysShowNameTag(long ptr);
    protected static native boolean nativeIsInWater(long ptr);
    protected static native boolean nativeHasEnteredWater(long ptr);
    protected static native boolean nativeIsImmersedInWater(long ptr);
    protected static native boolean nativeIsInWaterOrRain(long ptr);
    protected static native boolean nativeIsInLava(long ptr);
    protected static native boolean nativeIsUnderLiquid(long ptr, int materialType);
    protected static native boolean nativeIsOverWater(long ptr);
    protected static native float nativeGetShadowRadius(long ptr);
    protected static native boolean nativeCanSeeInvisible(long ptr);
    protected static native boolean nativeCanSee(long ptr, long actorptr);
    protected static native boolean nativeCanSee(long ptr, float x, float y, float z);
    protected static native boolean nativeIsImmobile(long ptr);
    protected static native boolean nativeIsSilent(long ptr);
    protected static native boolean nativeIsPickable(long ptr);
    protected static native boolean nativeIsFishable(long ptr);
    protected static native boolean nativeIsSleeping(long ptr);
    protected static native boolean nativeIsShootable(long ptr);
    protected static native boolean nativeIsBlocking(long ptr);
    protected static native boolean nativeIsAlive(long ptr);
    protected static native boolean nativeIsOnFire(long ptr);
    protected static native void nativeSetOnFire(long ptr, int fireTicks);
    protected static native boolean nativeIsOnHotBlock(long ptr);
    protected static native boolean nativeIsCreativeModeAllowed(long ptr);
    protected static native boolean nativeIsSurfaceMob(long ptr);
    protected static native boolean nativeIsTargetable(long ptr);
    protected static native boolean nativeIsLocalPlayer(long ptr);
    protected static native boolean nativeIsPlayer(long ptr);
    protected static native boolean nativeCanAttack(long ptr, long victim, boolean someBool);
    protected static native boolean nativeIsValidTarget(long ptr, long potentialTarget);
    protected static native void nativeAttack(long ptr, long victim);
    protected static native void nativePerformRangedAttack(long ptr, long victim, float distanceFactor);
    protected static native int nativeGetEquipmentCount(long ptr);
    protected static native int nativeGetInventorySize(long ptr);
    protected static native int nativeGetEquipSlots(long ptr);
    protected static native int nativeGetChestSlots(long ptr);
    protected static native boolean nativeCanPowerJump(long ptr);
    protected static native void nativeSetCanPowerJump(long ptr, boolean canPowerJump);
    protected static native boolean nativeIsJumping(long ptr);
    protected static native void nativeDoFireHurt(long ptr, int amount);
    protected static native void nativeOnLightningHit(long ptr);
    protected static native void nativeFeed(long ptr, int amount);
    protected static native float nativeGetPickRadius(long ptr);
    protected static native long nativeGetArmor(long ptr, int slot);
    protected static native void nativeSetArmor(long ptr, int slot, long stack);
    protected static native int nativeGetArmorMaterialTypeInSlot(long ptr, int slot);
    protected static native int nativeGetArmorMaterialTextureTypeInSlot(long ptr, int slot);
    protected static native long nativeGetEquippedSlot(long ptr, int slot);
    protected static native void nativeSetEquippedSlot(long ptr, int slot, long stack);
    protected static native long nativeGetCarriedItem(long ptr);
    protected static native void nativeSetCarriedItem(long ptr, long stackptr);
    protected static native void nativeSetOffhandSlot(long ptr, long stackptr);
    protected static native void nativeConsumeTotem(long ptr);
    protected static native int nativeGetEntityTypeId(long ptr);
    protected static native int nativeGetPortalCooldown(long ptr);
    protected static native int nativeGetPortalWaitTime(long ptr);
    protected static native boolean nativeCanBePulledIntoVehicle(long ptr);
    protected static native boolean nativeInCaravan(long ptr);
    protected static native void nativeHeal(long ptr, int amount);
    protected static native boolean nativeIsInvertedHealAndHarm(long ptr);
    protected static native boolean nativeCanBeAffected(long ptr, int effectId);
    protected static native boolean nativeCanBeAffected(long ptr, long mobEffectInstance);
    protected static native boolean nativeCanBeAffectedByArrow(long ptr, long mei);
    protected static native void nativeSwing(long ptr);
    protected static native boolean nativeHasOutputSignal(long ptr, short signal);
    protected static native short nativeGetOutputSignal(long ptr);
    protected static native float nativeGetRiderYRotation(long ptr, long riderptr);
    protected static native boolean nativeIsWorldBuilder(long ptr);
    protected static native boolean nativeIsCreative(long ptr);
    protected static native boolean nativeIsAdventure(long ptr);
    protected static native void nativeAdd(long ptr, long stackptr);
    protected static native void nativeDrop(long ptr, long stackptr, boolean someBool);
    protected static native void nativeSetAuxValue(long ptr, int aux);
    protected static native void nativeWobble(long ptr);
    protected static native boolean nativeHasHurt(long ptr);
    protected static native void nativeStartSpinAttack(long ptr);
    protected static native void nativeStopSpinAttack(long ptr);
    protected static native void nativeKill(long ptr);
    protected static native boolean nativeShouldTryMakeStepSound(long ptr);
    protected static native boolean nativeCanMakeStepSound(long ptr);
    protected static native boolean nativeOutOfWorld(long ptr);
    protected static native void nativePushOutOfBlocks(long ptr, float x, float y, float z);
    protected static native void nativeDoWaterSplashEffect(long ptr);
    protected static native void nativeSpawnTrailBubbles(long ptr);
    protected static native boolean nativeIsMob(long ptr);

    public static boolean isValid(long entityUID)
    {
        return wrap(entityUID) != 0L;
    }
    
    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public Actor(long entity)
    {
        long ptr = wrap(entity);
        if(ptr == 0L) throw new IllegalArgumentException("There is no entity with given id!");
        this.pointer = ptr;
    }

    protected Actor(long pointer, boolean flag)
    {
        this.pointer = pointer;
    }

    public boolean isBreakingObstruction()
    {
        return nativeIsBreakingObstruction(this.pointer);
    }

    public void setBreakingObstruction(boolean breaking)
    {
        nativeSetBreakingObstruction(this.pointer, breaking);
    }

    public boolean isDancing()
    {
        return nativeIsDancing(this.pointer);
    }

    public void setDancing(boolean dancing)
    {
        nativeSetDancing(this.pointer, dancing);
    }

    public void healEffects(int value)
    {
        nativeHealEffects(this.pointer, value);
    }

    public int getColor()
    {
        return nativeGetColor(this.pointer);
    }

    public void setColor(int color)
    {
        nativeSetColor(this.pointer, color);
    }

    public int getColor2()
    {
        return nativeGetColor2(this.pointer);
    }

    public void setColor2(int color)
    {
        nativeSetColor2(this.pointer, color);
    }
    
    public boolean isInClouds()
    {
        return nativeIsInClouds(this.pointer);
    }

    public boolean hasUniqueID()
    {
        return nativeHasUniqueID(this.pointer);
    }

    public long getUniqueID()
    {
        return nativeGetUniqueID(this.pointer);
    }

    public int getHurtDir()
    {
        return nativeGetHurtDir(this.pointer);
    }

    public void setHurtDir(int hurtDir)
    {
        nativeSetHurtDir(this.pointer, hurtDir);
    }

    public boolean isEnchanted()
    {
        return nativeIsEnchanted(this.pointer);
    }

    public void setEnchanted(boolean enchanted)
    {
        nativeSetEnchanted(this.pointer, enchanted);
    }

    public int getMarkVariant()
    {
        return nativeGetMarkVariant(this.pointer);
    }

    public void setMarkVariant(int variant)
    {
        nativeSetMarkVariant(this.pointer, variant);
    }

    public boolean hasDimension()
    {
        return nativeHasDimension(this.pointer);
    }

    public boolean canChangeDimensions()
    {
        return nativeCanChangeDimensions(this.pointer);
    }

    public int getDimensionId()
    {
        return nativeGetDimensionId(this.pointer);
    }

    @Nullable public Dimension getDimension()
    {
        long ptr = nativeGetDimension(this.pointer);
        if(ptr == 0) return null;
        return new Dimension(ptr);
    }

    public boolean wasLastHitByPlayer()
    {
        return nativeWasLastHitByPlayer(this.pointer);
    }

    public boolean isDelayedAttacking()
    {
        return nativeIsDelayedAttacking(this.pointer);
    }

    public void setDelayedAttacking(boolean delayed)
    {
        nativeSetDelayedAttacking(this.pointer, delayed);
    }

    public boolean canBeginOrContinueClimbingLadder()
    {
        return nativeCanBeginOrContinueClimbingLadder(this.pointer);
    }

    public int getStructuralIntegrity()
    {
        return nativeGetStructuralIntegrity(this.pointer);
    }

    public void setStructuralIntegrity(int integrity)
    {
        nativeSetStructuralIntegrity(this.pointer, integrity);
    }

    public boolean hasLevel()
    {
        return nativeHasLevel(this.pointer);
    }

    @Nullable public Level getLevel()
    {
        long ptr = nativeGetLevel(this.pointer);
        if(ptr == 0L) return null;
        return new Level(ptr);
    }

    public float getCameraDistance()
    {
        return nativeGetCameraDistance(this.pointer);
    }

    public void setCameraDistance(float distance)
    {
        nativeSetCameraDistance(this.pointer, distance);
    }

    public boolean isDoorOpener()
    {
        return nativeIsDoorOpener(this.pointer);
    }

    public void setDoorOpener(boolean opener)
    {
        nativeSetDoorOpener(this.pointer, opener);
    }

    public boolean hasType(int type)
    {
        return nativeHasType(this.pointer, type);
    }

    public boolean isType(int type)
    {
        return nativeIsType(this.pointer, type);
    }

    public void removeEffectNoUpdate(int id)
    {
        nativeRemoveEffectNoUpdate(this.pointer, id);
    }

    @Nullable public MobEffectInstance getEffect(MobEffect effect)
    {
        long instancePtr = nativeGetEffect(this.pointer, effect.getPointer());
        if(instancePtr == 0L) return null;
        return new MobEffectInstance(instancePtr, true);
    }

    @Nullable public MobEffectInstance getEffect(int effectId)
    {
        long instancePtr = nativeGetEffect(this.pointer, effectId);
        if(instancePtr == 0L) return null;
        return new MobEffectInstance(instancePtr, true);
    }

    public int getActiveEffectCount()
    {
        return nativeGetActiveEffectCount(this.pointer);
    }

    public boolean hasEffect(MobEffect effect)
    {
        return nativeHasEffect(this.pointer, effect.getPointer());
    }

    public boolean hasEffect(int effectId)
    {
        return nativeHasEffect(this.pointer, effectId);
    }

    public boolean hasAnyVisibleEffects()
    {
        return nativeHasAnyVisibleEffects(this.pointer);
    }

    public void removeEffect(int id)
    {
        nativeRemoveEffect(this.pointer, id);
    }

    public boolean hasAnyEffects()
    {
        return nativeHasAnyEffects(this.pointer);
    }

    public void removeAllEffects()
    {
        nativeRemoveAllEffects(this.pointer);
    }

    public void addEffect(MobEffectInstance effectInstance)
    {
        nativeAddEffect(this.pointer, effectInstance.getPointer());
    }

    public boolean isInSnow()
    {
        return nativeIsInSnow(this.pointer);
    }

    public boolean canMate(Actor mate)
    {
        return nativeCanMate(this.pointer, mate.getPointer());
    }

    public boolean hasTickingArea()
    {
        return nativeHasTickingArea(this.pointer);
    }

    @Nullable public TickingArea getTickingArea()
    {
        long areaPtr = nativeGetTickingArea(this.pointer);
        if(areaPtr == 0L) return null;
        return new TickingArea(areaPtr);
    }

    public boolean getIsOnScreen()
    {
        return nativeGetIsOnScreen(this.pointer);
    }

    public void setIsOnScreen(boolean onScreen)
    {
        nativeSetIsOnScreen(this.pointer, onScreen);
    }

    public boolean isOverScaffolding()
    {
        return nativeIsOverScaffolding(this.pointer);
    }

    public boolean isInScaffolding()
    {
        return nativeIsInScaffolding(this.pointer);
    }

    public boolean shouldOrphan(NativeBlockSource world)
    {
        return nativeShouldOrphan(this.pointer, world.getPointer());
    }

    public boolean isOrphan()
    {
        return nativeIsOrphan(this.pointer);
    }

    public boolean isPredictedMovementEnabled()
    {
        return nativeIsPredictedMovementEnabled(this.pointer);
    }

    public boolean isInRain()
    {
        return nativeIsInRain(this.pointer);
    }

    public boolean isWASDControlled()
    {
        return nativeIsWASDControlled(this.pointer);
    }

    public void setWASDControlled(boolean wasd)
    {
        nativeSetWASDControlled(this.pointer, wasd);
    }

    public boolean hasPriorityAmmunition()
    {
        return nativeHasPriorityAmmunition(this.pointer);
    }

    public boolean hasRuntimeID()
    {
        return nativeHasRuntimeID(this.pointer);
    }

    public int getVariant()
    {
        return nativeGetVariant(this.pointer);
    }

    public void setVariant(int variant)
    {
        nativeSetVariant(this.pointer, variant);
    }

    public boolean isRiding(Actor ridden)
    {
        return nativeIsRiding(this.pointer, ridden.getPointer());
    }

    public boolean isRider(Actor rider)
    {
        return nativeIsRider(this.pointer, rider.getPointer());
    }

    public void removeAllRiders(boolean b1, boolean b2)
    {
        nativeRemoveAllRiders(this.pointer, b1, b2);
    }

    public boolean hasPlayerRider()
    {
        return nativeHasPlayerRider(this.pointer);
    }

    public boolean isRiding()
    {
        return nativeIsRiding(this.pointer);
    }

    @Nullable public Actor getRide()
    {
        long ridePtr = nativeGetRide(this.pointer);
        if(ridePtr == 0L) return null;
        return new Actor(ridePtr);
    }

    public boolean hasRider()
    {
        return nativeHasRider(this.pointer);
    }

    public boolean getStatusFlag(int flag)
    {
        return nativeGetStatusFlag(this.pointer, flag);
    }

    public boolean isChested()
    {
        return nativeIsChested(this.pointer);
    }

    public boolean isStackable()
    {
        return nativeIsStackable(this.pointer);
    }

    public boolean isResting()
    {
        return nativeIsResting(this.pointer);
    }

    public void setResting(boolean resting)
    {
        nativeSetIsResting(this.pointer, resting);
    }

    public float getHealth()
    {
        return nativeGetHealth(this.pointer);
    }

    public float getMaxHealth()
    {
        return nativeGetMaxHealth(this.pointer);
    }

    public int getControllingSeat()
    {
        return nativeGetControllingSeat(this.pointer);
    }

    public void setControllingSeat(int seat)
    {
        nativeSetControllingSeat(this.pointer, seat);
    }

    public boolean isInsidePortal()
    {
        return nativeIsInsidePortal(this.pointer);
    }

    public boolean hasTeleported()
    {
        return nativeHasTeleported(this.pointer);
    }

    public void moveRelative(float strafe, float up, float forward, float friction)
    {
        nativeMoveRelative(this.pointer, strafe, up, forward, friction);
    }

    @Nullable public NativeBlockSource getRegion()
    {
        long bsptr = nativeGetRegion(this.pointer);
        if(bsptr == 0L) return null;
        return new NativeBlockSource(bsptr, false);
    }

    public boolean isTame()
    {
        return nativeIsTame(this.pointer);
    }

    public boolean isLeashed()
    {
        return nativeIsLeashed(this.pointer);
    }

    public boolean isLeashableType()
    {
        return nativeIsLeashableType(this.pointer);
    }

    public boolean isMoving()
    {
        return nativeIsMoving(this.pointer);
    }

    public void setMoving(boolean moving)
    {
        nativeSetMoving(this.pointer, moving);
    }

    public boolean hasTotemEquipped()
    {
        return nativeHasTotemEquipped(this.pointer);
    }

    public boolean isAutonomous()
    {
        return nativeIsAutonomous(this.pointer);
    }

    public void setAutonomous(boolean auto)
    {
        nativeSetAutonomous(this.pointer, auto);
    }

    public boolean isPersistent()
    {
        return nativeIsPersistent(this.pointer);
    }

    public void removeEntity()
    {
        nativeRemoveEntity(this.pointer);
    }

    public void setCollidableMob(boolean collidable)
    {
        nativeSetCollidableMob(this.pointer, collidable);
    }

    public boolean getCollidableMobNear()
    {
        return nativeGetCollidableMobNear(this.pointer);
    }

    public void setCollidableMobNear(boolean collidable)
    {
        nativeSetCollidableMobNear(this.pointer, collidable);
    }

    public boolean hasFishingHook()
    {
        return nativeHasFishingHook(this.pointer);
    }

    public boolean getChainedDamageEffects()
    {
        return nativeGetChainedDamageEffects(this.pointer);
    }

    public void setChainedDamageEffects(boolean chained)
    {
        nativeSetChainedDamageEffects(this.pointer, chained);
    }

    public boolean isPacified()
    {
        return nativeIsPacified(this.pointer);
    }

    public float distanceTo(Actor actor)
    {
        return nativeDistanceTo(this.pointer, actor.getPointer());
    }

    public float distanceTo(float x, float y, float z)
    {
        return nativeDistanceTo(this.pointer, x, y, z);
    }

    public boolean canCurrentlySwim()
    {
        return nativeCanCurrentlySwim(this.pointer);
    }

    public boolean isSwimming()
    {
        return nativeIsSwimming(this.pointer);
    }

    public boolean isSwimmer()
    {
        return nativeIsSwimmer(this.pointer);
    }

    public void setSwimmer(boolean swimmer)
    {
        nativeSetSwimmer(this.pointer, swimmer);
    }

    public boolean hasFamily(String family)
    {
        return nativeHasFamily(this.pointer, family);
    }

    public boolean hasAttributeBuff(int buffType)
    {
        return nativeHasAttributeBuff(this.pointer, buffType);
    }

    public boolean isClientSide()
    {
        return nativeIsClientSide(this.pointer);
    }

    public boolean isControlledByLocalInstance()
    {
        return nativeIsControlledByLocalInstance(this.pointer);
    }

    public boolean isClimbing()
    {
        return nativeIsClimbing(this.pointer);
    }

    public void setClimbing(boolean climbing)
    {
        nativeSetClimbing(this.pointer, climbing);
    }

    public boolean canClimb()
    {
        return nativeCanClimb(this.pointer);
    }

    public void setCanClimb(boolean canClimb)
    {
        nativeSetCanClimb(this.pointer, canClimb);
    }

    public int getSkinID()
    {
        return nativeGetSkinID(this.pointer);
    }

    public void setSkinID(int id)
    {
        nativeSetSkinID(this.pointer, id);
    }

    public float getSpeedInMetersPerSecond()
    {
        return nativeGetSpeedInMetersPerSecond(this.pointer);
    }

    public int getStrength()
    {
        return nativeGetStrength(this.pointer);
    }

    public void setStrength(int strength)
    {
        nativeSetStrength(this.pointer, strength);
    }

    public int getStrengthMax()
    {
        return nativeGetStrengthMax(this.pointer);
    }

    public void setStrengthMax(int strength)
    {
        nativeSetStrengthMax(this.pointer, strength);
    }

    public boolean getDamageNearbyMobs()
    {
        return nativeGetDamageNearbyMobs(this.pointer);
    }

    public void setDamageNearbyMobs(boolean damage)
    {
        nativeSetDamageNearbyMobs(this.pointer, damage);
    }

    public boolean isLayingDown()
    {
        return nativeIsLayingDown(this.pointer);
    }

    public void setLayingDown(boolean laying)
    {
        nativeSetLayingDown(this.pointer, laying);
    }

    public boolean getTempted()
    {
        return nativeGetTempted(this.pointer);
    }

    public void setTempted(boolean tempted)
    {
        nativeSetTempted(this.pointer, tempted);
    }

    public void dropTowards(NativeItemInstance stack, float x, float y, float z)
    {
        nativeDropTowards(this.pointer, stack.getPointer(), x, y, z);
    }

    public boolean isTrading()
    {
        return nativeIsTrading(this.pointer);
    }

    public boolean inDownwardFlowingLiquid()
    {
        return nativeInDownwardFlowingLiquid(this.pointer);
    }

    public int getJumpDuration()
    {
        return nativeGetJumpDuration(this.pointer);
    }

    public void setJumpDuration(int dur)
    {
        nativeSetJumpDuration(this.pointer, dur);
    }

    public boolean isScared()
    {
        return nativeIsScared(this.pointer);
    }

    public void setScared(boolean scared)
    {
        nativeSetScared(this.pointer, scared);
    }

    public boolean isSitting()
    {
        return nativeIsSitting(this.pointer);
    }

    public void setSitting(boolean sitting)
    {
        nativeSetSitting(this.pointer, sitting);
    }

    public boolean isBaby()
    {
        return nativeIsBaby(this.pointer);
    }

    public boolean isIgnited()
    {
        return nativeIsIgnited(this.pointer);
    }

    public int getLifeSpan()
    {
        return nativeGetLifeSpan(this.pointer);
    }

    public void setLimitedLife(int life)
    {
        nativeSetLimitedLife(this.pointer, life);
    }

    public boolean isInvisible()
    {
        return nativeIsInvisible(this.pointer);
    }

    public void setInvisible(boolean invisible)
    {
        nativeSetInvisible(this.pointer, invisible);
    }
    
    public boolean isInWorld()
    {
        return nativeIsInWorld(this.pointer);
    }

    public boolean isInLove()
    {
        return nativeIsInLove(this.pointer);
    }

    public void setInLove(Actor lover)
    {
        nativeSetInLove(this.pointer, lover.getPointer());
    }

    public boolean isDoorBreaker()
    {
        return nativeIsDoorBreaker(this.pointer);
    }

    public void setDoorBreaker(boolean breaker)
    {
        nativeSetDoorBreaker(this.pointer, breaker);
    }

    public boolean isWalker()
    {
        return nativeIsWalker(this.pointer);
    }

    public void setWalker(boolean walker)
    {
        nativeSetWalker(this.pointer, walker);
    }

    public boolean isCharged()
    {
        return nativeIsCharged(this.pointer);
    }

    public void setCharged(boolean charged)
    {
        nativeSetCharged(this.pointer, charged);
    }

    public boolean canFly()
    {
        return nativeCanFly(this.pointer);
    }

    public void setCanFly(boolean canFly)
    {
        nativeSetCanFly(this.pointer, canFly);
    }

    public boolean isInPrecipitation()
    {
        return nativeIsInPrecipitation(this.pointer);
    }

    public void setAABB(float x1, float y1, float z1, float x2, float y2, float z2)
    {
        nativeSetAABB(this.pointer, x1, y1, z1, x2, y2, z2);
    }

    public boolean isSafeToSleepNear()
    {
        return nativeIsSafeToSleepNear(this.pointer);
    }

    public void setBlockTarget(int x, int y, int z)
    {
        nativeSetBlockTarget(this.pointer, x, y, z);
    }

    public boolean isAngry()
    {
        return nativeIsAngry(this.pointer);
    }

    public boolean isPowered()
    {
        return nativeIsPowered(this.pointer);
    }

    public void setPowered(boolean powered)
    {
        nativeSetPowered(this.pointer, powered);
    }

    public boolean isSheared()
    {
        return nativeIsSheared(this.pointer);
    }

    public boolean isOutOfControl()
    {
        return nativeIsOutOfControl(this.pointer);
    }

    public boolean isSneaking()
    {
        return nativeIsSneaking(this.pointer);
    }
    
    public void setSneaking(boolean sneaking)
    {
        nativeSetSneaking(this.pointer, sneaking);
    }

    @Nullable public Actor getTarget()
    {
        long targetptr = nativeGetTarget(this.pointer);
        if(targetptr == 0L) return null;
        return new Actor(targetptr);
    }

    public void setTarget(Actor target)
    {
        nativeSetTarget(this.pointer, target.getPointer());
    }

    public void setStunned(boolean stunned)
    {
        nativeSetStunned(this.pointer, stunned);
    }

    public short getTotalAirSupply()
    {
        return nativeGetTotalAirSupply(this.pointer);
    }

    public short getAirSupply()
    {
        return nativeGetAirSupply(this.pointer);
    }

    public boolean isInThunderstorm()
    {
        return nativeIsInThunderstorm(this.pointer);
    }

    public boolean isBribed()
    {
        return nativeIsBribed(this.pointer);
    }

    public boolean isStanding()
    {
        return nativeIsStanding(this.pointer);
    }

    public void setStanding(boolean standing)
    {
        nativeSetStanding(this.pointer, standing);
    }

    public int getShakeTime()
    {
        return nativeGetShakeTime(this.pointer);
    }

    public void setShakeTime(int time)
    {
        nativeSetShakeTime(this.pointer, time);
    }

    public boolean hasCategory(int category)
    {
        return nativeHasCategory(this.pointer, category);
    }

    public float getVerticalSpeedInMetersPerSecond()
    {
        return nativeGetVerticalSpeedInMetersPerSecond(this.pointer);
    }

    public boolean isTrusting()
    {
        return nativeIsTrusting(this.pointer);
    }

    public float getRadius()
    {
        return nativeGetRadius(this.pointer);
    }

    public boolean hasComponent(String component)
    {
        return nativeHasComponent(this.pointer, component);
    }

    public int getOnDeathExperience()
    {
        return nativeGetOnDeathExperience(this.pointer);
    }

    public float getInterpolatedBodyYaw(float partialTicks)
    {
        return nativeGetInterpolatedBodyYaw(this.pointer, partialTicks);
    }

    public float getYawSpeedInDegreesPerSecond()
    {
        return nativeGetYawSpeedInDegreesPerSecond(this.pointer);
    }

    public float getInterpolatedWalkAnimSpeed(float partialTicks)
    {
        return nativeGetInterpolatedWalkAnimSpeed(this.pointer, partialTicks);
    }

    public boolean isFireImmune()
    {
        return nativeIsFireImmune(this.pointer);
    }

    public boolean breaksFallingBlocks()
    {
        return nativeBreaksFallingBlocks(this.pointer);
    }

    public void chorusFruitTeleport(float x, float y, float z)
    {
        nativeChorusFruitTeleport(this.pointer, x, y, z);
    }

    public void lerpTo(double x, double y, double z, float rotX, float rotY)
    {
        nativeLerpTo(this.pointer, x, y, z, rotX, rotY);
    }

    public void lerpMotion(double x, double y, double z)
    {
        nativeLerpMotion(this.pointer, x, y, z);
    }

    public float getRidingHeight()
    {
        return nativeGetRidingHeight(this.pointer);
    }

    public void startRiding(Actor ridden)
    {
        nativeStartRiding(this.pointer, ridden.getPointer());
    }

    public void addRider(Actor rider)
    {
        nativeAddRider(this.pointer, rider.getPointer());
    }

    public boolean intersects(float x1, float y1, float z1, float x2, float y2, float z2)
    {
        return nativeIntersects(this.pointer, x1, y1, z1, x2, y2, z2);
    }

    public boolean isFree(float x, float y, float z)
    {
        return nativeIsFree(this.pointer, x, y, z);
    }

    public boolean isFree(float x, float y, float z, float someFloat)
    {
        return nativeIsFree(this.pointer, x, y, z, someFloat);
    }

    public boolean isInWall()
    {
        return nativeIsInWall(this.pointer);
    }

    public boolean canShowNameTag()
    {
        return nativeCanShowNameTag(this.pointer);
    }

    public boolean canExistInPeaceful()
    {
        return nativeCanExistInPeaceful(this.pointer);
    }

    public void setNameTagVisible(boolean visible)
    {
        nativeSetNameTagVisible(this.pointer, visible);
    }

    public boolean getAlwaysShowNameTag()
    {
        return nativeGetAlwaysShowNameTag(this.pointer);
    }

    public boolean isInWater()
    {
        return nativeIsInWater(this.pointer);
    }

    public boolean hasEnteredWater()
    {
        return nativeHasEnteredWater(this.pointer);
    }

    public boolean isImmersedInWater()
    {
        return nativeIsImmersedInWater(this.pointer);
    }

    public boolean isInWaterOrRain()
    {
        return nativeIsInWaterOrRain(this.pointer);
    }

    public boolean isInLava()
    {
        return nativeIsInLava(this.pointer);
    }

    public boolean isUnderLiquid(int materialType)
    {
        return nativeIsUnderLiquid(this.pointer, materialType);
    }

    public boolean isOverWater()
    {
        return nativeIsOverWater(this.pointer);
    }

    public float getShadowRadius()
    {
        return nativeGetShadowRadius(this.pointer);
    }

    public boolean canSeeInvisible()
    {
        return nativeCanSeeInvisible(this.pointer);
    }

    public boolean canSee(Actor actor)
    {
        return nativeCanSee(this.pointer, actor.getPointer());
    }

    public boolean canSee(float x, float y, float z)
    {
        return nativeCanSee(this.pointer, x, y, z);
    }

    public boolean isImmobile()
    {
        return nativeIsImmobile(this.pointer);
    }

    public boolean isSilent()
    {
        return nativeIsSilent(this.pointer);
    }

    public boolean isPickable()
    {
        return nativeIsPickable(this.pointer);
    }

    public boolean isFishable()
    {
        return nativeIsFishable(this.pointer);
    }

    public boolean isSleeping()
    {
        return nativeIsSleeping(this.pointer);
    }

    public boolean isShootable()
    {
        return nativeIsShootable(this.pointer);
    }

    public boolean isBlocking()
    {
        return nativeIsBlocking(this.pointer);
    }

    public boolean isAlive()
    {
        return nativeIsAlive(this.pointer);
    }

    public boolean isOnFire()
    {
        return nativeIsOnFire(this.pointer);
    }

    public void setOnFire(int fireTicks)
    {
        nativeSetOnFire(this.pointer, fireTicks);
    }

    public boolean isOnHotBlock()
    {
        return nativeIsOnHotBlock(this.pointer);
    }

    public boolean isCreativeModeAllowed()
    {
        return nativeIsCreativeModeAllowed(this.pointer);
    }

    public boolean isSurfaceMob()
    {
        return nativeIsSurfaceMob(this.pointer);
    }

    public boolean isTargetable()
    {
        return nativeIsTargetable(this.pointer);
    }

    public boolean isLocalPlayer()
    {
        return nativeIsLocalPlayer(this.pointer);
    }

    public boolean isPlayer()
    {
        return nativeIsPlayer(this.pointer);
    }

    public boolean canAttack(Actor victim, boolean someBool)
    {
        return nativeCanAttack(this.pointer, victim.getPointer(), someBool);
    }

    public boolean isValidTarget(Actor potentialTarget)
    {
        return nativeIsValidTarget(this.pointer, potentialTarget.getPointer());
    }

    public void attack(Actor victim)
    {
        nativeAttack(this.pointer, victim.getPointer());
    }

    public void performRangedAttack(Actor victim, float distanceFactor)
    {
        nativePerformRangedAttack(this.pointer, victim.getPointer(), distanceFactor);
    }

    public int getEquipmentCount()
    {
        return nativeGetEquipmentCount(this.pointer);
    }

    public int getInventorySize()
    {
        return nativeGetInventorySize(this.pointer);
    }

    public int getEquipSlots()
    {
        return nativeGetEquipSlots(this.pointer);
    }

    public int getChestSlots()
    {
        return nativeGetChestSlots(this.pointer);
    }

    public boolean canPowerJump()
    {
        return nativeCanPowerJump(this.pointer);
    }
    
    public void setCanPowerJump(boolean canPowerJump)
    {
        nativeSetCanPowerJump(this.pointer, canPowerJump);
    }

    public boolean isJumping()
    {
        return nativeIsJumping(this.pointer);
    }

    public void doFireHurt(int amount)
    {
        nativeDoFireHurt(this.pointer, amount);
    }

    public void onLightningHit()
    {
        nativeOnLightningHit(this.pointer);
    }

    public void feed(int amount)
    {
        nativeFeed(this.pointer, amount);
    }

    public float getPickRadius()
    {
        return nativeGetPickRadius(this.pointer);
    }

    @Nullable public ItemStack getArmor(int slot)
    {
        long stackptr = nativeGetArmor(this.pointer, slot);
        if(stackptr == 0L) return null;
        return ItemStack.fromPtr(stackptr);
    }

    public void setArmor(int slot, NativeItemInstance stack)
    {
        nativeSetArmor(this.pointer, slot, stack.getPointer());
    }

    public int getArmorMaterialTypeInSlot(int slot)
    {
        return nativeGetArmorMaterialTypeInSlot(this.pointer, slot);
    }

    public int getArmorMaterialTextureTypeInSlot(int slot)
    {
        return nativeGetArmorMaterialTextureTypeInSlot(this.pointer, slot);
    }

    @Nullable public ItemStack getEquippedSlot(int slot)
    {
        long stackptr = nativeGetEquippedSlot(this.pointer, slot);
        if(stackptr == 0L) return null;
        return ItemStack.fromPtr(stackptr);
    }

    public void setEquippedSlot(int slot, NativeItemInstance stack)
    {
        nativeSetEquippedSlot(this.pointer, slot, stack.getPointer());
    }

    @Nullable public ItemStack getCarriedItem()
    {
        long stackptr = nativeGetCarriedItem(this.pointer);
        if(stackptr == 0L) return null;
        return ItemStack.fromPtr(stackptr);
    }

    public void setCarriedItem(NativeItemInstance stack)
    {
        nativeSetCarriedItem(this.pointer, stack.getPointer());
    }

    public void setOffhandSlot(NativeItemInstance stack)
    {
        nativeSetOffhandSlot(this.pointer, stack.getPointer());
    }

    public void consumeTotem()
    {
        nativeConsumeTotem(this.pointer);
    }

    public int getEntityTypeId()
    {
        return nativeGetEntityTypeId(this.pointer);
    }

    public int getPortalCooldown()
    {
        return nativeGetPortalCooldown(this.pointer);
    }

    public int getPortalWaitTime()
    {
        return nativeGetPortalWaitTime(this.pointer);
    }

    public boolean canBePulledIntoVehicle()
    {
        return nativeCanBePulledIntoVehicle(this.pointer);
    }

    public boolean inCaravan()
    {
        return nativeInCaravan(this.pointer);
    }

    public void heal(int amount)
    {
        nativeHeal(this.pointer, amount);
    }

    public boolean isInvertedHealAndHarm()
    {
        return nativeIsInvertedHealAndHarm(this.pointer);
    }

    public boolean canBeAffected(int effectId)
    {
        return nativeCanBeAffected(this.pointer, effectId);
    }

    public boolean canBeAffected(MobEffectInstance effect)
    {
        return nativeCanBeAffected(this.pointer, effect.getPointer());
    }

    public boolean canBeAffectedByArrow(MobEffectInstance effect)
    {
        return nativeCanBeAffectedByArrow(this.pointer, effect.getPointer());
    }

    public void swing()
    {
        nativeSwing(this.pointer);
    }

    public boolean hasOutputSignal(short signal)
    {
        return nativeHasOutputSignal(this.pointer, signal);
    }

    public short getOutputSignal()
    {
        return nativeGetOutputSignal(this.pointer);
    }

    public float getRiderYRotation(Actor rider)
    {
        return nativeGetRiderYRotation(this.pointer, rider.getPointer());
    }

    public boolean isWorldBuilder()
    {
        return nativeIsWorldBuilder(this.pointer);
    }

    public boolean isCreative()
    {
        return nativeIsCreative(this.pointer);
    }

    public boolean isAdventure()
    {
        return nativeIsAdventure(this.pointer);
    }

    public void add(NativeItemInstance stack)
    {
        nativeAdd(this.pointer, stack.getPointer());
    }

    public void drop(NativeItemInstance stack, boolean someBool)
    {
        nativeDrop(this.pointer, stack.getPointer(), someBool);
    }

    public void setAuxValue(int aux)
    {
        nativeSetAuxValue(this.pointer, aux);
    }

    public void wobble()
    {
        nativeWobble(this.pointer);
    }

    public boolean hasHurt()
    {
        return nativeHasHurt(this.pointer);
    }
    
    public void startSpinAttack()
    {
        nativeStartSpinAttack(this.pointer);
    }

    public void stopSpinAttack()
    {
        nativeStopSpinAttack(this.pointer);
    }

    public void kill()
    {
        nativeKill(this.pointer);
    }

    public boolean shouldTryMakeStepSound()
    {
        return nativeShouldTryMakeStepSound(this.pointer);
    }

    public boolean canMakeStepSound()
    {
        return nativeCanMakeStepSound(this.pointer);
    }

    public boolean outOfWorld()
    {
        return nativeOutOfWorld(this.pointer);
    }

    public void pushOutOfBlocks(float x, float y, float z)
    {
        nativePushOutOfBlocks(this.pointer, x, y, z);
    }

    public void doWaterSplashEffect()
    {
        nativeDoWaterSplashEffect(this.pointer);
    }

    public void spawnTrailBubbles()
    {
        nativeSpawnTrailBubbles(this.pointer);
    }

    public boolean isMob()
    {
        return nativeIsMob(this.pointer);
    }

    public boolean isElytraFlying()
    {
        return getStatusFlag(32);
    }

    @Nullable public Mob asMob()
    {
        if(!this.isMob()) return null;
        return new Mob(this);
    }

}
