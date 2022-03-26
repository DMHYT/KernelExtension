package vsdum.kex.natives;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.apparatus.mcpe.NativePlayer;
import com.zhekasmirnov.innercore.api.NativeItemInstanceExtra;

public class Player extends Mob {

    protected static native boolean nativeIsAutoJumpEnabled(long ptr);
    protected static native int nativeGetCommandPermissionLevel(long ptr);
    protected static native void nativeSetPermissions(long ptr, int level);
    protected static native int nativeGetPlayerPermissionLevel(long ptr);
    protected static native void nativeDisplayChatMessage(long ptr, String prefix, String message);
    protected static native void nativeDisplayClientMessage(long ptr, String message);
    protected static native void nativeDisplayWhisperMessage(long ptr, String s1, String s2, String s3, String s4);
    protected static native void nativeStartSleepInBed(long ptr, int x, int y, int z);
    protected static native void nativeStopSleepInBed(long ptr, boolean b1, boolean b2);
    protected static native boolean nativeCanStartSleepInBed(long ptr);
    protected static native int nativeGetSleepTimer(long ptr);
    protected static native int nativeGetPreviousTickSleepTimer(long ptr);
    protected static native void nativeOpenSign(long ptr, int x, int y, int z);
    protected static native void nativePlayEmote(long ptr, String emote);
    protected static native boolean nativeIsHostingPlayer(long ptr);
    protected static native void nativeSetGameMode(long ptr, int mode);
    protected static native void nativeAddLevels(long ptr, int levels);
    protected static native void nativeSetFieldOfViewModifier(long ptr, float modifier);
    protected static native void nativeStartCooldown(long ptr, int id);
    protected static native void nativeStartGliding(long ptr);
    protected static native void nativeStopGliding(long ptr);
    protected static native boolean nativeIsChatAllowed(long ptr);
    protected static native boolean nativeGetHasSeenCredits(long ptr);
    protected static native void nativeSetHasSeenCredits(long ptr, boolean seen);
    protected static native boolean nativeShouldShowCredits(long ptr);
    protected static native int nativeGetLuck(long ptr);
    protected static native boolean nativeForceAllowEating(long ptr);
    protected static native void nativeEat(long ptr, int nutrition, float saturation);
    protected static native void nativeEat2(long ptr, int nutrition, float saturationModifier);
    protected static native void nativeCauseFoodExhaustion(long ptr, float value);
    protected static native boolean nativeIsBouncing(long ptr);
    protected static native boolean nativeIsForcedRespawn(long ptr);
    protected static native int nativeGetEnchantmentSeed(long ptr);
    protected static native void nativeSetEnchantmentSeed(long ptr, int seed);
    protected static native int nativeGetNewEnchantmentSeed(long ptr);
    protected static native int nativeGetTicksUsingItem(long ptr);
    protected static native boolean nativeCanUseOperatorBlocks(long ptr);
    protected static native boolean nativeIsOperator(long ptr);
    protected static native boolean nativeIsViewer(long ptr);
    protected static native int nativeGetXpNeededForNextLevel(long ptr);
    protected static native int nativeGetXpNeededForLevelRange(long ptr, int min, int max);
    protected static native boolean nativeIsEmoting(long ptr);
    protected static native float nativeGetLevelProgress(long ptr);
    protected static native int nativeGetMapIndex(long ptr);
    protected static native void nativeSetMapIndex(long ptr, int index);
    protected static native int nativeGetAttackDamage(long ptr);
    protected static native boolean nativeIsHungry(long ptr);
    protected static native boolean nativeIsInRaid(long ptr);
    protected static native boolean nativeHasOpenContainer(long ptr);
    protected static native boolean nativeIsUsingItem(long ptr);
    protected static native float nativeGetUnderwaterLightLevel(long ptr);
    protected static native void nativeSetUnderwaterLightLevel(long ptr, float level);
    protected static native boolean nativeCanBeSeenOnMap(long ptr);

    private final NativePlayer shortcut;

    public Player(long entity)
    {
        super(entity);
        if(!this.isPlayer())
            throw new IllegalArgumentException("The given entity is not a Player! Consider using Actor.asPlayer() in order not to get exceptions thrown!");
        this.shortcut = new NativePlayer(this.getUniqueID());
    }

    protected Player(long ptr, boolean flag)
    {
        super(ptr, flag);
        this.shortcut = new NativePlayer(this.getUniqueID());
    }

    public Player(Mob mob)
    {
        this(mob.pointer, true);
        if(!this.isPlayer())
            throw new IllegalArgumentException("The given Mob is not a Player! Consider using Mob.asPlayer() in order not to get exceptions thrown!");
    }

    public Player(Actor actor)
    {
        this(actor.pointer, true);
        if(!this.isPlayer())
            throw new IllegalArgumentException("The given Actor is not a Player! Consider using Actor.asPlayer() in order not to get exceptions thrown!");
    }

    public void addExperience(int exp)
    {
        this.shortcut.addExperience(exp);
    }

    public void addItemToInventory(int id, int count, int data)
    {
        this.addItemToInventory(id, count, data, null);
    }

    public void addItemToInventory(int id, int count, int data, NativeItemInstanceExtra extra)
    {
        this.addItemToInventory(id, count, data, extra, true);
    }

    public void addItemToInventory(int id, int count, int data, NativeItemInstanceExtra extra, boolean dropRemaining)
    {
        this.shortcut.addItemToInventory(id, count, data, extra, dropRemaining);
    }

    public float getExhaustion()
    {
        return this.shortcut.getExhaustion();
    }

    public float getExperience()
    {
        return this.shortcut.getExperience();
    }

    public int getGameMode()
    {
        return this.shortcut.getGameMode();
    }

    public float getHunger()
    {
        return this.shortcut.getHunger();
    }

    public ItemStack getInventorySlot(int slot)
    {
        return this.shortcut.getInventorySlot(slot);
    }

    public float getExpLevel()
    {
        return this.shortcut.getLevel();
    }

    public float getSaturation()
    {
        return this.shortcut.getSaturation();
    }

    public int getScore()
    {
        return this.shortcut.getScore();
    }

    public int getSelectedSlot()
    {
        return this.shortcut.getSelectedSlot();
    }

    public void invokeUseItemNoTarget(int id, int count, int data, NativeItemInstanceExtra extra)
    {
        this.shortcut.invokeUseItemNoTarget(id, count, data, extra);
    }

    public void setExhaustion(float value)
    {
        this.shortcut.setExhaustion(value);
    }

    public void setExperience(float value)
    {
        this.shortcut.setExperience(value);
    }

    public void setHunger(float value)
    {
        this.shortcut.setHunger(value);
    }

    public void setInventorySlot(int slot, int id, int count, int data, NativeItemInstanceExtra extra)
    {
        this.shortcut.setInventorySlot(slot, id, count, data, extra);
    }

    public void setExpLevel(float level)
    {
        this.shortcut.setLevel(level);
    }

    public void setRespawnCoords(int x, int y, int z)
    {
        this.shortcut.setRespawnCoords(x, y, z);
    }

    public void setSaturation(float value)
    {
        this.shortcut.setSaturation(value);
    }

    public void setSelectedSlot(int slot)
    {
        this.shortcut.setSelectedSlot(slot);
    }

    public void spawnExpOrbs(float x, float y, float z, int value)
    {
        this.shortcut.spawnExpOrbs(x, y, z, value);
    }

    public boolean isAutoJumpEnabled()
    {
        return nativeIsAutoJumpEnabled(this.pointer);
    }

    public int getCommandPermissionLevel()
    {
        return nativeGetCommandPermissionLevel(this.pointer);
    }

    public void setPermissions(int level)
    {
        nativeSetPermissions(this.pointer, level);
    }

    public int getPlayerPermissionLevel()
    {
        return nativeGetPlayerPermissionLevel(this.pointer);
    }

    public void displayChatMessage(String prefix, String message)
    {
        nativeDisplayChatMessage(this.pointer, prefix, message);
    }

    public void displayClientMessage(String message)
    {
        nativeDisplayClientMessage(this.pointer, message);
    }

    public void displayWhisperMessage(String s1, String s2, String s3, String s4)
    {
        nativeDisplayWhisperMessage(this.pointer, s1, s2, s3, s4);
    }

    public void startSleepInBed(int x, int y, int z)
    {
        nativeStartSleepInBed(this.pointer, x, y, z);
    }

    public void stopSleepInBed(boolean b1, boolean b2)
    {
        nativeStopSleepInBed(this.pointer, b1, b2);
    }

    public boolean canStartSleepInBed()
    {
        return nativeCanStartSleepInBed(this.pointer);
    }

    public int getSleepTimer()
    {
        return nativeGetSleepTimer(this.pointer);
    }

    public int getPreviousTickSleepTimer()
    {
        return nativeGetPreviousTickSleepTimer(this.pointer);
    }

    public void openSign(int x, int y, int z)
    {
        nativeOpenSign(this.pointer, x, y, z);
    }

    public void playEmote(String emote)
    {
        nativePlayEmote(this.pointer, emote);
    }

    public boolean isHostingPlayer()
    {
        return nativeIsHostingPlayer(this.pointer);
    }

    public void setGameMode(int mode)
    {
        nativeSetGameMode(this.pointer, mode);
    }

    public void addLevels(int levels)
    {
        nativeAddLevels(this.pointer, levels);
    }

    public void setFieldOfViewModifier(float modifier)
    {
        nativeSetFieldOfViewModifier(this.pointer, modifier);
    }

    public void startCooldown(int id)
    {
        nativeStartCooldown(this.pointer, id);
    }

    public void startGliding()
    {
        nativeStartGliding(this.pointer);
    }

    public void stopGliding()
    {
        nativeStopGliding(this.pointer);
    }

    public boolean isChatAllowed()
    {
        return nativeIsChatAllowed(this.pointer);
    }

    public boolean getHasSeenCredits()
    {
        return nativeGetHasSeenCredits(this.pointer);
    }
    
    public void setHasSeenCredits(boolean seen)
    {
        nativeSetHasSeenCredits(this.pointer, seen);
    }

    public boolean shouldShowCredits()
    {
        return nativeShouldShowCredits(this.pointer);
    }

    public int getLuck()
    {
        return nativeGetLuck(this.pointer);
    }
    
    public boolean forceAllowEating()
    {
        return nativeForceAllowEating(this.pointer);
    }

    public void eat(int nutrition, float saturation)
    {
        nativeEat(this.pointer, nutrition, saturation);
    }

    public void eat2(int nutrition, float saturationModifier)
    {
        nativeEat2(this.pointer, nutrition, saturationModifier / 2.0f);
    }

    public void causeFoodExhaustion(float exhaustion)
    {
        nativeCauseFoodExhaustion(this.pointer, exhaustion);
    }

    public boolean isBouncing()
    {
        return nativeIsBouncing(this.pointer);
    }

    public boolean isForcedRespawn()
    {
        return nativeIsForcedRespawn(this.pointer);
    }

    public int getEnchantmentSeed()
    {
        return nativeGetEnchantmentSeed(this.pointer);
    }

    public void setEnchantmentSeed(int seed)
    {
        nativeSetEnchantmentSeed(this.pointer, seed);
    }

    public int getNewEnchantmentSeed()
    {
        return nativeGetNewEnchantmentSeed(this.pointer);
    }

    public int getTicksUsingItem()
    {
        return nativeGetTicksUsingItem(this.pointer);
    }

    public boolean canUseOperatorBlocks()
    {
        return nativeCanUseOperatorBlocks(this.pointer);
    }

    public boolean isOperator()
    {
        return nativeIsOperator(this.pointer);
    }

    public boolean isViewer()
    {
        return nativeIsViewer(this.pointer);
    }

    public int getXpNeededForNextLevel()
    {
        return nativeGetXpNeededForNextLevel(this.pointer);
    }

    public int getXpNeededForLevelRange(int min, int max)
    {
        return nativeGetXpNeededForLevelRange(this.pointer, min, max);
    }

    public boolean isEmoting()
    {
        return nativeIsEmoting(this.pointer);
    }

    public float getLevelProgress()
    {
        return nativeGetLevelProgress(this.pointer);
    }

    public int getMapIndex()
    {
        return nativeGetMapIndex(this.pointer);
    }

    public void setMapIndex(int index)
    {
        nativeSetMapIndex(this.pointer, index);
    }

    public int getAttackDamage()
    {
        return nativeGetAttackDamage(this.pointer);
    }

    public boolean isHungry()
    {
        return nativeIsHungry(this.pointer);
    }

    public boolean isInRaid()
    {
        return nativeIsInRaid(this.pointer);
    }

    public boolean hasOpenContainer()
    {
        return nativeHasOpenContainer(this.pointer);
    }

    public boolean isUsingItem()
    {
        return nativeIsUsingItem(this.pointer);
    }

    public float getUnderwaterLightLevel()
    {
        return nativeGetUnderwaterLightLevel(this.pointer);
    }

    public void setUnderwaterLightLevel(float level)
    {
        nativeSetUnderwaterLightLevel(this.pointer, level);
    }

    public boolean canBeSeenOnMap()
    {
        return nativeCanBeSeenOnMap(this.pointer);
    }

}
