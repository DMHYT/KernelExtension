package vsdum.kex.natives;

public class Slime extends Mob {
    
    protected static native float nativeDecreaseSquish(long ptr);
    protected static native boolean nativeJustJumped(long ptr);
    protected static native boolean nativeJustLanded(long ptr);
    protected static native int nativeGetSquishValue(long ptr);
    protected static native int nativeGetOldSquishValue(long ptr);
    protected static native int nativeGetTargetSquish(long ptr);
    protected static native int nativeGetSlimeSize(long ptr);
    protected static native void nativeSetSlimeSize(long ptr, int size);

    public Slime(long entity)
    {
        super(entity);
        if(!this.isSlime())
            throw new IllegalArgumentException("The given entity is not a Slime! Consider using Mob.asSlime() in order not to get exceptions thrown!");
    }

    protected Slime(long ptr, boolean flag)
    {
        super(ptr, flag);
    }

    public Slime(Mob mob)
    {
        this(mob.pointer, true);
        if(!this.isSlime())
            throw new IllegalArgumentException("The given Mob is not a Slime! Consider using Mob.asSlime() in order not to get exceptions thrown!");
    }

    public Slime(Actor actor)
    {
        this(actor.pointer, true);
        if(!this.isMob())
            throw new IllegalArgumentException("The given Actor is not a Mob, and logically, cannot be converted to Slime! Consider using Actor.asMob() and Mob.asSlime() in order not to get exceptions thrown!");
        if(!this.isSlime())
            throw new IllegalArgumentException("The given Actor is not a Slime! Consider using Actor.asMob() and Mob.asSlime() in order not to get exceptions thrown!");
    }

    public float decreaseSquish()
    {
        return nativeDecreaseSquish(this.pointer);
    }

    public boolean justJumped()
    {
        return nativeJustJumped(this.pointer);
    }

    public boolean justLanded()
    {
        return nativeJustLanded(this.pointer);
    }

    public int getSquishValue()
    {
        return nativeGetSquishValue(this.pointer);
    }

    public int getOldSquishValue()
    {
        return nativeGetOldSquishValue(this.pointer);
    }

    public int getTargetSquish()
    {
        return nativeGetTargetSquish(this.pointer);
    }

    public int getSlimeSize()
    {
        return nativeGetSlimeSize(this.pointer);
    }
    
    public void setSlimeSize(int size)
    {
        nativeSetSlimeSize(this.pointer, size);
    }

}
