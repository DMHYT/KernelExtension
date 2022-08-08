package vsdum.kex.modules.tileentity;

import java.util.List;
import java.util.Objects;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.innercore.api.nbt.NativeCompoundTag;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public abstract class BlockActor implements INativeInterface {
    
    protected final long pointer;
    private final int type;
    private BlockPos blockPos;
    @Nullable private ExtendedBlockSource world = null;

    public final long getPointer()
    {
        return this.pointer;
    }

    public BlockActor(long ptr, int type, BlockPos blockPos)
    {
        this.pointer = ptr;
        this.type = type;
        this.blockPos = blockPos;
    }

    public BlockPos getBlockPos()
    {
        return this.blockPos;
    }

    public BlockState getBlockState()
    {
        return this.world.getBlock(this.blockPos.x, this.blockPos.y, this.blockPos.z);
    }

    public boolean hasWorld()
    {
        return this.world != null;
    }

    @Nullable public ExtendedBlockSource getWorld()
    {
        return this.world;
    }

    public void setWorld(ExtendedBlockSource world)
    {
        this.world = Objects.requireNonNull(world);
    }

    public int getType()
    {
        return this.type;
    }

    public void load(NativeCompoundTag data) {}

    public boolean save(NativeCompoundTag data)
    {
        return true;
    }

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

    public float getShadowRadius()
    {
        return 0.0f;
    }

    public void getDebugText(List<String> text, BlockPos pos) {}

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

}
