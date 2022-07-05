package vsdum.kex.network;

import org.json.JSONObject;

public abstract class AbstractPacket {
    
    public abstract String getIdentifier();

    public abstract JSONObject serialize();

    public abstract void deserialize(JSONObject from);

}
