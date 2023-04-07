package vsdum.kex.modules;

import java.util.HashMap;
import java.util.Map;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.innercore.api.commontypes.Coords;

import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Direction;

public class BlocksModule {

    protected static native void nativeEnableComparatorSignalCallback(int id);

    public static interface ComparatorSignalCallback {
        public int getComparatorSignal(BlockState block, ExtendedBlockSource world, BlockPos pos, Direction side);
    }

    public static interface ComparatorSignalCallbackJS {
        public int getComparatorSignal(BlockState block, ExtendedBlockSource world, Coords coords);
    }

    private static final Map<Integer, ComparatorSignalCallback> comparatorSignalCallbacks = new HashMap<>();

    public static void registerComparatorSignalCallback(int id, ComparatorSignalCallback callback)
    {
        nativeEnableComparatorSignalCallback(id);
        comparatorSignalCallbacks.put(id, callback);
    }

    public static void registerComparatorSignalCallbackJS(int id, ComparatorSignalCallbackJS callback)
    {
        registerComparatorSignalCallback(id, (block, world, pos, side) -> callback.getComparatorSignal(block, world, new Coords(pos.x, pos.y, pos.z, side.getIndex())));
    }

    public static int getComparatorSignal(long blockLong, long blockSourcePtr, int x, int y, int z, int side)
    {
        BlockState state = new BlockState(blockLong);
        if(comparatorSignalCallbacks.containsKey(state.id))
        {
            return comparatorSignalCallbacks.get(state.id).getComparatorSignal(state, new ExtendedBlockSource(blockSourcePtr), new BlockPos(x, y, z), Direction.VALUES[side]);
        }
        return 0;
    }
    
}
