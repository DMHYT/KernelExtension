package vsdum.kex.modules;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.innercore.api.NativeBlock;
import com.zhekasmirnov.innercore.api.commontypes.Coords;

import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Direction;

public class BlocksModule {

    protected static native void nativeEnableComparatorSignalCallback(int id, boolean isCallbackForced);
    protected static native void nativeEnableDynamicLightEmission(int id);
    protected static native void nativeSetLightEmission(int id, int data, byte lightLevel);
    protected static native byte nativeGetLightEmission(int id, int data);

    public static interface ComparatorSignalCallback {
        public int getComparatorSignal(BlockState block, ExtendedBlockSource world, BlockPos pos, Direction side);
    }

    public static interface ComparatorSignalCallbackJS {
        public int getComparatorSignal(BlockState block, ExtendedBlockSource world, Coords coords);
    }

    private static final Map<Integer, ComparatorSignalCallback> comparatorSignalCallbacks = new HashMap<>();
    private static final Set<Integer> dynamicLightBlocks = new HashSet<>();

    public static void registerComparatorSignalCallback(int id, ComparatorSignalCallback callback)
    {
        registerComparatorSignalCallback(id, callback, false);
    }

    public static void registerComparatorSignalCallback(int id, ComparatorSignalCallback callback, boolean isCallbackForced)
    {
        nativeEnableComparatorSignalCallback(id, isCallbackForced);
        comparatorSignalCallbacks.put(id, callback);
    }

    public static void registerComparatorSignalCallbackJS(int id, ComparatorSignalCallbackJS callback)
    {
        registerComparatorSignalCallbackJS(id, callback, false);
    }

    public static void registerComparatorSignalCallbackJS(int id, ComparatorSignalCallbackJS callback, boolean isCallbackForced)
    {
        registerComparatorSignalCallback(id, (block, world, pos, side) -> callback.getComparatorSignal(block, world, new Coords(pos.x, pos.y, pos.z, side.getIndex())), isCallbackForced);
    }

    public static void setLightEmission(int id, int data, byte lightLevel)
    {
        nativeEnableDynamicLightEmission(id);
        dynamicLightBlocks.add(id);
        nativeSetLightEmission(id, data, lightLevel);
    }

    public static byte getLightEmission(int id, int data)
    {
        if(dynamicLightBlocks.contains(id)) return nativeGetLightEmission(id, data);
        return (byte) NativeBlock.getLightLevel(id);
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
