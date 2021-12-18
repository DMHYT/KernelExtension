package vsdum.kex.natives;

import vsdum.kex.common.INativeInterface;

public class MobEffectInstance implements INativeInterface {
    


    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public MobEffectInstance(long ptr)
    {
        this.pointer = ptr;
    }

}
