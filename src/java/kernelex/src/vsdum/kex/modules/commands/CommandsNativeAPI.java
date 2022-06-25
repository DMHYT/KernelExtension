package vsdum.kex.modules.commands;

public class CommandsNativeAPI {
    
    public static native long nativeNewCommand(String commandName, int permissionLevel, Object[] aliases);
    public static native long nativeAddOverload(long factoryPtr, int overloadIndex);
    public static native void nativeAddEnum(String enumName, Object[] strings, int[] ints);
    public static native void nativeAddStringEnum(String enumName, Object[] strings);
    public static native void nativeBuildIntArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset, int defaultValue);
    public static native void nativeBuildFloatArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset, float defaultValue);
    public static native void nativeBuildBoolArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset, boolean defaultValue);
    public static native void nativeBuildRelativeFloatArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset, float defaultValue);
    public static native void nativeBuildPositionArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset, float defaultX, float defaultY, float defaultZ);
    public static native void nativeBuildFloatPositionArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset, float defaultX, float defaultY, float defaultZ);
    public static native void nativeBuildStringArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset, String defaultValue);
    public static native void nativeBuildMessageArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset);
    public static native void nativeBuildJsonArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset);
    public static native void nativeBuildEntityArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset);
    public static native void nativeBuildPlayerArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset);
    public static native void nativeBuildEnumArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset, String enumName, int defaultValue);
    public static native void nativeBuildStringEnumArgument(long vectorPtr, String paramName, boolean mandatory, int fieldOffset, String enumName, String defaultValue);
    public static native int nativeGetInt(long ptr, int offset);
    public static native float nativeGetFloat(long ptr, int offset);
    public static native boolean nativeGetBool(long ptr, int offset);
    public static native float nativeGetRelativeFloat(long ptr, int offset, float center);
    public static native float[] nativeGetPosition(long ptr, int offset, long originPtr);
    public static native float[] nativeGetFloatPosition(long ptr, int offset, long originPtr);
    public static native String nativeGetString(long ptr, int offset);
    public static native String nativeGetMessage(long ptr, int offset, long originPtr);
    public static native String nativeGetJson(long ptr, int offset);
    public static native long[] nativeGetEntities(long ptr, int offset, long originPtr);
    public static native long[] nativeGetPlayers(long ptr, int offset, long originPtr);
    public static native int[] nativeGetSourceBlockPosition(long ptr);
    public static native float[] nativeGetSourceWorldPosition(long ptr);
    public static native long nativeGetSourceLevel(long ptr);
    public static native long nativeGetSourceDimension(long ptr);
    public static native long nativeGetSourceEntity(long ptr);
    public static native void nativeEmptySuccess(long ptr);
    public static native void nativeSuccess(long ptr, String msg);
    public static native void nativeError(long ptr, String msg);

}
