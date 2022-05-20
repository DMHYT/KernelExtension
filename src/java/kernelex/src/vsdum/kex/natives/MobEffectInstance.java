package vsdum.kex.natives;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;

public class MobEffectInstance implements INativeInterface {
    
    protected static native int nativeGetId(long ptr);
    protected static native int nativeGetDuration(long ptr);
    protected static native int nativeGetDifficultyDuration(long ptr, int difficulty);
    protected static native int nativeGetAmplifier(long ptr);
    protected static native boolean nativeDisplaysOnScreenTextureAnimation(long ptr);
    protected static native boolean nativeIsAmbient(long ptr);
    protected static native boolean nativeIsNoCounter(long ptr);
    protected static native boolean nativeIsEffectVisible(long ptr);
    protected static native void nativeSetDuration(long ptr, int duration);
    protected static native void nativeSetDifficultyDuration(long ptr, int difficulty, int duration);
    protected static native void nativeSetNoCounter(long ptr, boolean noCounter);

    protected final long pointer;
    private final boolean isNative;
    private final int id;
    private int durationPeaceful;
    private int durationEasy;
    private int durationNormal;
    private int durationHard;
    private final int amplifier;
    private final boolean _displaysOnScreenTextureAnimation;
    private final boolean _isAmbient;
    private boolean _isNoCounter = false;
    private final boolean _isEffectVisible;
    @Nullable private final MobEffect effect;

    public final long getPointer()
    {
        return this.pointer;
    }

    public MobEffectInstance(long ptr, boolean flagForPointerOverload)
    {
        this.isNative = true;
        this.pointer = ptr;
        this.id = nativeGetId(this.pointer);
        this.effect = MobEffect.getById(this.id);
        this.durationPeaceful = nativeGetDuration(this.pointer);
        this.durationEasy = nativeGetDifficultyDuration(this.pointer, 1);
        this.durationNormal = nativeGetDifficultyDuration(this.pointer, 2);
        this.durationHard = nativeGetDifficultyDuration(this.pointer, 3);
        this.amplifier = nativeGetAmplifier(this.pointer);
        this._displaysOnScreenTextureAnimation = nativeDisplaysOnScreenTextureAnimation(this.pointer);
        this._isAmbient = nativeIsAmbient(this.pointer);
        this._isNoCounter = nativeIsNoCounter(this.pointer);
        this._isEffectVisible = nativeIsEffectVisible(this.pointer);
    }

    public MobEffectInstance(int id)
    {
        this(id, 0);
    }

    public MobEffectInstance(int id, int duration)
    {
        this(id, duration, 0);
    }

    public MobEffectInstance(int id, int duration, int amplifier)
    {
        this(id, duration, amplifier, false, true, false);
    }

    public MobEffectInstance(int id, int duration, int amplifier, boolean isAmbient, boolean isEffectVisible, boolean displaysOnScreenTextureAnimation)
    {
        this(id, duration, -1, -1, -1, amplifier, isAmbient, isEffectVisible, displaysOnScreenTextureAnimation);
    }

    public MobEffectInstance(int id, int durationPeaceful, int durationEasy, int durationNormal, int durationHard, int amplifier, boolean isAmbient, boolean isEffectVisible, boolean displaysOnScreenTextureAnimation)
    {
        this.isNative = false;
        this.pointer = 0L;
        this.id = id;
        this.effect = MobEffect.getById(this.id);
        this.durationPeaceful = durationPeaceful;
        this.durationEasy = durationEasy;
        this.durationNormal = durationNormal;
        this.durationHard = durationHard;
        this.amplifier = amplifier;
        this._isAmbient = isAmbient;
        this._isEffectVisible = isEffectVisible;
        this._displaysOnScreenTextureAnimation = displaysOnScreenTextureAnimation;
    }

    public final int getId()
    {
        return this.id;
    }

    public final int getDuration()
    {
        return this.isNative ? (this.durationPeaceful = nativeGetDuration(this.pointer)) : this.durationPeaceful;
    }
    
    public final void setDuration(int duration)
    {
        this.durationPeaceful = duration;
        if(this.isNative) nativeSetDuration(this.pointer, duration);
    }

    private final int _getDifficultyDuration(int difficulty)
    {
        switch(difficulty)
        {
            case 1: return this.durationEasy;
            case 2: return this.durationNormal;
            case 3: return this.durationHard;
            default: return -1;
        }
    }

    public final boolean hasDifficultyDuration(int difficulty)
    {
        return _getDifficultyDuration(difficulty) != -1;
    }

    public final int getDifficultyDuration(int difficulty)
    {
        return hasDifficultyDuration(difficulty) ? _getDifficultyDuration(difficulty) : this.durationPeaceful;
    }

    public final void setDifficultyDuration(int difficulty, int duration)
    {
        switch(difficulty)
        {
            case 1: this.durationEasy = duration; break;
            case 2: this.durationNormal = duration; break;
            case 3: this.durationHard = duration; break;
            default: break;
        }
        if(this.isNative) nativeSetDifficultyDuration(this.pointer, difficulty, duration);
    }

    public final int getAmplifier()
    {
        return this.amplifier;
    }

    public final boolean isAmbient()
    {
        return this._isAmbient;
    }

    public final boolean isEffectVisible()
    {
        return this._isEffectVisible;
    }

    public final boolean displaysOnScreenTextureAnimation()
    {
        return this._displaysOnScreenTextureAnimation;
    }

    public final boolean isNoCounter()
    {
        return this.isNative ? (this._isNoCounter = nativeIsNoCounter(this.pointer)) : this._isNoCounter;
    }

    public final void setNoCounter(boolean noCounter)
    {
        this._isNoCounter = noCounter;
        if(this.isNative) nativeSetNoCounter(this.pointer, noCounter);
    }

    public final int getSplashDuration()
    {
        return (int) (this.getDuration() * .75);
    }

    public final int getLingerDuration()
    {
        return (int) (this.getDuration() * .25);
    }

    @Nullable public final MobEffect getEffect()
    {
        return this.effect;
    }

}
