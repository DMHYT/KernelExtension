package vsdum.kex.modules.misc;

import vsdum.kex.common.INativeInterface;

public class ReachDistanceModifier implements INativeInterface {

    protected static native long nativeConstruct();
    protected static native void nativeSetModifier(long ptr, float modifier);
    protected static native void nativeSetMultiplier(long ptr, float multiplier);
    protected static native void nativeToggle(long ptr, boolean enabled);
    protected static native float nativeGetModifier(long ptr);
    protected static native float nativeGetMultiplier(long ptr);
    protected static native boolean nativeIsActive(long ptr);
    
    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public ReachDistanceModifier()
    {
        this.pointer = nativeConstruct();
    }

    public ReachDistanceModifier setModifier(float modifier)
    {
        nativeSetModifier(this.pointer, modifier);
        return this;
    }

    public ReachDistanceModifier setMultiplier(float multiplier)
    {
        nativeSetMultiplier(this.pointer, multiplier);
        return this;
    }

    public ReachDistanceModifier enable()
    {
        nativeToggle(this.pointer, true);
        return this;
    }

    public ReachDistanceModifier disable()
    {
        nativeToggle(this.pointer, false);
        return this;
    }

    public float getModifier()
    {
        return nativeGetModifier(this.pointer);
    }

    public float getMultiplier()
    {
        return nativeGetMultiplier(this.pointer);
    }

    public boolean isActive()
    {
        return nativeIsActive(this.pointer);
    }

}
