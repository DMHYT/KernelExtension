package vsdum.kex.natives;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.NativeItemInstanceExtra;

import android.support.annotation.Nullable;

public class Mob extends Actor {

    protected static native void nativeSetSleeping(long ptr, boolean sleeping);
    protected static native boolean nativeIsSprinting(long ptr);
    protected static native void nativeSetSprinting(long ptr, boolean sprinting);
    protected static native float nativeGetSpeed(long ptr);
    protected static native void nativeSetSpeed(long ptr, float speed);
    protected static native float nativeGetJumpPower(long ptr);
    protected static native int nativeGetMeleeWeaponDamageBonus(long ptr, long mobptr);
    protected static native float nativeGetMeleeKnockbackBonus(long ptr);
    protected static native void nativeTravel(long ptr, float strafe, float vertical, float forward);
    protected static native void nativeApplyFinalFriction(long ptr, float friction, boolean discardFriction);
    protected static native boolean nativeIsLookingAtAnEntity(long ptr);
    protected static native int nativeGetItemUseDuration(long ptr);
    protected static native float nativeGetItemUseStartupProgress(long ptr);
    protected static native float nativeGetItemUseIntervalProgress(long ptr);
    protected static native float nativeGetMaxHeadXRot(long ptr);
    protected static native long nativeGetLastHurtByMob(long ptr);
    protected static native void nativeSetLastHurtByMob(long ptr, long mobptr);
    protected static native long nativeGetLastHurtByPlayer(long ptr);
    protected static native void nativeSetLastHurtByPlayer(long ptr, long playerptr);
    protected static native long nativeGetLastHurtMob(long ptr);
    protected static native void nativeSetLastHurtMob(long ptr, long actorptr);
    protected static native boolean nativeIsAlliedTo(long ptr, long mobptr);
    protected static native boolean nativeCanBeControlledByRider(long ptr);
    protected static native void nativeLeaveCaravan(long ptr);
    protected static native void nativeJoinCaravan(long ptr, long caravanHeadPtr);
    protected static native boolean nativeHasCaravanTail(long ptr);
    protected static native long nativeGetCaravanHead(long ptr);
    protected static native int nativeGetArmorValue(long ptr);
    protected static native float nativeGetArmorCoverPercentage(long ptr);
    protected static native long nativeGetItemSlot(long ptr, int slot);
    protected static native void nativeSetItemSlot(long ptr, int slot, int id, int count, int data, long extra);
    protected static native boolean nativeIsTransitioningSitting(long ptr);
    protected static native void nativeSetTransitioningSitting(long ptr, boolean ts);
    protected static native boolean nativeCanExistWhenDisallowMob(long ptr);
    protected static native void nativeJumpFromGround(long ptr);
    protected static native int nativeGetNoActionTime(long ptr);
    protected static native void nativeResetNoActionTime(long ptr);
    protected static native boolean nativeWantsToBeJockey(long ptr);
    protected static native void nativeSetWantsToBeJockey(long ptr, boolean wants);
    protected static native boolean nativeIsLayingEgg(long ptr);
    protected static native void nativeSetIsLayingEgg(long ptr, boolean laying);
    protected static native int nativeGetGlidingTicks(long ptr);
    protected static native float nativeGetFrictionModifier(long ptr);
    protected static native void nativeSetFrictionModifier(long ptr, float mod);
    protected static native void nativeSnapToYBodyRot(long ptr, float rot);
    protected static native void nativeSnapToYHeadRot(long ptr, float rot);
    protected static native void nativeIncrementArrowCount(long ptr, int incr);
    protected static native boolean nativeCanPickUpLoot(long ptr, int id, int count, int data, long extra);
    protected static native float nativeGetJumpMultiplier(long ptr);
    protected static native boolean nativeHasBeenHurtByMobInLastTicks(long ptr, int ticks);
    protected static native boolean nativeIsHeadInWater(long ptr);
    protected static native float nativeGetMovementComponentCurrentSpeed(long ptr);
    protected static native void nativeSetMovementComponentCurrentSpeed(long ptr, float speed);
    protected static native float nativeGetFlightSpeed(long ptr);
    protected static native void nativeSetFlightSpeed(long ptr, float speed);
    protected static native boolean nativeIsInterpolationActive(long ptr);
    protected static native void nativeSetInterpolationActive(long ptr, boolean interpolationActive);
    protected static native void nativeSetYHeadRot(long ptr, float rot);
    protected static native float nativeGetRiderRotLimit(long ptr);
    protected static native void nativeSetRiderRotLimit(long ptr, float lim);
    protected static native int nativeGetRollCounter(long ptr);
    protected static native boolean nativeIsRolling(long ptr);
    protected static native void nativeSetRolling(long ptr, boolean rolling);
    protected static native int nativeGetSpawnMethod(long ptr);
    protected static native void nativeSetSpawnMethod(long ptr, int method);
    protected static native float nativeGetXxa(long ptr);
    protected static native void nativeSetXxa(long ptr, float xxa);
    protected static native float nativeGetYya(long ptr);
    protected static native void nativeSetYya(long ptr, float yya);
    protected static native float nativeGetZza(long ptr);
    protected static native void nativeSetZza(long ptr, float zza);
    protected static native int nativeGetTravelType(long ptr);
    protected static native void nativeSetSurfaceMob(long ptr, boolean surface);
    protected static native boolean nativeIsPregnant(long ptr);
    protected static native void nativeSetIsPregnant(long ptr, boolean pregnant);
    protected static native boolean nativeIsNaturallySpawned(long ptr);
    protected static native void nativeSetNaturallySpawned(long ptr, boolean naturally);
    protected static native float nativeGetRiderLockedBodyRot(long ptr);
    protected static native void nativeSetRiderLockedBodyRot(long ptr, float rot);
    protected static native boolean nativeIsFrostWalking(long ptr);
    protected static native void nativeSetJumpVelRedux(long ptr, boolean redux);
    protected static native float nativeCalcMoveRelativeSpeed(long ptr, int travelType);
    protected static native boolean nativeIsEating(long ptr);
    protected static native void nativeSetEating(long ptr, boolean eating);
    protected static native int nativeGetEatCounter(long ptr);
    protected static native void nativeSetEatCounter(long ptr, int counter);
    protected static native boolean nativeHasBoundOrigin(long ptr);
    protected static native int nativeGetCaravanSize(long ptr);
    protected static native boolean nativeShouldApplyWaterGravity(long ptr);
    protected static native boolean nativeIsGliding(long ptr);
    protected static native long nativeGetFirstCaravanHead(long ptr);
    protected static native float nativeGetYRotA(long ptr);
    protected static native void nativeSetYRotA(long ptr, float yrota);
    protected static native void nativeSetJumping(long ptr, boolean jumping);
    protected static native void nativeSetSpeedModifier(long ptr, float speedMod);
    protected static native int nativeGetCurrentSwingDuration(long ptr);
    protected static native boolean nativeIsSwinging(long ptr);
    protected static native int nativeCalculateJumpImpulse(long ptr);
    protected static native boolean nativeIsSlime(long ptr);
    
    public Mob(long entity)
    {
        super(entity);
        if(!this.isMob())
            throw new IllegalArgumentException("The given entity is not a Mob! Consider using Actor.asMob() in order not to get exceptions thrown!");
    }

    protected Mob(long ptr, boolean flag)
    {
        super(ptr, flag);
    }

    public Mob(Actor actor)
    {
        this(actor.pointer, true);
        if(!this.isMob())
            throw new IllegalArgumentException("The given Actor is not a Mob! Consider using Actor.asMob() in order not to get exceptions thrown!");
    }

    public void setSleeping(boolean sleeping)
    {
        nativeSetSleeping(this.pointer, sleeping);
    }

    public boolean isSprinting()
    {
        return nativeIsSprinting(this.pointer);
    }
    
    public void setSprinting(boolean sprinting)
    {
        nativeSetSprinting(this.pointer, sprinting);
    }

    public float getSpeed()
    {
        return nativeGetSpeed(this.pointer);
    }

    public void setSpeed(float speed)
    {
        nativeSetSpeed(this.pointer, speed);
    }

    public float getJumpPower()
    {
        return nativeGetJumpPower(this.pointer);
    }

    public int getMeleeWeaponDamageBonus(Mob mob)
    {
        return nativeGetMeleeWeaponDamageBonus(this.pointer, mob.getPointer());
    }

    public float getMeleeKnockbackBonus()
    {
        return nativeGetMeleeKnockbackBonus(this.pointer);
    }

    public void travel(float strafe, float vertical, float forward)
    {
        nativeTravel(this.pointer, strafe, vertical, forward);
    }

    public void applyFinalFriction(float friction, boolean discardFriction)
    {
        nativeApplyFinalFriction(this.pointer, friction, discardFriction);
    }

    public boolean isLookingAtAnEntity()
    {
        return nativeIsLookingAtAnEntity(this.pointer);
    }

    public int getItemUseDuration()
    {
        return nativeGetItemUseDuration(this.pointer);
    }

    public float getItemUseStartupProgress()
    {
        return nativeGetItemUseStartupProgress(this.pointer);
    }

    public float getItemUseIntervalProgress()
    {
        return nativeGetItemUseIntervalProgress(this.pointer);
    }

    public float getMaxHeadXRot()
    {
        return nativeGetMaxHeadXRot(this.pointer);
    }

    @Nullable public Mob getLastHurtByMob()
    {
        long mobptr = nativeGetLastHurtByMob(this.pointer);
        if(mobptr == 0L) return null;
        return new Mob(mobptr, true);
    }

    public void setLastHurtByMob(Mob mob)
    {
        nativeSetLastHurtByMob(this.pointer, mob.getPointer());
    }

    // TODO Player

    @Nullable public Actor getLastHurtMob()
    {
        long actorptr = nativeGetLastHurtMob(this.pointer);
        if(actorptr == 0L) return null;
        return new Actor(actorptr, true);
    }

    public void setLastHurtMob(Actor actor)
    {
        nativeSetLastHurtMob(this.pointer, actor.getPointer());
    }

    public boolean isAlliedTo(Mob mob)
    {
        return nativeIsAlliedTo(this.pointer, mob.getPointer());
    }

    public boolean canBeControlledByRider()
    {
        return nativeCanBeControlledByRider(this.pointer);
    }

    public void leaveCaravan()
    {
        nativeLeaveCaravan(this.pointer);
    }

    public void joinCaravan(Mob caravanHead)
    {
        nativeJoinCaravan(this.pointer, caravanHead.getPointer());
    }

    public boolean hasCaravanTail()
    {
        return nativeHasCaravanTail(this.pointer);
    }

    @Nullable public Mob getCaravanHead()
    {
        long mobptr = nativeGetCaravanHead(this.pointer);
        if(mobptr == 0L) return null;
        return new Mob(mobptr, true);
    }

    public int getArmorValue()
    {
        return nativeGetArmorValue(this.pointer);
    }

    public float getArmorCoverPercentage()
    {
        return nativeGetArmorCoverPercentage(this.pointer);
    }

    @Nullable public ItemStack getItemSlot(int slot)
    {
        long stackptr = nativeGetItemSlot(this.pointer, slot);
        if(stackptr == 0L) return null;
        return ItemStack.fromPtr(stackptr);
    }

    public void setItemSlot(int slot, int id, int count, int data)
    {
        this.setItemSlot(slot, id, count, data, null);
    }

    public void setItemSlot(int slot, int id, int count, int data, NativeItemInstanceExtra extra)
    {
        nativeSetItemSlot(this.pointer, slot, id, count, data, extra != null ? extra.getValue() : 0L);
    }

    public boolean isTransitioningSitting()
    {
        return nativeIsTransitioningSitting(this.pointer);
    }

    public void setTransitioningSitting(boolean transitioningSitting)
    {
        nativeSetTransitioningSitting(this.pointer, transitioningSitting);
    }

    public boolean canExistWhenDisallowMob()
    {
        return nativeCanExistWhenDisallowMob(this.pointer);
    }

    public void jumpFromGround()
    {
        nativeJumpFromGround(this.pointer);
    }

    public int getNoActionTime()
    {
        return nativeGetNoActionTime(this.pointer);
    }

    public void resetNoActionTime()
    {
        nativeResetNoActionTime(this.pointer);
    }

    public boolean wantsToBeJockey()
    {
        return nativeWantsToBeJockey(this.pointer);
    }

    public void setWantsToBeJockey(boolean wantsToBeJockey)
    {
        nativeSetWantsToBeJockey(this.pointer, wantsToBeJockey);
    }

    public boolean isLayingEgg()
    {
        return nativeIsLayingEgg(this.pointer);
    }

    public void setIsLayingEgg(boolean laying)
    {
        nativeSetIsLayingEgg(this.pointer, laying);
    }

    public int getGlidingTicks()
    {
        return nativeGetGlidingTicks(this.pointer);
    }

    public float getFrictionModifier()
    {
        return nativeGetFrictionModifier(this.pointer);
    }

    public void setFrictionModifier(float frictionModifier)
    {
        nativeSetFrictionModifier(this.pointer, frictionModifier);
    }

    public void snapToYBodyRot(float rot)
    {
        nativeSnapToYBodyRot(this.pointer, rot);
    }

    public void snapToYHeadRot(float rot)
    {
        nativeSnapToYHeadRot(this.pointer, rot);
    }

    public void incrementArrowCount(int increment)
    {
        nativeIncrementArrowCount(this.pointer, increment);
    }

    public boolean canPickUpLoot(int id, int count, int data)
    {
        return this.canPickUpLoot(id, count, data, null);
    }

    public boolean canPickUpLoot(int id, int count, int data, NativeItemInstanceExtra extra)
    {
        return nativeCanPickUpLoot(this.pointer, id, count, data, extra != null ? extra.getValue() : 0L);
    }

    public float getJumpMultiplier()
    {
        return nativeGetJumpMultiplier(this.pointer);
    }

    public boolean hasBeenHurtByMobInLastTicks(int ticks)
    {
        return nativeHasBeenHurtByMobInLastTicks(this.pointer, ticks);
    }

    public boolean isHeadInWater()
    {
        return nativeIsHeadInWater(this.pointer);
    }

    public float getMovementComponentCurrentSpeed()
    {
        return nativeGetMovementComponentCurrentSpeed(this.pointer);
    }

    public void setMovementComponentCurrentSpeed(float speed)
    {
        nativeSetMovementComponentCurrentSpeed(this.pointer, speed);
    }

    public float getFlightSpeed()
    {
        return nativeGetFlightSpeed(this.pointer);
    }

    public void setFlightSpeed(float speed)
    {
        nativeSetFlightSpeed(this.pointer, speed);
    }

    public boolean isInterpolationActive()
    {
        return nativeIsInterpolationActive(this.pointer);
    }

    public void setInterpolationActive(boolean interpolationActive)
    {
        nativeSetInterpolationActive(this.pointer, interpolationActive);
    }

    public void setYHeadRot(float rot)
    {
        nativeSetYHeadRot(this.pointer, rot);
    }

    public float getRiderRotLimit()
    {
        return nativeGetRiderRotLimit(this.pointer);
    }

    public void setRiderRotLimit(float lim)
    {
        nativeSetRiderRotLimit(this.pointer, lim);
    }

    public int getRollCounter()
    {
        return nativeGetRollCounter(this.pointer);
    }

    public boolean isRolling()
    {
        return nativeIsRolling(this.pointer);
    }

    public void setRolling(boolean rolling)
    {
        nativeSetRolling(this.pointer, rolling);
    }

    public int getSpawnMethod()
    {
        return nativeGetSpawnMethod(this.pointer);
    }

    public void setSpawnMethod(int method)
    {
        nativeSetSpawnMethod(this.pointer, method);
    }

    public float getXxa()
    {
        return nativeGetXxa(this.pointer);
    }

    public void setXxa(float xxa)
    {
        nativeSetXxa(this.pointer, xxa);
    }

    public float getYya()
    {
        return nativeGetYya(this.pointer);
    }

    public void setYya(float yya)
    {
        nativeSetYya(this.pointer, yya);
    }

    public float getZza()
    {
        return nativeGetZza(this.pointer);
    }

    public void setZza(float zza)
    {
        nativeSetZza(this.pointer, zza);
    }

    public int getTravelType()
    {
        return nativeGetTravelType(this.pointer);
    }

    public void setSurfaceMob(boolean surface)
    {
        nativeSetSurfaceMob(this.pointer, surface);
    }

    public boolean isPregnant()
    {
        return nativeIsPregnant(this.pointer);
    }

    public void setIsPregnant(boolean pregnant)
    {
        nativeSetIsPregnant(this.pointer, pregnant);
    }

    public boolean isNaturallySpawned()
    {
        return nativeIsNaturallySpawned(this.pointer);
    }

    public void setNaturallySpawned(boolean naturally)
    {
        nativeSetNaturallySpawned(this.pointer, naturally);
    }

    public float getRiderLockedBodyRot()
    {
        return nativeGetRiderLockedBodyRot(this.pointer);
    }

    public void setRiderLockedBodyRot(float rot)
    {
        nativeSetRiderLockedBodyRot(this.pointer, rot);
    }

    public boolean isFrostWalking()
    {
        return nativeIsFrostWalking(this.pointer);
    }

    public void setJumpVelRedux(boolean redux)
    {
        nativeSetJumpVelRedux(this.pointer, redux);
    }

    public float calcMoveRelativeSpeed(int travelType)
    {
        return nativeCalcMoveRelativeSpeed(this.pointer, travelType);
    }

    public boolean isEating()
    {
        return nativeIsEating(this.pointer);
    }

    public void setEating(boolean eating)
    {
        nativeSetEating(this.pointer, eating);
    }

    public int getEatCounter()
    {
        return nativeGetEatCounter(this.pointer);
    }

    public void setEatCounter(int counter)
    {
        nativeSetEatCounter(this.pointer, counter);
    }

    public boolean hasBoundOrigin()
    {
        return nativeHasBoundOrigin(this.pointer);
    }

    public int getCaravanSize()
    {
        return nativeGetCaravanSize(this.pointer);
    }

    public boolean shouldApplyWaterGravity()
    {
        return nativeShouldApplyWaterGravity(this.pointer);
    }

    public boolean isGliding()
    {
        return nativeIsGliding(this.pointer);
    }

    @Nullable public Mob getFirstCaravanHead()
    {
        long mobptr = nativeGetFirstCaravanHead(this.pointer);
        if(mobptr == 0L) return null;
        return new Mob(mobptr, true);
    }

    public float getYRotA()
    {
        return nativeGetYRotA(this.pointer);
    }

    public void setYRotA(float yrota)
    {
        nativeSetYRotA(this.pointer, yrota);
    }

    public void setJumping(boolean jumping)
    {
        nativeSetJumping(this.pointer, jumping);
    }

    public void setSpeedModifier(float speedMod)
    {
        nativeSetSpeedModifier(this.pointer, speedMod);
    }

    public int getCurrentSwingDuration()
    {
        return nativeGetCurrentSwingDuration(this.pointer);
    }

    public boolean isSwinging()
    {
        return nativeIsSwinging(this.pointer);
    }

    public int calculateJumpImpulse()
    {
        return nativeCalculateJumpImpulse(this.pointer);
    }

    public boolean isSlime()
    {
        return nativeIsSlime(this.pointer);
    }

    @Nullable public Slime asSlime()
    {
        if(!this.isSlime()) return null;
        return new Slime(this);
    }

}
