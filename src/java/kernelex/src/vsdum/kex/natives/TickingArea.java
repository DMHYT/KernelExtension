package vsdum.kex.natives;

import vsdum.kex.common.INativeInterface;

public class TickingArea implements INativeInterface {
    


    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public TickingArea(long ptr)
    {
        this.pointer = ptr;
    }

}
