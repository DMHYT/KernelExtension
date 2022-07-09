package vsdum.kex.modules;

import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.MCSystem;

import vsdum.kex.modules.chunks.*;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.natives.Dimension;

public class ChunksModule {

    public static LoadedRectangle addLoadedRectangle(int dimension, String name)
    {
        return addLoadedRectangle(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject(), name);
    }

    public static LoadedRectangle addLoadedRectangle(NativeBlockSource world, String name)
    {
        return addLoadedRectangle(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject(), name);
    }
    
    public static LoadedRectangle addLoadedRectangle(Dimension dimension, String name)
    {
        ensureServerSide();
        return new LoadedRectangle(dimension, name);
    }

    public static LoadedRectangle addLoadedRectangle(int dimension)
    {
        return addLoadedRectangle(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject());
    }

    public static LoadedRectangle addLoadedRectangle(NativeBlockSource world)
    {
        return addLoadedRectangle(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject());
    }
    
    public static LoadedRectangle addLoadedRectangle(Dimension dimension)
    {
        ensureServerSide();
        return new LoadedRectangle(dimension);
    }

    public static LoadedCircle addLoadedCircle(int dimension, String name)
    {
        return addLoadedCircle(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject(), name);
    }

    public static LoadedCircle addLoadedCircle(NativeBlockSource world, String name)
    {
        return addLoadedCircle(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject(), name);
    }
    
    public static LoadedCircle addLoadedCircle(Dimension dimension, String name)
    {
        ensureServerSide();
        return new LoadedCircle(dimension, name);
    }

    public static LoadedCircle addLoadedCircle(int dimension)
    {
        return addLoadedCircle(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject());
    }

    public static LoadedCircle addLoadedCircle(NativeBlockSource world)
    {
        return addLoadedCircle(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject());
    }
    
    public static LoadedCircle addLoadedCircle(Dimension dimension)
    {
        ensureServerSide();
        return new LoadedCircle(dimension);
    }

    public static LoadedRectangle addLoadedChunk(int dimension, String name, int x, int z)
    {
        return addLoadedChunk(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject(), name, x, z);
    }

    public static LoadedRectangle addLoadedChunk(NativeBlockSource world, String name, int x, int z)
    {
        return addLoadedChunk(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject(), name, x, z);
    }

    public static LoadedRectangle addLoadedChunk(Dimension dimension, String name, int x, int z)
    {
        return addLoadedRectangle(dimension, name)
            .start(x, z).end(x, z);
    }

    public static LoadedRectangle addLoadedChunk(int dimension, int x, int z)
    {
        return addLoadedChunk(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject(), x, z);
    }

    public static LoadedRectangle addLoadedChunk(NativeBlockSource world, int x, int z)
    {
        return addLoadedChunk(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject(), x, z);
    }

    public static LoadedRectangle addLoadedChunk(Dimension dimension, int x, int z)
    {
        return addLoadedRectangle(dimension)
            .start(x, z).end(x, z);
    }

    public static boolean areaExists(String name, int dimension)
    {
        return areaExists(name, ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject());
    }

    public static boolean areaExists(String name, NativeBlockSource world)
    {
        return areaExists(name, ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject());
    }

    public static boolean areaExists(String name, Dimension dimension)
    {
        return dimension.getLevel()
            .getTickingAreasManager()
            .hasArea(name, dimension);
    }

    private static void ensureServerSide()
    {
        if(MCSystem.getNetwork().inRemoteWorld())
        {
            throw new IllegalStateException("Loaded area cannot be created on the client side");
        }
    }

}
