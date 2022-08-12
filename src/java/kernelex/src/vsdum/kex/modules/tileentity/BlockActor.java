package vsdum.kex.modules.tileentity;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.innercore.api.nbt.NativeCompoundTag;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.natives.Player;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Vec3d;

public abstract class BlockActor implements INativeInterface {
    
    protected final long pointer;
    private final int type;
    private BlockPos blockPos;
    private int dimension = -1;

    public final long getPointer()
    {
        return this.pointer;
    }

    public BlockActor(long ptr, int type, BlockPos blockPos, int dimension)
    {
        this.pointer = ptr;
        this.type = type;
        this.blockPos = blockPos;
        this.dimension = dimension;
    }

    public BlockPos getBlockPos()
    {
        return this.blockPos;
    }

    public BlockActor updateBlockPos()
    {
        int[] pos = TileEntityNativeAPI.getPosition(this.pointer);
        this.blockPos = new BlockPos(pos[0], pos[1], pos[2]);
        return this;
    }

    public BlockState getBlockState()
    {
        return this.hasWorld() ? this.getWorld().getBlock(this.blockPos.x, this.blockPos.y, this.blockPos.z) : null;
    }

    @Nullable public ExtendedBlockSource getWorld()
    {
        return this.hasWorld() ? ExtendedBlockSource.getDefaultForDimension(this.dimension) : null;
    }
    
    public boolean hasWorld()
    {
        return this.dimension != -1;
    }

    public int getType()
    {
        return this.type;
    }

    public boolean isClient()
    {
        return this.hasWorld() ? this.getWorld().getLevel().isClientSide() : true;
    }

    public boolean isServer()
    {
        return !this.isClient();
    }

    public void loadDimension(NativeCompoundTag data)
    {
        this.dimension = data.contains("Dimension") ? data.getInt("Dimension") : -1;
    }
    
    public void saveDimension(NativeCompoundTag data)
    {
        data.putInt("Dimension", this.dimension);
    }

    public void load(NativeCompoundTag data, boolean fromNative)
    {
        if(fromNative) load(data);
        else TileEntityNativeAPI.load(this.pointer, data.pointer);
    }

    protected abstract void load(NativeCompoundTag data);

    public boolean save(NativeCompoundTag data, boolean fromNative)
    {
        return fromNative ? save(data) : TileEntityNativeAPI.save(this.pointer, data.pointer);
    }

    protected abstract boolean save(NativeCompoundTag data);

    public void tick() {}

    public boolean isFinished()
    {
        return false;
    }

    public void onChanged() {}

    public boolean isMovable()
    {
        return true;
    }

    public void onPlace() {}

    public void onMove() {}

    public void onRemoved() {}

    public void triggerEvent(int id, int type) {}

    public void onNeighborChanged(BlockPos changed) {}

    @Nullable public String getCustomName()
    {
        return null;
    }

    public void setCustomName(String customName) {}

    @Nullable public String getName()
    {
        return null;
    }

    public void onChunkLoaded() {}

    public void onChunkUnloaded() {}

    public boolean onUse(Player player, byte side, Vec3d vec)
    {
        return false;
    }

}
