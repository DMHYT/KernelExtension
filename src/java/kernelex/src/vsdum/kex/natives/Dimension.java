package vsdum.kex.natives;

import vsdum.kex.common.INativeInterface;

public class Dimension implements INativeInterface {
    
    

    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public Dimension(long pointer)
    {
        this.pointer = pointer;
    }

}
