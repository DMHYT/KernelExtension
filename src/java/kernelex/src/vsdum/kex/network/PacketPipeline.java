package vsdum.kex.network;

import com.zhekasmirnov.apparatus.multiplayer.server.ConnectedClient;
import com.zhekasmirnov.apparatus.multiplayer.util.list.ConnectedClientList;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Entity;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.MCSystem;

import vsdum.kex.network.packets.PacketSound;

public class PacketPipeline {

    private static final PacketPipeline singleton = new PacketPipeline();

    public static final PacketPipeline getSingleton()
    {
        return singleton;
    }

    private boolean wasInit = false;

    private PacketPipeline() {}
    
    public void sendTo(ClientPacket message, long player)
    {
        try {
            ConnectedClient client = MCSystem.getNetwork().getClientForPlayer(player);
            if(client != null)
            {
                client.send(message.getIdentifier(), message.serialize());
            }
        } catch(Throwable ex) { ex.printStackTrace(); }
    }

    public void sendToServer(ServerPacket message)
    {
        try {
            MCSystem.getNetwork()
                .sendToServer(message.getIdentifier(), message.serialize());
        } catch(Throwable ex) { ex.printStackTrace(); }
    }

    public void sendToAllAround(ClientPacket message, long entity, float range)
    {
        float[] pos = Entity.getPosition(entity);
        this.sendToAllAround(message, pos[0], pos[1], pos[2], Entity.getDimension(entity), range);
    }

    public void sendToAllAround(ClientPacket message, float x, float y, float z, int dimension, float range)
    {
        try {
            new ConnectedClientList()
                .setupDistancePolicy(x, y, z, dimension, range)
                .send(message.getIdentifier(), message.serialize());
        } catch(Throwable ex) { ex.printStackTrace(); }
    }

    public void sendToAll(ClientPacket message)
    {
        try {
            MCSystem.getNetwork()
                .sendToAllClients(message.getIdentifier(), message.serialize());
        } catch(Throwable ex) { ex.printStackTrace(); }
    }

    public void sendToDimension(ClientPacket message, int dimension)
    {
        try {
            new ConnectedClientList()
                .setupAllInDimensionPolicy(dimension)
                .send(message.getIdentifier(), message.serialize());
        } catch(Throwable ex) { ex.printStackTrace(); }
    }

    public void initPackets()
    {
        if(!this.wasInit)
        {
            PacketSound.register();
            this.wasInit = true;
        }
    }

}
