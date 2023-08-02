package vsdum.kex.modules;

import vsdum.kex.modules.tileentity.TileEntityCreationCallback;
import vsdum.kex.modules.tileentity.TileEntityData;

public class TileEntityModule {

    /**
     * Since 4.1+ doesn't return the generated numeric ID of the type.
     * Now you have to call registerForBlock(int blockID, String type)
     */
    public static int registerTileEntityType(String typeName, TileEntityCreationCallback callback)
    {
        if(TileEntityData.vanillaTileEntityTypes.contains(typeName))
        {
            throw new IllegalArgumentException(String.format("Tile entity type name %s has already been registered by vanilla! Try using another name", typeName));
        }
        if(TileEntityData.idScope.has(typeName))
        {
            throw new IllegalArgumentException(String.format("Tile entity type name %s has already been registered before! Try using another name", typeName));
        }
        TileEntityData.idScope.add(typeName);
        TileEntityData.creationCallbacksByNameID.put(typeName, callback);
        return 0;
    }

    public static void registerForBlock(int blockID, String type)
    {
        TileEntityData.blockToTileNameID.put(blockID, type);
    }

    @Deprecated public static native void registerForBlock(int blockID, int type);

}
