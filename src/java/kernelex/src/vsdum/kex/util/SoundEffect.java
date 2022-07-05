package vsdum.kex.util;

import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.MCSystem;

import vsdum.kex.KernelExtension;
import vsdum.kex.network.PacketPipeline;
import vsdum.kex.network.packets.PacketSound;

public class SoundEffect {

    public static final SoundEffect create(String sound)
    {
        return new SoundEffect(sound);
    }
    
    public final String sound;

    protected SoundEffect(String sound)
    {
        this.sound = sound;
    }

    public void playAt(long entity)
    {
        this.playAt(entity, 0.5f);
    }
    
    public void playAt(long entity, float volume)
    {
        this.playAt(entity, volume, 0.4f / ((float) KernelExtension.rand.nextDouble() * 0.4f + 0.8f));
    }

    public void playAt(long entity, float volume, float pitch)
    {
        if(!this.sound.isEmpty() && !MCSystem.getNetwork().inRemoteWorld())
        {
            PacketPipeline.getSingleton().sendToAllAround(new PacketSound(this.sound, entity, volume, pitch), entity, 32);
        }
    }

    public void playAt(NativeBlockSource world, float x, float y, float z)
    {
        this.playAt(world, x, y, z, 0.5f);
    }

    public void playAt(NativeBlockSource world, float x, float y, float z, float volume)
    {
        this.playAt(world, x, y, z, volume, 0.4f / ((float) KernelExtension.rand.nextDouble() * 0.4f + 0.8f));
    }

    public void playAt(NativeBlockSource world, float x, float y, float z, float volume, float pitch)
    {
        if(!this.sound.isEmpty() && !MCSystem.getNetwork().inRemoteWorld())
        {
            PacketPipeline.getSingleton().sendToAllAround(new PacketSound(this.sound, x, y, z, volume, pitch), x, y, z, world.getDimension(), 32);
        }
    }

    public void playOnlyTo(long player)
    {
        this.playOnlyTo(player, -1.0f, -1.0f);
    }

    public void playOnlyTo(long player, float volume, float pitch)
    {
        if(!this.sound.isEmpty() && !MCSystem.getNetwork().inRemoteWorld())
        {
            PacketPipeline.getSingleton().sendTo(new PacketSound(this.sound, player, volume, pitch), player);
        }
    }

}
