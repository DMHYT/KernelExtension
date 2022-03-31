package vsdum.kex.natives;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;

public class LootTableContext implements INativeInterface {

    private static native long nativeGetThisEntity(long ptr);
    @Nullable private static native String nativeGetOriginalItemName(long ptr);
    private static native long nativeGetLevel(long ptr);
    private static native float nativeGetExplosionRadius(long ptr);
    private static native float nativeGetLuck(long ptr);
    private static native long nativeGetKillerPlayer(long ptr);
    private static native long nativeGetKillerPet(long ptr);
    private static native long nativeGetKillerEntity(long ptr);
    private static native void nativeSetOriginalItemName(long ptr, String name);
    private static native long nativeBuilderConstruct(long levelPtr);
    private static native void nativeBuilderExplosionRadius(long ptr, float radius);
    private static native void nativeBuilderThisEntity(long ptr, long actorPtr);
    private static native void nativeBuilderLuck(long ptr, float luck);
    private static native void nativeBuilderItemName(long ptr, String name);
    private static native void nativeBuilderKillerPlayer(long ptr, long playerPtr);
    private static native long nativeBuilderCreate(long ptr);
    
    private final long pointer;
    @Nullable private final Actor thisEntity;
    @Nullable private String originalItemName;
    @Nullable private final Level level;
    private final float explosionRadius;
    private final float luck;
    @Nullable private final Player killerPlayer;
    @Nullable private final Actor killerPet;
    @Nullable private final Actor killerEntity;

    public final long getPointer()
    {
        return this.pointer;
    }

    public LootTableContext(long ptr)
    {
        this.pointer = ptr;
        long thisEntityPtr = nativeGetThisEntity(this.pointer);
        this.thisEntity = thisEntityPtr == 0L ? null : new Actor(thisEntityPtr, true);
        this.originalItemName = nativeGetOriginalItemName(this.pointer);
        long levelPtr = nativeGetLevel(this.pointer);
        this.level = levelPtr == 0L ? null : new Level(levelPtr);
        this.explosionRadius = nativeGetExplosionRadius(this.pointer);
        this.luck = nativeGetLuck(this.pointer);
        long killerPlayerPtr = nativeGetKillerPlayer(this.pointer);
        this.killerPlayer = killerPlayerPtr == 0L ? null : new Player(killerPlayerPtr, true);
        long killerPetPtr = nativeGetKillerPet(this.pointer);
        this.killerPet = killerPetPtr == 0L ? null : new Actor(killerPetPtr, true);
        long killerEntityPtr = nativeGetKillerEntity(this.pointer);
        this.killerEntity = killerEntityPtr == 0L ? null : new Actor(killerEntityPtr, true);
    }

    @Nullable public final Actor getThisEntity()
    {
        return this.thisEntity;
    }

    @Nullable public String getOriginalItemName()
    {
        return this.originalItemName;
    }

    public void setOriginalItemName(String name)
    {
        nativeSetOriginalItemName(this.pointer, name);
        this.originalItemName = name;
    }

    @Nullable public final Level getLevel()
    {
        return this.level;
    }

    public final float getExplosionRadius()
    {
        return this.explosionRadius;
    }

    public final float getLuck()
    {
        return this.luck;
    }

    @Nullable public final Player getKillerPlayer()
    {
        return this.killerPlayer;
    }

    @Nullable public final Actor getKillerPet()
    {
        return this.killerPet;
    }

    @Nullable public final Actor getKillerEntity()
    {
        return this.killerEntity;
    }

    public static class Builder implements INativeInterface {

        private final long pointer;
        
        public final long getPointer()
        {
            return this.pointer;
        }

        public Builder(Level level)
        {
            this.pointer = nativeBuilderConstruct(level.getPointer());
        }

        public Builder withExplosionRadius(float radius)
        {
            nativeBuilderExplosionRadius(this.pointer, radius);
            return this;
        }

        public Builder withThisEntity(Actor entity)
        {
            nativeBuilderThisEntity(this.pointer, entity.getPointer());
            return this;
        }

        public Builder withLuck(float luck)
        {
            nativeBuilderLuck(this.pointer, luck);
            return this;
        }

        public Builder withOriginalItemName(String name)
        {
            nativeBuilderItemName(this.pointer, name);
            return this;
        }

        public Builder withKillerPlayer(Player player)
        {
            nativeBuilderKillerPlayer(this.pointer, player.getPointer());
            return this;
        }

        @Nullable public LootTableContext create()
        {
            long ctxPtr = nativeBuilderCreate(this.pointer);
            return ctxPtr == 0L ? null : new LootTableContext(ctxPtr);
        }

    }
    
}
