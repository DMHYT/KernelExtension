package vsdum.kex.natives;

import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;

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
    protected static native boolean nativeIsDownwardFlowingLiquid(long ptr);
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

    public Actor(long pointer, boolean flag)
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
        return new MobEffectInstance(instancePtr);
    }

    @Nullable public MobEffectInstance getEffect(int effectId)
    {
        long instancePtr = nativeGetEffect(this.pointer, effectId);
        if(instancePtr == 0L) return null;
        return new MobEffectInstance(instancePtr);
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

    public void dropTowards(ItemStack stack, float x, float y, float z)
    {
        nativeDropTowards(this.pointer, stack.getPointer(), x, y, z);
    }

    public boolean isTrading()
    {
        return nativeIsTrading(this.pointer);
    }

    public boolean isDownwardFlowingLiquid()
    {
        return nativeIsDownwardFlowingLiquid(this.pointer);
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

}
