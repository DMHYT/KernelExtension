package vsdum.kex.modules;

import java.lang.reflect.Constructor;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import com.zhekasmirnov.apparatus.mod.ContentIdScope;
import com.zhekasmirnov.apparatus.mod.ContentIdSource;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.nbt.NativeCompoundTag;

import android.support.annotation.Nullable;
import vsdum.kex.modules.tileentity.*;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.natives.Player;
import vsdum.kex.util.SetBuilder;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Vec3d;

public class TileEntityModule {
    
    private static final Map<Integer, Class<? extends BlockActor>> customTileEntityTypes = new HashMap<>();
    private static final Map<Long, BlockActor> customTileEntityMap = new HashMap<>();
    private static final Set<String> vanillaTileEntityTypeNames = new SetBuilder<String>()
        .add("Furnace").add("Chest").add("NetherReactor").add("Sign").add("MobSpawner").add("Skull").add("FlowerPot").add("BrewingStand").add("EnchantTable").add("DaylightDetector").add("Music").add("Comparator").add("Dispenser").add("Dropper").add("Hopper").add("Cauldron").add("ItemFrame").add("PistonArm").add("Beacon").add("MovingBlock").add("EndPortal").add("EnderChest").add("EndGateway").add("Banner").add("StructureBlock").add("JigsawBlock").add("ChalkboardBlock").add("ShulkerBox").add("CommandBlock").add("Bed").add("ChemistryTable").add("Conduit").add("Lectern").add("BlastFurnace").add("Bell").add("Smoker").add("Campfire").add("Barrel").add("Lodestone")
        .build();
    private static final ContentIdScope idSource = ContentIdSource.getGlobal().getOrCreateScope("kex-nativetetypes");

    @Nullable private static BlockActor getOrCreate(long tilePtr)
    {
        return getOrCreate(tilePtr, 0L);
    }

    @Nullable private static BlockActor getOrCreate(long tilePtr, long blockSourcePtr)
    {
        if(customTileEntityMap.containsKey(tilePtr))
        {
            BlockActor result = customTileEntityMap.get(tilePtr);
            if(blockSourcePtr != 0L && !result.hasWorld())
            {
                result.setWorld(new ExtendedBlockSource(blockSourcePtr));
            }
            return result;
        }
        int type = TileEntityNativeAPI.getType(tilePtr);
        if(customTileEntityTypes.containsKey(type))
        {
            Class<? extends BlockActor> tileClass = customTileEntityTypes.get(type);
            try {
                Constructor<? extends BlockActor> tileConstructor = tileClass.getConstructor(long.class, int.class, BlockPos.class);
                int[] pos = TileEntityNativeAPI.getPosition(tilePtr);
                BlockActor result = tileConstructor.newInstance(tilePtr, type, new BlockPos(pos[0], pos[1], pos[2]));
                if(blockSourcePtr != 0L)
                {
                    result.setWorld(new ExtendedBlockSource(blockSourcePtr));
                }
                customTileEntityMap.put(tilePtr, result);
                return result;
            } catch(Throwable ex) { ex.printStackTrace(); }
        }
        return null;
    }

    private static void load(long tilePtr, long tagPtr)
    {
        getOrCreate(tilePtr).load(new NativeCompoundTag(tagPtr).setFinalizable(false), true);
    }

    private static boolean save(long tilePtr, long tagPtr)
    {
        return getOrCreate(tilePtr).save(new NativeCompoundTag(tagPtr).setFinalizable(false), true);
    }

    private static void tick(long tilePtr, long blockSourcePtr)
    {
        getOrCreate(tilePtr, blockSourcePtr).tick();
    }

    private static boolean isFinished(long tilePtr)
    {
        return getOrCreate(tilePtr).isFinished();
    }

    private static void onChanged(long tilePtr, long blockSourcePtr)
    {
        getOrCreate(tilePtr, blockSourcePtr).onChanged();
    }

    private static boolean isMovable(long tilePtr, long blockSourcePtr)
    {
        return getOrCreate(tilePtr, blockSourcePtr).isMovable();
    }

    private static void onPlace(long tilePtr, long blockSourcePtr)
    {
        getOrCreate(tilePtr, blockSourcePtr).onPlace();
    }

    private static void onMove(long tilePtr)
    {
        getOrCreate(tilePtr).updateBlockPos().onMove();
    }

    private static void onRemoved(long tilePtr, long blockSourcePtr)
    {
        BlockActor tile = getOrCreate(tilePtr, blockSourcePtr);
        customTileEntityMap.remove(tile.getPointer());
        tile.onRemoved();
    }

    private static void triggerEvent(long tilePtr, int id, int type)
    {
        getOrCreate(tilePtr).triggerEvent(id, type);
    }

    private static void onNeighborChanged(long tilePtr, long blockSourcePtr, int changedX, int changedY, int changedZ)
    {
        getOrCreate(tilePtr, blockSourcePtr).onNeighborChanged(new BlockPos(changedX, changedY, changedZ));
    }

    @Nullable private static String getCustomName(long tilePtr)
    {
        return getOrCreate(tilePtr).getCustomName();
    }

    @Nullable private static String getName(long tilePtr)
    {
        return getOrCreate(tilePtr).getName();
    }

    private static void setCustomName(long tilePtr, String customName)
    {
        getOrCreate(tilePtr).setCustomName(customName);
    }

    private static void onChunkLoaded(long tilePtr)
    {
        getOrCreate(tilePtr).onChunkLoaded();
    }

    private static void onChunkUnloaded(long tilePtr)
    {
        getOrCreate(tilePtr).onChunkUnloaded();
    }

    private static boolean onUse(long tilePtr, long playerUid, byte side, float vecX, float vecY, float vecZ)
    {
        return getOrCreate(tilePtr).onUse(new Player(playerUid), side, new Vec3d(vecX, vecY, vecZ));
    }

    private static void getUpdatePacket(long tilePtr, long blockSourcePtr, long tagPtr)
    {
        getOrCreate(tilePtr, blockSourcePtr).getUpdatePacket(new NativeCompoundTag(tagPtr).setFinalizable(false));
    }

    private static void onUpdatePacket(long tilePtr, long blockSourcePtr, long tagPtr)
    {
        getOrCreate(tilePtr, blockSourcePtr).onUpdatePacket(new NativeCompoundTag(tagPtr).setFinalizable(false));
    }

    public static int registerTileEntityType(String typeName, Class<? extends BlockActor> typeClass)
    {
        if(vanillaTileEntityTypeNames.contains(typeName))
        {
            throw new IllegalArgumentException(String.format("Tile entity type name %s has already been registered by vanilla! Try using another name for your tile entity class %s", new Object[]{ typeName, typeClass.getName() }));
        }
        if(idSource.isNameIdUsed(typeName))
        {
            throw new IllegalArgumentException(String.format("Tile entity type name %s has already been registered before! Try using another name for your tile entity class %s", new Object[]{ typeName, typeClass.getName() }));
        }
        if(typeClass == BlockActor.class)
        {
            throw new IllegalArgumentException("You cannot register a tile entity type using base BlockActor abstract class!");
        }
        int typeId = idSource.getOrGenerateId(typeName, 1024, Integer.MAX_VALUE, true);
        TileEntityNativeAPI.newType(typeName, typeId);
        customTileEntityTypes.put(typeId, typeClass);
        Logger.debug("KEX-TileEntityModule", String.format("Successfully assigned numeric ID %d to custom tile entity type name %s", new Object[]{ Integer.valueOf(typeId), typeName }));
        return typeId;
    }

    public static native void registerForBlock(int blockID, int type);

}
