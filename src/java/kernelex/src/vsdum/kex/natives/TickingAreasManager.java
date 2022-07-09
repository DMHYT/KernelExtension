package vsdum.kex.natives;

import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;

import vsdum.kex.common.INativeInterface;

public class TickingAreasManager implements INativeInterface {

    protected static native boolean nativeHasActiveAreas(long ptr);
    protected static native int nativeCountAreasIn(long ptr, long dimensionPtr);
    protected static native int nativeCountAllAreas(long ptr);
    protected static native boolean nativeHasArea(long ptr, String areaName, int dimensionId);
    protected static native void nativeAddRectangleArea(long ptr, long dimensionPtr, String areaName, int x1, int z1, int x2, int z2);
    protected static native void nativeAddCircleArea(long ptr, long dimensionPtr, String areaName, int x, int z, int radius);
    protected static native void nativeRemoveAreaByPosition(long ptr, long dimensionPtr, int x, int z);
    protected static native void nativeRemoveAreaByName(long ptr, long dimensionPtr, String areaName);
    protected static native String nativeFindUsableDefaultName(long ptr, long dimensionPtr);
    
    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public TickingAreasManager(long ptr)
    {
        this.pointer = ptr;
    }

    public boolean hasActiveAreas()
    {
        return nativeHasActiveAreas(this.pointer);
    }

    public int countAreasIn(int dimension)
    {
        return nativeCountAreasIn(this.pointer, ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject().getPointer());
    }

    public int countAreasIn(NativeBlockSource world)
    {
        ExtendedBlockSource kexWorld = ExtendedBlockSource.toKEXBlockSource(world);
        return nativeCountAreasIn(this.pointer, kexWorld.getDimensionObject().getPointer());
    }

    public int countAreasIn(Dimension dimension)
    {
        return nativeCountAreasIn(this.pointer, dimension.getPointer());
    }

    public int countAllAreas()
    {
        return nativeCountAllAreas(this.pointer);
    }

    public boolean hasArea(String areaName, Dimension dimension)
    {
        return this.hasArea(areaName, dimension.getDimensionId());
    }

    public boolean hasArea(String areaName, NativeBlockSource world)
    {
        return this.hasArea(areaName, world.getDimension());
    }

    public boolean hasArea(String areaName, int dimension)
    {
        return nativeHasArea(this.pointer, areaName, dimension);
    }

    public void addRectangleArea(int dimension, int x1, int z1, int x2, int z2)
    {
        this.addRectangleArea(dimension, this.findUsableDefaultName(dimension), x1, z1, x2, z2);
    }

    public void addRectangleArea(int dimension, String name, int x1, int z1, int x2, int z2)
    {
        this.addRectangleArea(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject(), name, x1, z1, x2, z2);
    }

    public void addRectangleArea(NativeBlockSource world, int x1, int z1, int x2, int z2)
    {
        this.addRectangleArea(world, this.findUsableDefaultName(world), x1, z1, x2, z2);
    }

    public void addRectangleArea(NativeBlockSource world, String name, int x1, int z1, int x2, int z2)
    {
        this.addRectangleArea(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject(), name, x1, z1, x2, z2);
    }

    public void addRectangleArea(Dimension dimension, int x1, int z1, int x2, int z2)
    {
        this.addRectangleArea(dimension, this.findUsableDefaultName(dimension), x1, z1, x2, z2);
    }

    public void addRectangleArea(Dimension dimension, String name, int x1, int z1, int x2, int z2)
    {
        nativeAddRectangleArea(this.pointer, dimension.getPointer(), name, x1, z1, x2, z2);
    }

    public void addCircleArea(int dimension, int x, int z, int radius)
    {
        this.addCircleArea(dimension, this.findUsableDefaultName(dimension), x, z, radius);
    }

    public void addCircleArea(int dimension, String name, int x, int z, int radius)
    {
        this.addCircleArea(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject(), name, x, z, radius);
    }

    public void addCircleArea(NativeBlockSource world, int x, int z, int radius)
    {
        this.addCircleArea(world, this.findUsableDefaultName(world), x, z, radius);
    }

    public void addCircleArea(NativeBlockSource world, String name, int x, int z, int radius)
    {
        this.addCircleArea(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject(), name, x, z, radius);
    }

    public void addCircleArea(Dimension dimension, int x, int z, int radius)
    {
        this.addCircleArea(dimension, this.findUsableDefaultName(dimension), x, z, radius);
    }

    public void addCircleArea(Dimension dimension, String name, int x, int z, int radius)
    {
        nativeAddCircleArea(this.pointer, dimension.getPointer(), name, x, z, radius);
    }

    public void removeAreaByPosition(int dimension, int x, int z)
    {
        this.removeAreaByPosition(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject(), x, z);
    }

    public void removeAreaByPosition(NativeBlockSource world, int x, int z)
    {
        this.removeAreaByPosition(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject(), x, z);
    }

    public void removeAreaByPosition(Dimension dimension, int x, int z)
    {
        nativeRemoveAreaByPosition(this.pointer, dimension.getPointer(), x, z);
    }

    public void removeAreaByName(int dimension, String name)
    {
        this.removeAreaByName(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject(), name);
    }

    public void removeAreaByName(NativeBlockSource world, String name)
    {
        this.removeAreaByName(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject(), name);
    }

    public void removeAreaByName(Dimension dimension, String name)
    {
        nativeRemoveAreaByName(this.pointer, dimension.getPointer(), name);
    }

    public String findUsableDefaultName(int dimension)
    {
        return this.findUsableDefaultName(ExtendedBlockSource.getDefaultForDimension(dimension).getDimensionObject());
    }

    public String findUsableDefaultName(NativeBlockSource world)
    {
        return this.findUsableDefaultName(ExtendedBlockSource.toKEXBlockSource(world).getDimensionObject());
    }

    public String findUsableDefaultName(Dimension dimension)
    {
        return nativeFindUsableDefaultName(this.pointer, dimension.getPointer());
    }

}
