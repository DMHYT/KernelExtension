package vsdum.kex.natives;

import android.support.annotation.Nullable;

public class LocalPlayer extends Player {
    
    protected static native long nativeGetMoveInputHandler(long ptr);
    protected static native boolean nativeIsFlying(long ptr);

    public LocalPlayer(long entity)
    {
        super(entity);
        if(!this.isLocalPlayer())
            throw new IllegalArgumentException("The given entity is not a LocalPlayer! Consider using Actor.asLocalPlayer() in order not to get exceptions thrown!");
    }

    protected LocalPlayer(long ptr, boolean flag)
    {
        super(ptr, flag);
    }

    public LocalPlayer(Player player)
    {
        this(player.pointer, true);
        if(!this.isLocalPlayer())
            throw new IllegalArgumentException("The given Player is not a LocalPlayer! Consider using Player.asLocalPlayer() in order not to get exceptions thrown!");
    }

    public LocalPlayer(Mob mob)
    {
        this(mob.pointer, true);
        if(!this.isLocalPlayer())
            throw new IllegalArgumentException("The given Mob is not a LocalPlayer! Consider using Mob.asLocalPlayer() in order not to get exceptions thrown!");
    }

    public LocalPlayer(Actor actor)
    {
        this(actor.pointer, true);
        if(!this.isLocalPlayer())
            throw new IllegalArgumentException("The given Actor is not a nullptr! Consider using Actor.asLocalPlayer() in order not to get exceptions thrown!");
    }

    @Nullable public MoveInputHandler getMoveInputHandler()
    {
        long handlerPtr = nativeGetMoveInputHandler(this.pointer);
        if(handlerPtr == 0L) return null;
        return new MoveInputHandler(handlerPtr);
    }

    public boolean isFlying()
    {
        return nativeIsFlying(this.pointer);
    }

}
