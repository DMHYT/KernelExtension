package vsdum.kex.natives;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;
import vsdum.kex.modules.states.BlockState;

public class ActorDamageSource implements INativeInterface {

    protected static native boolean nativeIsEntitySource(long ptr);
    protected static native boolean nativeIsChildEntitySource(long ptr);
    protected static native boolean nativeIsBlockSource(long ptr);
    protected static native boolean nativeIsCreative(long ptr);
    protected static native boolean nativeIsWorldBuilder(long ptr);
    protected static native long nativeGetEntityUniqueID(long ptr);
    protected static native int nativeGetEntityType(long ptr);
    protected static native int nativeGetEntityCategories(long ptr);
    protected static native boolean nativeIsDamagingEntityCreative(long ptr);
    protected static native boolean nativeIsDamagingEntityWorldBuilder(long ptr);
    protected static native long nativeGetDamagingEntityUniqueID(long ptr);
    protected static native int nativeGetDamagingEntityType(long ptr);
    protected static native int nativeGetDamagingEntityCategories(long ptr);
    protected static native int nativeGetCause(long ptr);
    protected static native void nativeSetCause(long ptr, int cause);
    protected static native long nativeGetBlock(long ptr);
    
    protected final long pointer;

    private final boolean entitySource;
    private final boolean childEntitySource;
    private final boolean blockSource;
    private final boolean entityIsCreative;
    private final boolean entityIsWorldBuilder;
    private final long entityUniqueID;
    private final int entityType;
    private final int entityCategories;
    @Nullable private final Actor entity;
    private final boolean damagingEntityIsCreative;
    private final boolean damagingEntityIsWorldBuilder;
    private final long damagingEntityUniqueID;
    private final int damagingEntityType;
    private final int damagingEntityCategories;
    @Nullable private final Actor damagingEntity;
    @Nullable private final BlockState block;

    public final long getPointer()
    {
        return this.pointer;
    }

    public ActorDamageSource(long ptr)
    {
        this.pointer = ptr;
        this.entitySource = nativeIsEntitySource(this.pointer);
        this.childEntitySource = nativeIsChildEntitySource(this.pointer);
        this.blockSource = nativeIsBlockSource(this.pointer);
        this.entityIsCreative = nativeIsCreative(this.pointer);
        this.entityIsWorldBuilder = nativeIsWorldBuilder(this.pointer);
        this.entityUniqueID = nativeGetEntityUniqueID(this.pointer);
        this.entityType = nativeGetEntityType(this.pointer);
        this.entityCategories = nativeGetEntityCategories(this.pointer);
        this.entity = this.entityUniqueID == -1L ? null : new Actor(this.entityUniqueID);
        this.damagingEntityIsCreative = nativeIsDamagingEntityCreative(this.pointer);
        this.damagingEntityIsWorldBuilder = nativeIsDamagingEntityWorldBuilder(this.pointer);
        this.damagingEntityUniqueID = nativeGetDamagingEntityUniqueID(this.pointer);
        this.damagingEntityType = nativeGetDamagingEntityType(this.pointer);
        this.damagingEntityCategories = nativeGetDamagingEntityCategories(this.pointer);
        this.damagingEntity = this.damagingEntityUniqueID == -1L ? null : new Actor(this.damagingEntityUniqueID);
        long blockLong = this.blockSource ? nativeGetBlock(this.pointer) : 0L;
        this.block = blockLong == 0L ? null : new BlockState(blockLong);
    }

    public final boolean isEntitySource()
    {
        return this.entitySource;
    }

    public final boolean isChildEntitySource()
    {
        return this.childEntitySource;
    }

    public final boolean isBlockSource()
    {
        return this.blockSource;
    }

    public final boolean isEntityCreative()
    {
        return this.entityIsCreative;
    }

    public final boolean isEntityWorldBuilder()
    {
        return this.entityIsWorldBuilder;
    }

    public final long getEntityUniqueID()
    {
        return this.entityUniqueID;
    }

    public final int getEntityType()
    {
        return this.entityType;
    }

    public final int getEntityCategories()
    {
        return this.entityCategories;
    }

    @Nullable public final Actor getEntity()
    {
        return this.entity;
    }

    public final boolean isDamagingEntityCreative()
    {
        return this.damagingEntityIsCreative;
    }

    public final boolean isDamagingEntityWorldBuilder()
    {
        return this.damagingEntityIsWorldBuilder;
    }

    public final long getDamagingEntityUniqueID()
    {
        return this.damagingEntityUniqueID;
    }

    public final int getDamagingEntityType()
    {
        return this.damagingEntityType;
    }

    public final int getDamagingEntityCategories()
    {
        return this.damagingEntityCategories;
    }

    @Nullable public final Actor getDamagingEntity()
    {
        return this.damagingEntity;
    }

    public final int getCause()
    {
        return nativeGetCause(this.pointer);
    }

    public void setCause(int cause)
    {
        nativeSetCause(this.pointer, cause);
    }

    @Nullable public final BlockState getBlock()
    {
        return this.block;
    }

}
