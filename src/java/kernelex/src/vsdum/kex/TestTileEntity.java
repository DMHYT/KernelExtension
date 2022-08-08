package vsdum.kex;

import com.zhekasmirnov.innercore.api.NativeAPI;

import vsdum.kex.modules.tileentity.BlockActor;
import vsdum.kex.util.mcmath.BlockPos;

public class TestTileEntity extends BlockActor {
    
    public TestTileEntity(long ptr, int type, BlockPos pos)
    {
        super(ptr, type, pos);
    }

    @Override public void tick()
    {
        if(Math.random() <= .1) NativeAPI.clientMessage("TICK");
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

    @Override public float getShadowRadius()
    {
        NativeAPI.clientMessage("CALLED GETSHADOWRADIUS");
        return 0.0f;
    }

    @Override public void onChunkLoaded()
    {
        NativeAPI.clientMessage("CHUNK LOADED");
    }

    @Override public void onChunkUnloaded()
    {
        NativeAPI.clientMessage("CHUNK UNLOADED");
    }

}
