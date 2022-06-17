package vsdum.kex.modules.commands;

public class CommandsNativeAPI {
    
    public static native long nativeNewCommand(String commandName, int permissionLevel, Object[] aliases);
    public static native long nativeAddOverload(long factoryPtr, int overloadIndex);
    public static native void nativeBuildArgument(long vectorPtr, String paramName, int paramType, String enumName, boolean mandatory, int fieldOffset);
    public static native void nativeAddEnum(String enumName, Object[] strings, int[] ints);

}
