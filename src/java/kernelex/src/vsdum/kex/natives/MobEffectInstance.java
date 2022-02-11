package vsdum.kex.natives;

import vsdum.kex.common.INativeInterface;

public class MobEffectInstance implements INativeInterface {
    
    protected static native long nativeConstruct(int id, int duration, int ampl);
    protected static native long nativeConstruct(int id, int duration, int ampl, boolean isAmbient, boolean alwaysTrue, boolean displaysOnScreenTextureAnimation);
    protected static native long nativeConstruct(int id, int duration);
    protected static native long nativeConstruct(int id);
    protected static native boolean nativeIsNoCounter(long ptr);
    protected static native boolean nativeIsAmbient(long ptr);
    protected static native int nativeGetAmplifier(long ptr);
    protected static native boolean nativeIsEffectVisible(long ptr);
    protected static native int nativeGetDuration(long ptr);
    protected static native int nativeGetId(long ptr);
    protected static native boolean nativeDisplaysOnScreenTextureAnimation(long ptr);

    protected final long pointer;
    private final int id;
    private final MobEffect effect;
    private final int amplifier;
    private final boolean _isAmbient;
    private final boolean _isVisible;
    private final boolean _displaysOnScreenTextureAnimation;

    public final long getPointer()
    {
        return this.pointer;
    }

    public MobEffectInstance(long ptr, boolean flagForPointerOverload)
    {
        this.pointer = ptr;
        this.id = nativeGetId(this.pointer);
        this.effect = MobEffect.getById(this.id);
        this.amplifier = nativeGetAmplifier(this.pointer);
        this._isAmbient = nativeIsAmbient(this.pointer);
        this._isVisible = nativeIsEffectVisible(this.pointer);
        this._displaysOnScreenTextureAnimation = nativeDisplaysOnScreenTextureAnimation(this.pointer);
    }

    public MobEffectInstance(int id)
    {
        this.pointer = nativeConstruct(id);
        this.id = id;
        this.effect = MobEffect.getById(this.id);
        this.amplifier = 0;
        this._isAmbient = nativeIsAmbient(this.pointer);
        this._isVisible = nativeIsEffectVisible(this.pointer);
        this._displaysOnScreenTextureAnimation = nativeDisplaysOnScreenTextureAnimation(this.pointer);
    }

    public MobEffectInstance(int id, int duration)
    {
        this.pointer = nativeConstruct(id, duration);
        this.id = id;
        this.effect = MobEffect.getById(this.id);
        this.amplifier = 0;
        this._isAmbient = nativeIsAmbient(this.pointer);
        this._isVisible = nativeIsEffectVisible(this.pointer);
        this._displaysOnScreenTextureAnimation = nativeDisplaysOnScreenTextureAnimation(this.pointer);
    }

    public MobEffectInstance(int id, int duration, int amplifier)
    {
        this.pointer = nativeConstruct(id, duration, amplifier);
        this.id = id;
        this.effect = MobEffect.getById(this.id);
        this.amplifier = amplifier;
        this._isAmbient = nativeIsAmbient(this.pointer);
        this._isVisible = nativeIsEffectVisible(this.pointer);
        this._displaysOnScreenTextureAnimation = nativeDisplaysOnScreenTextureAnimation(this.pointer);
    }

    public MobEffectInstance(int id, int duration, int amplifier, boolean isAmbient, boolean alwaysTrue, boolean __displaysOnScreenTextureAnimation) {
        this.pointer = nativeConstruct(id, duration, amplifier, isAmbient, alwaysTrue, __displaysOnScreenTextureAnimation);
        this.id = id;
        this.effect = MobEffect.getById(this.id);
        this.amplifier = amplifier;
        this._isAmbient = isAmbient;
        this._isVisible = alwaysTrue;
        this._displaysOnScreenTextureAnimation = __displaysOnScreenTextureAnimation;
    }

    public final int getId()
    {
        return this.id;
    }

    public final MobEffect getEffect()
    {
        return this.effect;
    }

    public final int getAmplifier()
    {
        return this.amplifier;
    }

    public final boolean isAmbient()
    {
        return this._isAmbient;
    }

    public final boolean isVisible()
    {
        return this._isVisible;
    }

    public final boolean displaysOnScreenTextureAnimation()
    {
        return this._displaysOnScreenTextureAnimation;
    }

    public final boolean isNoCounter()
    {
        return nativeIsNoCounter(this.pointer);
    }

    public final int getDuration()
    {
        return nativeGetDuration(this.pointer);
    }

}
