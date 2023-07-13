package vsdum.kex.japi.blocks;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.NativeItemInstanceExtra;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import vsdum.kex.japi.blocks.components.*;
import vsdum.kex.modules.states.BlockState;
import vsdum.kex.natives.Actor;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.natives.Player;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Direction;
import vsdum.kex.util.mcmath.Vec3d;

public class BlockEvents {

    static final Map<Integer, IUsable> onUseEvents = new HashMap<>();
    static final Map<Integer, IHasDrops> getDropsEvents = new HashMap<>();
    static final Map<Integer, IEntityInsideListener> entityInsideEvents = new HashMap<>();
    static final Map<Integer, INeighborChangeListener> neighborChangedEvents = new HashMap<>();
    static final Map<Integer, ICustomPlaceBehavior> onPlaceEvents = new HashMap<>();
    static final Map<Integer, IExplosionListener> popResourcesEvents = new HashMap<>();

    public static void onUse(int id, int data, int dimension, int x, int y, int z, long player, int side, float vx, float vy, float vz)
    {
        if(onUseEvents.containsKey(id))
        {
            onUseEvents.get(id).onUse(new BlockState(id, data), ExtendedBlockSource.getDefaultForDimension(dimension), new BlockPos(x, y, z), new Player(player), Direction.VALUES[side], new Vec3d(vx, vy, vz));
        }
    }

    @NonNull public static List<ItemStack> getDrops(int blockID, int blockData, int dimension, int id, int count, int data, @Nullable NativeItemInstanceExtra extra, int x, int y, int z)
    {
        return getDropsEvents.containsKey(blockID) ?
            Objects.requireNonNull(getDropsEvents.get(blockID).getDrops(new BlockState(blockID, blockData), new BlockPos(x, y, z), ExtendedBlockSource.getDefaultForDimension(dimension), new ItemStack(id, count, data, extra)), "List of items dropped from a block must be non-null!") :
            new ArrayList<>();
    }

    public static void entityInside(int id, int data, int dimension, int x, int y, int z, long entity)
    {
        if(entityInsideEvents.containsKey(id))
        {
            entityInsideEvents.get(id).entityInside(new BlockState(id, data), ExtendedBlockSource.getDefaultForDimension(dimension), new BlockPos(x, y, z), new Actor(entity));
        }
    }

    public static void neighborChanged(int id, int data, int dimension, int x, int y, int z, int cx, int cy, int cz)
    {
        if(neighborChangedEvents.containsKey(id))
        {
            neighborChangedEvents.get(id).neighborChanged(new BlockState(id, data), ExtendedBlockSource.getDefaultForDimension(dimension), new BlockPos(x, y, z), new BlockPos(cx, cy, cz));
        }
    }

    public static void onPlace(int x, int y, int z, int id, int count, int data, @Nullable NativeItemInstanceExtra extra, int touchedID, int touchedData, long player, int dimension, int blockID)
    {
        if(onPlaceEvents.containsKey(blockID))
        {
            onPlaceEvents.get(blockID).onPlace(new BlockPos(x, y, z), new ItemStack(id, count, data, extra), new BlockState(touchedID, touchedData), new Player(player), ExtendedBlockSource.getDefaultForDimension(dimension));
        }
    }

    public static void popResources(int x, int y, int z, int dimension, int id, int data)
    {
        if(popResourcesEvents.containsKey(id))
        {
            popResourcesEvents.get(id).popResources(new BlockPos(x, y, z), ExtendedBlockSource.getDefaultForDimension(dimension), new BlockState(id, data));
        }
    }
    
}
