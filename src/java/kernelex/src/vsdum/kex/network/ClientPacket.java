package vsdum.kex.network;

import org.json.JSONObject;

import com.zhekasmirnov.apparatus.multiplayer.client.ModdedClient.OnPacketReceivedListener;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.MCSystem;

public abstract class ClientPacket extends AbstractPacket {
    
    protected static void init(String identifier, OnPacketReceivedListener handler)
    {
        MCSystem.getNetwork().addClientPacket(identifier, handler);
    }

    protected static OnPacketReceivedListener makeListener(ClientHandler handler)
    {
        return new OnPacketReceivedListener() {
            @Override public void onPacketReceived(Object packetObj, String str, Class<?> clazz)
            {
                if(packetObj instanceof JSONObject)
                {
                    handler.onMessage((JSONObject) packetObj);
                }
            }
        };
    }

    public static interface ClientHandler {
        public void onMessage(JSONObject packetObj);
    }

}
