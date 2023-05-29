package vsdum.kex.modules.tileentity;

import java.util.Optional;

import org.json.JSONObject;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.apparatus.api.container.ItemContainer;
import com.zhekasmirnov.apparatus.api.container.ItemContainer.ClientEventListener;
import com.zhekasmirnov.apparatus.api.container.ItemContainer.ServerEventListener;
import com.zhekasmirnov.apparatus.multiplayer.util.entity.NetworkEntity;
import com.zhekasmirnov.apparatus.multiplayer.util.entity.NetworkEntityType;
import com.zhekasmirnov.apparatus.multiplayer.util.entity.NetworkEntityType.OnClientPacketListener;
import com.zhekasmirnov.apparatus.multiplayer.util.entity.NetworkEntityType.OnServerPacketListener;
import com.zhekasmirnov.apparatus.multiplayer.util.entity.SyncedNetworkData;
import com.zhekasmirnov.innercore.api.mod.ui.window.IWindow;
import com.zhekasmirnov.innercore.api.nbt.NativeCompoundTag;
import com.zhekasmirnov.innercore.api.runtime.MainThreadQueue;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Pair;
import vsdum.kex.common.INativeInterface;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.natives.Player;
import vsdum.kex.util.MapBuilder;
import vsdum.kex.util.NBTJSON;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Vec3d;

public abstract class BlockActor implements INativeInterface {
    
    private final int type;
    private BlockPos blockPos;

    protected final long pointer;

    @Nullable public NetworkEntityType networkEntityType = null;
    @Nullable public NetworkEntity networkEntity = null;
    @Nullable public SyncedNetworkData networkData = null;
    @Nullable public ItemContainer container = null;

    Optional<Integer> dimension = Optional.empty();
    Optional<Boolean> client = Optional.empty();
    boolean networkInitialized = false;

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

    public int getDimension()
    {
        return this.dimension.isPresent() ? this.dimension.get() : -1;
    }

    public BlockActor updateBlockPos()
    {
        int[] pos = TileEntityNativeAPI.getPosition(this.pointer);
        this.blockPos = new BlockPos(pos[0], pos[1], pos[2]);
        return this;
    }

    @Nullable public BlockState getBlockState()
    {
        return this.hasWorld() ? this.getWorld().getBlock(this.blockPos.x, this.blockPos.y, this.blockPos.z) : null;
    }

    @Nullable public ExtendedBlockSource getWorld()
    {
        return this.hasWorld() ? ExtendedBlockSource.getDefaultForDimension(this.dimension.get()) : null;
    }
    
    public boolean hasWorld()
    {
        return this.dimension.isPresent();
    }

    public int getType()
    {
        return this.type;
    }

    public int getLife()
    {
        return TileEntityNativeAPI.getLife(this.pointer);
    }

    public boolean isClient()
    {
        return this.client.isPresent() ? this.client.get() : true;
    }

    public boolean isServer()
    {
        return !this.isClient();
    }

    public void load(NativeCompoundTag data, boolean fromNative)
    {
        if(fromNative) load(data);
        else TileEntityNativeAPI.load(this.pointer, data.pointer);
    }

    public boolean save(NativeCompoundTag data, boolean fromNative)
    {
        return fromNative ? save(data) : TileEntityNativeAPI.save(this.pointer, data.pointer);
    }

    public void load(NativeCompoundTag data) {}

    public boolean save(NativeCompoundTag data)
    {
        return true;
    }

    @Nullable public NativeCompoundTag getUpdatePacket()
    {
        return null;
    }

    public void onUpdatePacket(NativeCompoundTag packet) {}

    @Nullable public JSONObject getUpdatePacketJSON()
    {
        return null;
    }

    public void onUpdatePacketJSON(JSONObject packet) {}

    public void tick() {}

    public boolean isFinished()
    {
        return false;
    }

    public void onChanged() {}

    public boolean isMovable()
    {
        return false;
    }

    public void onPlace() {}

    public void onMove() {}

    public void onRemoved() {}

    public void triggerEvent(int id, int type) {}

    public void onNeighborChanged(BlockPos changed) {}

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

    public boolean onUse(Player player, byte side, Vec3d vec)
    {
        return false;
    }

    @NonNull public MapBuilder<String, OnServerPacketListener> getServerEvents()
    {
        return new MapBuilder<String, OnServerPacketListener>();
    }

    @NonNull public MapBuilder<String, OnClientPacketListener> getClientEvents()
    {
        return new MapBuilder<String, OnClientPacketListener>();
    }

    @NonNull public MapBuilder<String, ServerEventListener> getContainerServerEvents()
    {
        return new MapBuilder<String, ServerEventListener>();
    }

    @NonNull public MapBuilder<String, ClientEventListener> getContainerClientEvents()
    {
        return new MapBuilder<String, ClientEventListener>();
    }

    @Nullable public IWindow getScreenByName(ItemContainer container, String screenName)
    {
        return null;
    }

    protected void sendUpdatePacket()
    {
        if(this.networkInitialized && this.isServer())
        {
            MainThreadQueue.serverThread.enqueue(() -> {
                NativeCompoundTag packetTag = this.getUpdatePacket();
                if(packetTag != null)
                {
                    this.networkEntity.send("kex.tile.server.update.nbt", NBTJSON.NBT2JSON(packetTag));
                }
            });
        }
    }

    protected void sendUpdatePacketJSON()
    {
        if(this.networkInitialized && this.isServer())
        {
            MainThreadQueue.serverThread.enqueue(() -> {
                JSONObject packetJSON = this.getUpdatePacketJSON();
                if(packetJSON != null)
                {
                    this.networkEntity.send("kex.tile.server.update.json", packetJSON);
                }
            });
        }
    }

    void initNetwork(int dimension, boolean isClient)
    {
        this.dimension = Optional.of(dimension);
        this.client = Optional.of(isClient);
        this.networkEntityType = TileEntityData.getNetworkEntityTypeFor(this);
        if(this.isServer())
        {
            MainThreadQueue.serverThread.enqueue(() -> {
                this.container = new ItemContainer();
                this.container.setParent(this);
                this.container.setClientContainerTypeName(this.networkEntityType.getTypeName());
                this.getContainerServerEvents()
                    .build()
                    .forEach(this.container::addServerEventListener);
                this.networkData = new SyncedNetworkData();
                this.networkEntity = new NetworkEntity(this.networkEntityType, this);
                this.networkData.setClients(this.networkEntity.getClients());
            });
        } else {
            Pair<String, NetworkEntity> awaitingData = TileEntityData.getAwaitingData(this.blockPos.x, this.blockPos.y, this.blockPos.z, this.dimension.isPresent() ? this.dimension.get() : -1);
            if(awaitingData != null)
            {
                this.networkEntity = awaitingData.second;
                this.networkEntity.setTarget(this);
                this.networkData = SyncedNetworkData.getClientSyncedData(awaitingData.first);
            }
        }
        this.networkInitialized = true;
    }
    
    void removeNetworkData()
    {
        if(this.networkInitialized && this.isServer())
        {
            MainThreadQueue.serverThread.enqueue(() -> {
                this.networkEntity.remove();
                this.networkEntity = null;
                this.container.close();
                this.container.dropAt(this.getWorld(), this.blockPos.x + .5f, this.blockPos.y + .5f, this.blockPos.z + .5f);
                this.container.removeEntity();
                this.networkInitialized = false;
            });
        }
    }

}
