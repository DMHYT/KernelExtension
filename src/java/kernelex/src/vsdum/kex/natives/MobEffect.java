package vsdum.kex.natives;

import vsdum.kex.common.INativeInterface;

public class MobEffect implements INativeInterface {
    

    
    protected final long pointer;
    
    public final long getPointer()
    {
        return this.pointer;
    }

    public MobEffect(long ptr)
    {
        this.pointer = ptr;
    }

}
