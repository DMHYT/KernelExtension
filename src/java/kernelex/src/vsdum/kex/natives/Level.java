package vsdum.kex.natives;

import vsdum.kex.common.INativeInterface;

public class Level implements INativeInterface {
    


    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public Level(long pointer)
    {
        this.pointer = pointer;
    }

}
