package vsdum.kex.natives;

import vsdum.kex.common.INativeInterface;

public class ItemStack implements INativeInterface {
    


    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public ItemStack(long ptr)
    {
        this.pointer = ptr;
    }

}
