package vsdum.kex.japi.items;

import java.util.HashMap;
import java.util.Map;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.NativeItem;
import com.zhekasmirnov.innercore.api.NativeItemInstanceExtra;

import android.support.annotation.Nullable;
import android.util.Pair;
import vsdum.kex.japi.items.components.IUsable;
import vsdum.kex.modules.states.BlockState;
import vsdum.kex.natives.Actor;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.natives.Player;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Direction;
import vsdum.kex.util.mcmath.Vec3d;
import vsdum.kex.japi.items.components.ICustomDispenseBehavior;
import vsdum.kex.japi.items.components.ICustomUsingReleasedBehavior;
import vsdum.kex.japi.items.components.IHasDynamicIcon;
import vsdum.kex.japi.items.components.IHasUseResult;
import vsdum.kex.japi.items.components.INoTargetUsable;
import vsdum.kex.japi.items.components.IThrowable;

public class ItemEvents {
    
    static final Map<Integer, ICustomDispenseBehavior> onDispenseEvents = new HashMap<>();
    static final Map<Integer, ICustomUsingReleasedBehavior> onReleaseUsingEvents = new HashMap<>();
    static final Map<Integer, IHasDynamicIcon> getIconEvents = new HashMap<>();
    static final Map<Integer, IHasUseResult> onCompleteUsingEvents = new HashMap<>();
    static final Map<Integer, INoTargetUsable> onUseNoTargetEvents = new HashMap<>();
    static final Map<Integer, IThrowable> onProjectileHitEvents = new HashMap<>();
    static final Map<Integer, IUsable> onUseEvents = new HashMap<>();

    public static void onDispense(int x, int y, int z, int side, float vx, float vy, float vz, int id, int count, int data, @Nullable NativeItemInstanceExtra extra, int dimension, int dispenserSlot)
    {
        if(onDispenseEvents.containsKey(id))
        {
            onDispenseEvents.get(id).onDispense(new BlockPos(x, y, z), Direction.VALUES[side], new Vec3d(vx, vy, vz), new ItemStack(id, count, data, extra), ExtendedBlockSource.getDefaultForDimension(dimension), dispenserSlot);
        }
    }

    public static void onReleaseUsing(int id, int count, int data, @Nullable NativeItemInstanceExtra extra, int ticksLeft, long player)
    {
        if(onReleaseUsingEvents.containsKey(id))
        {
            onReleaseUsingEvents.get(id).onReleaseUsing(new ItemStack(id, count, data, extra), ticksLeft, new Player(player));
        }
    }

    public static void getIcon(int id, int count, int data, @Nullable NativeItemInstanceExtra extra, boolean isModUI)
    {
        if(getIconEvents.containsKey(id))
        {
            Pair<String, Integer> icon = getIconEvents.get(id).getIcon(new ItemStack(id, count, data, extra), isModUI);
            if(icon != null) NativeItem.overrideItemIcon(icon.first, icon.second);
        }
    }

    public static void onCompleteUsing(int id, int count, int data, @Nullable NativeItemInstanceExtra extra, long player)
    {
        if(onCompleteUsingEvents.containsKey(id))
        {
            onCompleteUsingEvents.get(id).onCompleteUsing(new ItemStack(id, count, data, extra), new Player(player));
        }
    }

    public static void onUseNoTarget(int id, int count, int data, @Nullable NativeItemInstanceExtra extra, long player)
    {
        if(onUseNoTargetEvents.containsKey(id))
        {
            onUseNoTargetEvents.get(id).onUseNoTarget(new ItemStack(id, count, data, extra), new Player(player));
        }
    }

    public static void onProjectileHit(long projectile, int id, int count, int data, @Nullable NativeItemInstanceExtra extra, float hx, float hy, float hz, long hitEntity, int blockX, int blockY, int blockZ, int blockSide)
    {
        IThrowable component = onProjectileHitEvents.get(id);
        if(component != null)
        {
            if(hitEntity == -1L)
            {
                component.onProjectileHitBlock(new Actor(projectile), new ItemStack(id, count, data, extra), new Vec3d(hx, hy, hz), new BlockPos(blockX, blockY, blockZ), Direction.VALUES[blockSide]);
            } else {
                component.onProjectileHitEntity(new Actor(projectile), new ItemStack(id, count, data, extra), new Vec3d(hx, hy, hz), new Actor(hitEntity));
            }
        }
    }

    public static void onUse(int x, int y, int z, int side, float vx, float vy, float vz, int id, int count, int data, @Nullable NativeItemInstanceExtra extra, int blockID, int blockData, long player)
    {
        if(onUseEvents.containsKey(id))
        {
            onUseEvents.get(id).onUse(new BlockPos(x, y, z), Direction.VALUES[side], new Vec3d(vx, vy, vz), new ItemStack(id, count, data, extra), new BlockState(blockID, blockData), new Player(player));
        }
    }

}
