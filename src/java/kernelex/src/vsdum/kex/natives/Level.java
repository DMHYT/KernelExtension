package vsdum.kex.natives;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;

public class Level implements INativeInterface {
    
    protected static native long nativeGetTickingAreasManager(long ptr);
    protected static native boolean nativeIsClientSide(long ptr);

    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public Level(long pointer)
    {
        this.pointer = pointer;
    }

    @Nullable public TickingAreasManager getTickingAreasManager()
    {
        long ptr = nativeGetTickingAreasManager(this.pointer);
        return ptr == 0L ? null : new TickingAreasManager(ptr);
    }

    public boolean isClientSide()
    {
        return nativeIsClientSide(this.pointer);
    }

}
