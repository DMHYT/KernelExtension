package vsdum.kex.network.packets;

import org.json.JSONException;
import org.json.JSONObject;

import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Entity;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Level;

import vsdum.kex.KernelExtension;
import vsdum.kex.network.ClientPacket;

public class PacketSound extends ClientPacket {

    private static final String IDENTIFIER = "kex.sound";

    @Override public String getIdentifier()
    {
        return IDENTIFIER;
    }

    private String sound;
    private double x;
    private double y;
    private double z;
    private float volume;
    private float pitch;

    public PacketSound() {}

    public PacketSound(String sound, long entity)
    {
        this(sound, entity, -1.0f, -1.0f);
    }
    
    public PacketSound(String sound, long entity, float volume, float pitch)
    {
        this.sound = sound;
        float[] pos = Entity.getPosition(entity);
        this.x = pos[0];
        this.y = pos[1];
        this.z = pos[2];
        this.volume = volume;
        this.pitch = pitch;
    }

    public PacketSound(String sound, double x, double y, double z)
    {
        this(sound, x, y, z, -1.0f, -1.0f);
    }

    public PacketSound(String sound, double x, double y, double z, float volume, float pitch)
    {
        this.sound = sound;
        this.x = x;
        this.y = y;
        this.z = z;
        this.volume = volume;
        this.pitch = pitch;
    }

    @Override public JSONObject serialize()
    {
        JSONObject result = new JSONObject();
        try {
            result
                .put("sound", this.sound)
                .put("x", this.x)
                .put("y", this.y)
                .put("z", this.z)
                .put("volume", this.volume)
                .put("pitch", this.pitch);
        } catch(JSONException ex) { ex.printStackTrace(); }
        return result;
    }

    @Override public void deserialize(JSONObject from)
    {
        try {
            this.sound = from.getString("sound");
            this.x = from.getDouble("x");
            this.y = from.getDouble("y");
            this.z = from.getDouble("z");
            this.volume = (float) from.getDouble("volume");
            this.pitch = (float) from.getDouble("pitch");
        } catch(JSONException ex) { ex.printStackTrace(); }
    }

    public static void register()
    {
        init(IDENTIFIER, makeListener(message -> {
            PacketSound packet = new PacketSound();
            packet.deserialize(message);
            if(packet.volume == -1.0f) packet.volume = 0.5f;
            if(packet.pitch == -1.0f) packet.pitch = 0.4f / ((float) KernelExtension.rand.nextDouble() * 0.4f + 0.8f);
            Level.playSound(packet.x, packet.y, packet.z, packet.sound, packet.volume, packet.pitch);
        }));
    }

}
