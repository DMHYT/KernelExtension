package vsdum.kex.natives;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;

public class MobEffect implements INativeInterface {
    
    protected static native long nativeGetById(int id);
    protected static native boolean nativeIsVisible(long ptr);
    protected static native int nativeGetId(long ptr);
    protected static native boolean nativeIsHarmful(long ptr);
    
    protected final long pointer;
    
    public final long getPointer()
    {
        return this.pointer;
    }

    public MobEffect(long ptr)
    {
        this.pointer = ptr;
    }

    @Nullable public static MobEffect getById(int id)
    {
        long ptr = nativeGetById(id);
        if(ptr == 0L) return null;
        return new MobEffect(ptr);
    }

    public boolean isVisible()
    {
        return nativeIsVisible(this.pointer);
    }

    public int getId()
    {
        return nativeGetId(this.pointer);
    }

    public boolean isHarmful()
    {
        return nativeIsHarmful(this.pointer);
    }

}
