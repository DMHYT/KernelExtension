package vsdum.kex.modules.tileentity;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import org.json.JSONException;
import org.json.JSONObject;

import com.zhekasmirnov.apparatus.api.container.ItemContainer;
import com.zhekasmirnov.apparatus.mod.ContentIdScope;
import com.zhekasmirnov.apparatus.mod.ContentIdSource;
import com.zhekasmirnov.apparatus.multiplayer.util.entity.NetworkEntity;
import com.zhekasmirnov.apparatus.multiplayer.util.entity.NetworkEntityType;
import com.zhekasmirnov.apparatus.multiplayer.util.entity.SyncedNetworkData;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import android.support.annotation.Nullable;
import android.util.Pair;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.NBTJSON;
import vsdum.kex.util.SetBuilder;
import vsdum.kex.util.mcmath.BlockPos;

public class TileEntityData {

    private static final Map<String, Pair<String, NetworkEntity>> awaitingClientNetworkData = new HashMap<>();
    private static final Map<Integer, NetworkEntityType> networkEntityTypes = new HashMap<>();

    public static final Map<Long, BlockActor> customTileEntityMap = new HashMap<>();
    public static final Map<Integer, TileEntityCreationCallback> customTileEntityCreationCallbacks = new HashMap<>();

    public static final Set<String> vanillaTileEntityTypes = new SetBuilder<String>()
        .add("Furnace")
        .add("Chest")
        .add("NetherReactor")
        .add("Sign")
        .add("MobSpawner")
        .add("Skull")
        .add("FlowerPot")
        .add("BrewingStand")
        .add("EnchantTable")
        .add("DaylightDetector")
        .add("Music")
        .add("Comparator")
        .add("Dispenser")
        .add("Dropper")
        .add("Hopper")
        .add("Cauldron")
        .add("ItemFrame")
        .add("PistonArm")
        .add("Beacon")
        .add("MovingBlock")
        .add("EndPortal")
        .add("EnderChest")
        .add("EndGateway")
        .add("Banner")
        .add("StructureBlock")
        .add("JigsawBlock")
        .add("ChalkboardBlock")
        .add("ShulkerBox")
        .add("CommandBlock")
        .add("Bed")
        .add("ChemistryTable")
        .add("Conduit")
        .add("Lectern")
        .add("BlastFurnace")
        .add("Bell")
        .add("Smoker")
        .add("Campfire")
        .add("Barrel")
        .add("Lodestone")
        .build();

    public static final ContentIdScope idSource = ContentIdSource.getGlobal().getOrCreateScope("kex-nativetetypes");

    @Nullable static BlockActor getOrCreate(long tilePtr)
    {
        if(customTileEntityMap.containsKey(tilePtr))
        {
            return customTileEntityMap.get(tilePtr);
        }
        int type = TileEntityNativeAPI.getType(tilePtr);
        if(customTileEntityCreationCallbacks.containsKey(type))
        {
            int[] pos = TileEntityNativeAPI.getPosition(tilePtr);
            BlockActor result = customTileEntityCreationCallbacks.get(type).create(tilePtr, type, new BlockPos(pos[0], pos[1], pos[2]));
            customTileEntityMap.put(tilePtr, result);
            return result;
        }
        return null;
    }

    static NetworkEntityType getNetworkEntityTypeFor(BlockActor tile)
    {
        int type = tile.getType();
        if(networkEntityTypes.containsKey(type))
        {
            return networkEntityTypes.get(type);
        }
        NetworkEntityType result = new NetworkEntityType("KEX-TILE-" + type)
            .setClientListSetupListener((list, target, entity) -> {
                BlockActor tileEntity = (BlockActor) target;
                BlockPos pos = tileEntity.getBlockPos();
                list.setupDistancePolicy(pos.x + .5f, pos.y + .5f, pos.z + .5f, tileEntity.getDimension(), 128f);
            })
            .setClientEntityAddedListener((entity, packet) -> {
                JSONObject packetJSON = (JSONObject) packet;
                if(
                    !packetJSON.has("x") ||
                    !packetJSON.has("y") ||
                    !packetJSON.has("z") ||
                    !packetJSON.has("d") ||
                    !packetJSON.has("sd")
                ) { return null; }
                try {
                    int x = packetJSON.getInt("x");
                    int y = packetJSON.getInt("y");
                    int z = packetJSON.getInt("z");
                    int dimension = packetJSON.getInt("d");
                    String networkDataName = packetJSON.getString("sd");
                    long tilePtr = TileEntityNativeAPI.get(ExtendedBlockSource.getCurrentClientRegion().getPointer(), x, y, z);
                    if(customTileEntityMap.containsKey(tilePtr))
                    {
                        BlockActor tileEntity = customTileEntityMap.get(tilePtr);
                        tileEntity.networkEntity = entity;
                        tileEntity.networkData = SyncedNetworkData.getClientSyncedData(networkDataName);
                        return tileEntity;
                    } else putAwaitingData(x, y, z, dimension, networkDataName, entity);
                } catch(JSONException ex) { ex.printStackTrace(); }
                return null;
            })
            .setClientAddPacketFactory((target, entity, client) -> {
                BlockActor tileEntity = (BlockActor) target;
                BlockPos pos = tileEntity.getBlockPos();
                JSONObject resultJSON = new JSONObject();
                try {
                    resultJSON
                        .put("x", pos.x)
                        .put("y", pos.y)
                        .put("z", pos.z)
                        .put("d", tileEntity.getDimension())
                        .put("sd", tileEntity.networkData.getName());
                } catch(JSONException ex) { ex.printStackTrace(); }
                return resultJSON;
            })
            .addClientPacketListener("kex.tile.server.update.nbt", (target, entity, packet, extra) -> ((BlockActor) target).onUpdatePacket(NBTJSON.JSON2NBT((JSONObject) packet)))
            .addClientPacketListener("kex.tile.server.update.json", (target, entity, packet, extra) -> ((BlockActor) target).onUpdatePacketJSON((JSONObject) packet));
        tile.getServerEvents().build().forEach(result::addServerPacketListener);
        tile.getClientEvents().build().forEach(result::addClientPacketListener);
        tile.getContainerClientEvents().build().forEach((eventName, eventHandler) -> ItemContainer.addClientEventListener(result.getTypeName(), eventName, eventHandler));
        ItemContainer.registerScreenFactory(result.getTypeName(), tile::getScreenByName);
        networkEntityTypes.put(type, result);
        return result;
    }

    @Nullable static Pair<String, NetworkEntity> getAwaitingData(int x, int y, int z, int dimension)
    {
        String key = x + ":" + y + ":" + z + ":" + dimension;
        return awaitingClientNetworkData.containsKey(key) ? awaitingClientNetworkData.remove(key) : null;
    }

    private static void putAwaitingData(int x, int y, int z, int dimension, String networkDataName, NetworkEntity networkEntity)
    {
        awaitingClientNetworkData.put(x + ":" + y + ":" + z + ":" + dimension, new Pair<>(networkDataName, networkEntity));
    }

    public static void onLevelLeft()
    {
        Logger.debug("KEX-TileEntityData", String.format("Player leaving level, clearing %d custom tile entity interfaces and %d awaiting client network data objects", customTileEntityMap.size(), awaitingClientNetworkData.size()));
        customTileEntityMap.clear();
        awaitingClientNetworkData.clear();
    }
    
}
