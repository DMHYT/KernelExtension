package vsdum.kex.natives;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;

public class Dimension implements INativeInterface {
    
    protected static native int nativeGetDimensionId(long ptr);
    protected static native long nativeGetLevel(long ptr);    

    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public Dimension(long pointer)
    {
        this.pointer = pointer;
    }

    public int getDimensionId()
    {
        return nativeGetDimensionId(this.pointer);
    }

    @Nullable public Level getLevel()
    {
        long levelPtr = nativeGetLevel(this.pointer);
        return levelPtr == 0L ? null : new Level(levelPtr);
    }

}
