package vsdum.kex.natives;

import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;
import vsdum.kex.modules.states.BlockState;
import vsdum.kex.modules.tileentity.BlockActor;
import vsdum.kex.modules.tileentity.TileEntityData;
import vsdum.kex.modules.tileentity.TileEntityNativeAPI;
import vsdum.kex.util.mcmath.BlockPos;

public class ExtendedBlockSource extends NativeBlockSource implements INativeInterface {

    protected static native long nativeGetLevel(long ptr);
    protected static native long nativeGetDimension(long ptr);
    protected static native long nativeGetBlockState(long ptr, int x, int y, int z);
    protected static native boolean nativeSetBlockState(long ptr, int x, int y, int z, int runtimeID, int flags);
    protected static native boolean nativeSetBlockStateNoUpdate(long ptr, int x, int y, int z, int runtimeID);
    protected static native int nativeGetBiome(long ptr, int x, int z);
    protected static native int nativeGetBiomeFast(long ptr, int x, int z);
    
    protected final long pointer;

    @Override public final long getPointer()
    {
        return this.pointer;
    }

    public ExtendedBlockSource(NativeBlockSource icObj)
    {
        super(icObj.getPointer(), false);
        this.pointer = icObj.getPointer();
    }

    public ExtendedBlockSource(long ptr)
    {
        super(ptr, false);
        this.pointer = ptr;
    }

    public static ExtendedBlockSource toKEXBlockSource(NativeBlockSource icObj)
    {
        return icObj instanceof ExtendedBlockSource ? (ExtendedBlockSource) icObj : new ExtendedBlockSource(icObj);
    }

    @Nullable public static ExtendedBlockSource getCurrentClientRegion()
    {
        NativeBlockSource icObj = NativeBlockSource.getCurrentClientRegion();
        return icObj == null ? null : new ExtendedBlockSource(icObj);
    }

    @Nullable public static ExtendedBlockSource getCurrentWorldGenRegion()
    {
        NativeBlockSource icObj = NativeBlockSource.getCurrentWorldGenRegion();
        return icObj == null ? null : new ExtendedBlockSource(icObj);
    }

    @Nullable public static ExtendedBlockSource getDefaultForActor(Actor entity)
    {
        return getDefaultForActor(entity.getUniqueID());
    }

    @Nullable public static ExtendedBlockSource getDefaultForActor(long entityUID)
    {
        NativeBlockSource icObj = NativeBlockSource.getDefaultForActor(entityUID);
        return icObj == null ? null : new ExtendedBlockSource(icObj);
    }

    @Nullable public static ExtendedBlockSource getDefaultForDimension(int dimensionId)
    {
        NativeBlockSource icObj = NativeBlockSource.getDefaultForDimension(dimensionId);
        return icObj == null ? null : new ExtendedBlockSource(icObj);
    }

    @Nullable public Level getLevel()
    {
        long ptr = nativeGetLevel(this.pointer);
        return ptr == 0L ? null : new Level(ptr);
    }
    
    @Nullable public Dimension getDimensionObject()
    {
        long ptr = nativeGetDimension(this.pointer);
        return ptr == 0L ? null : new Dimension(ptr);
    }

    @Nullable public BlockActor getCustomBlockEntity(BlockPos pos)
    {
        return this.getCustomBlockEntity(pos.x, pos.y, pos.z);
    }

    @Nullable public BlockActor getCustomBlockEntity(int x, int y, int z)
    {
        long ptr = TileEntityNativeAPI.get(this.pointer, x, y, z);
        if(ptr == 0L || !TileEntityData.customTileEntityMap.containsKey(ptr)) return null;
        return TileEntityData.customTileEntityMap.get(ptr);
    }

    @Nullable public BlockState getBlockState(BlockPos pos)
    {
        return this.getBlockState(pos.x, pos.y, pos.z);
    }

    @Nullable public BlockState getBlockState(int x, int y, int z)
    {
        long blockLong = nativeGetBlockState(this.pointer, x, y, z);
        return blockLong == 0L ? null : new BlockState(blockLong);
    }

    public boolean setBlockState(int x, int y, int z, BlockState state, int flags)
    {
        return nativeSetBlockState(this.pointer, x, y, z, state.getRuntimeID(), flags);
    }

    public boolean setBlockStateNoUpdate(int x, int y, int z, BlockState state)
    {
        return nativeSetBlockStateNoUpdate(this.pointer, x, y, z, state.getRuntimeID());
    }

    @Override public int getBiome(int x, int z)
    {
        return nativeGetBiome(this.pointer, x, z);
    }

    public int getBiomeFast(int x, int z)
    {
        return nativeGetBiomeFast(this.pointer, x, z);
    }

}
