package vsdum.kex.modules.tileentity;

public class TileEntityNativeAPI {

    public static native int getType(long ptr);
    public static native int[] getPosition(long ptr);
    public static native void newType(String name, int id);

}
