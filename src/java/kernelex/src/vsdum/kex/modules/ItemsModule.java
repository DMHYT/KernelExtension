package vsdum.kex.modules;

public class ItemsModule {
    
    public static native void setRequiresWorldBuilder(int id, boolean requiresWorldBuilder);
    public static native void setExplodable(int id, boolean explodable);
    public static native void setFireResistant(int id, boolean fireResistant);
    public static native void setShouldDespawn(int id, boolean shouldDespawn);
    public static native void setIsMirroredArt(int id, boolean isMirroredArt);
    public static native void setFurnaceBurnIntervalMultiplier(int id, float multiplier);
    public static native void setFurnaceXPMultiplier(int id, float multiplier);
    public static native void setCannotBeRepairedInAnvil(int id);
    
}
