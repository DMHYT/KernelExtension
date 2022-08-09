package vsdum.kex.modules.tileentity;

public class TileEntityNativeAPI {

    public static native int getType(long ptr);
    public static native int[] getPosition(long ptr);
    public static native void newType(String name, int id);
    public static native void load(long ptr, long tagPtr);
    public static native boolean save(long ptr, long tagPtr);

}
