package vsdum.kex.modules.misc;

import vsdum.kex.common.INativeInterface;

public class CameraRollModifier implements INativeInterface {
    
    protected static native long nativeConstruct();
    protected static native void nativeSetModifier(long ptr, float modifier);
    protected static native void nativeSetInterpolationEnabled(long ptr, boolean enabled);
    protected static native void nativeSetSmoothing(long ptr, float smoothing);
    protected static native void nativeToggle(long ptr, boolean enabled);
    protected static native float nativeGetModifier(long ptr);
    protected static native boolean nativeIsInterpolationEnabled(long ptr);
    protected static native float nativeGetSmoothing(long ptr);
    protected static native boolean nativeIsActive(long ptr);

    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public CameraRollModifier()
    {
        this.pointer = nativeConstruct();
    }

    public CameraRollModifier setModifier(float modifier)
    {
        nativeSetModifier(this.pointer, modifier);
        return this;
    }

    public CameraRollModifier setInterpolationEnabled(boolean enabled)
    {
        nativeSetInterpolationEnabled(this.pointer, enabled);
        return this;
    }

    public CameraRollModifier setSmoothing(float smoothing)
    {
        nativeSetSmoothing(this.pointer, smoothing);
        return this;
    }

    public CameraRollModifier enable()
    {
        nativeToggle(this.pointer, true);
        return this;
    }

    public CameraRollModifier disable()
    {
        nativeToggle(this.pointer, false);
        return this;
    }

    public float getModifier()
    {
        return nativeGetModifier(this.pointer);
    }
    
    public boolean isInterpolationEnabled()
    {
        return nativeIsInterpolationEnabled(this.pointer);
    }

    public float getSmoothing()
    {
        return nativeGetSmoothing(this.pointer);
    }

    public boolean isActive()
    {
        return nativeIsActive(this.pointer);
    }

}
