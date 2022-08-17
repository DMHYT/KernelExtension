package vsdum.kex.modules.tileentity;

import java.util.Optional;

import com.zhekasmirnov.innercore.api.nbt.NativeCompoundTag;

import android.support.annotation.Nullable;
import vsdum.kex.natives.Player;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Vec3d;

@SuppressWarnings("unused")
public class TileEntityEvents {

    private static void construct(long tilePtr)
    {
        TileEntityData.getOrCreate(tilePtr);
    }
    
    private static void load(long tilePtr, long tagPtr)
    {
        BlockActor tile = TileEntityData.getOrCreate(tilePtr);
        NativeCompoundTag tag = new NativeCompoundTag(tagPtr).setFinalizable(false);
        tile.load(tag, true);
    }

    private static boolean save(long tilePtr, long tagPtr)
    {
        BlockActor tile = TileEntityData.getOrCreate(tilePtr);
        NativeCompoundTag tag = new NativeCompoundTag(tagPtr).setFinalizable(false);
        return tile.save(tag, true);
    }

    private static void tick(long tilePtr)
    {
        TileEntityData.getOrCreate(tilePtr).tick();
    }

    private static boolean isFinished(long tilePtr)
    {
        return TileEntityData.getOrCreate(tilePtr).isFinished();
    }

    private static void onChanged(long tilePtr)
    {
        TileEntityData.getOrCreate(tilePtr).onChanged();
    }

    private static boolean isMovable(long tilePtr)
    {
        return TileEntityData.getOrCreate(tilePtr).isMovable();
    }

    private static void onPlace(long tilePtr)
    {
        TileEntityData.getOrCreate(tilePtr).onPlace();
    }

    private static void onMove(long tilePtr)
    {
        TileEntityData.getOrCreate(tilePtr).updateBlockPos().onMove();
    }

    private static void onRemoved(long tilePtr)
    {
        BlockActor tile = TileEntityData.getOrCreate(tilePtr);
        TileEntityData.customTileEntityMap.remove(tile.getPointer());
        tile.onRemoved();
        tile.removeNetworkData();
    }

    private static void triggerEvent(long tilePtr, int id, int type)
    {
        TileEntityData.getOrCreate(tilePtr).triggerEvent(id, type);
    }

    private static void onNeighborChanged(long tilePtr, int changedX, int changedY, int changedZ)
    {
        TileEntityData.getOrCreate(tilePtr).onNeighborChanged(new BlockPos(changedX, changedY, changedZ));
    }

    @Nullable private static String getCustomName(long tilePtr)
    {
        return TileEntityData.getOrCreate(tilePtr).getCustomName();
    }

    @Nullable private static String getName(long tilePtr)
    {
        return TileEntityData.getOrCreate(tilePtr).getName();
    }

    private static void setCustomName(long tilePtr, String customName)
    {
        TileEntityData.getOrCreate(tilePtr).setCustomName(customName);
    }

    private static void onChunkLoaded(long tilePtr)
    {
        TileEntityData.getOrCreate(tilePtr).onChunkLoaded();
    }

    private static void onChunkUnloaded(long tilePtr)
    {
        TileEntityData.getOrCreate(tilePtr).onChunkUnloaded();
    }

    private static boolean onUse(long tilePtr, long playerUid, byte side, float vecX, float vecY, float vecZ)
    {
        return TileEntityData.getOrCreate(tilePtr).onUse(new Player(playerUid), side, new Vec3d(vecX, vecY, vecZ));
    }

    private static void reportTileSideAndDimension(long tilePtr, boolean client, int dimension)
    {
        TileEntityData.getOrCreate(tilePtr).initNetwork(dimension, client);
    }

}
