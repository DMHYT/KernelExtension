package vsdum.kex;

import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.nbt.NativeCompoundTag;

import vsdum.kex.modules.tileentity.BlockActor;
import vsdum.kex.natives.Player;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Vec3d;

public class TestTileEntity extends BlockActor {

    private int testValue = 0;
    
    public TestTileEntity(long ptr, int type, BlockPos pos, int dimension)
    {
        super(ptr, type, pos, dimension);
    }

    @Override public void tick()
    {
        if(Math.random() <= .01) NativeAPI.clientMessage("TICK");
    }

    @Override public void onChanged()
    {
        NativeAPI.clientMessage("CALLED ONCHANGED");
    }

    @Override public void onPlace()
    {
        NativeAPI.clientMessage("PLACED");
    }

    @Override public void onRemoved()
    {
        NativeAPI.clientMessage("REMOVED");
    }

    @Override public void triggerEvent(int id, int type)
    {
        NativeAPI.clientMessage(String.format("EVENT{id=%d,type=%d}", new Object[]{ Integer.valueOf(id), Integer.valueOf(type) }));
    }

    @Override public void onNeighborChanged(BlockPos changed)
    {
        NativeAPI.clientMessage("NEIGHBOR CHANGED ON " + changed.toString());
    }

    @Override public void onChunkLoaded()
    {
        NativeAPI.clientMessage("CHUNK LOADED");
    }

    @Override public void onChunkUnloaded()
    {
        NativeAPI.clientMessage("CHUNK UNLOADED");
    }

    @Override public boolean onUse(Player player, byte side, Vec3d vec)
    {
        NativeAPI.clientMessage(String.format("Clicked on side %d with exact coords %s", new Object[]{ Byte.valueOf(side), vec.toString() }));
        return true;
    }

    @Override protected void load(NativeCompoundTag tag)
    {
        this.testValue = tag.contains("testValue") ? tag.getInt("testValue") : 0;
    }

    @Override protected boolean save(NativeCompoundTag tag)
    {
        tag.putInt("testValue", this.testValue);
        return true;
    }

}
