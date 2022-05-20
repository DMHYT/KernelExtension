package vsdum.kex.natives;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;

public class MobEffect implements INativeInterface {
    
    protected static native long nativeGetById(int id);
    protected static native boolean nativeIsVisible(long ptr);
    protected static native int nativeGetId(long ptr);
    protected static native boolean nativeIsHarmful(long ptr);
    @Nullable protected static native String nativeGetDescriptionId(long ptr);
    
    protected final long pointer;

    private final int id;
    private final boolean visible;
    private final boolean harmful;
    @Nullable private final String descriptionId;
    
    public final long getPointer()
    {
        return this.pointer;
    }

    public MobEffect(long ptr)
    {
        this.pointer = ptr;
        this.id = nativeGetId(this.pointer);
        this.visible = nativeIsVisible(this.pointer);
        this.harmful = nativeIsHarmful(this.pointer);
        this.descriptionId = nativeGetDescriptionId(this.pointer);
    }

    @Nullable public static MobEffect getById(int id)
    {
        long ptr = nativeGetById(id);
        if(ptr == 0L) return null;
        return new MobEffect(ptr);
    }

    public final boolean isVisible()
    {
        return this.visible;
    }

    public final int getId()
    {
        return this.id;
    }

    public final boolean isHarmful()
    {
        return this.harmful;
    }

    @Nullable public final String getDescriptionId()
    {
        return this.descriptionId;
    }

}
