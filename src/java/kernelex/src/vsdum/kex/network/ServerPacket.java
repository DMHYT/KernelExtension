package vsdum.kex.network;

import org.json.JSONObject;

import com.zhekasmirnov.apparatus.multiplayer.server.ConnectedClient;
import com.zhekasmirnov.apparatus.multiplayer.server.ModdedServer.OnPacketReceivedListener;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.MCSystem;

public abstract class ServerPacket extends AbstractPacket {
    
    protected static void init(String identifier, OnPacketReceivedListener handler)
    {
        MCSystem.getNetwork().addServerPacket(identifier, handler);
    }

    protected static OnPacketReceivedListener makeListener(ServerHandler handler)
    {
        return new OnPacketReceivedListener() {
            @Override public void onPacketReceived(ConnectedClient sender, Object packetObj, String str, Class<?> clazz)
            {
                if(packetObj instanceof JSONObject)
                {
                    handler.onMessage(sender, (JSONObject) packetObj);
                }
            }
        };
    }

    public static interface ServerHandler {
        public void onMessage(ConnectedClient sender, JSONObject packetObj);
    }

}
