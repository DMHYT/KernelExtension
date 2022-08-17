package vsdum.kex.natives;

import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;
import vsdum.kex.modules.tileentity.BlockActor;
import vsdum.kex.modules.tileentity.TileEntityData;
import vsdum.kex.modules.tileentity.TileEntityNativeAPI;
import vsdum.kex.util.mcmath.BlockPos;

public class ExtendedBlockSource extends NativeBlockSource implements INativeInterface {

    protected static native long nativeGetLevel(long ptr);
    protected static native long nativeGetDimension(long ptr);
    
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
        long ptr = TileEntityNativeAPI.get(this.pointer, pos.x, pos.y, pos.z);
        if(ptr == 0L || !TileEntityData.customTileEntityMap.containsKey(ptr)) return null;
        return TileEntityData.customTileEntityMap.get(ptr);
    }

}
