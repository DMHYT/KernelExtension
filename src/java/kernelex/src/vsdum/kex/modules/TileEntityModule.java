package vsdum.kex.modules;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

import vsdum.kex.modules.tileentity.TileEntityCreationCallback;
import vsdum.kex.modules.tileentity.TileEntityData;
import vsdum.kex.modules.tileentity.TileEntityNativeAPI;

public class TileEntityModule {

    public static int registerTileEntityType(String typeName, TileEntityCreationCallback callback)
    {
        if(TileEntityData.vanillaTileEntityTypes.contains(typeName))
        {
            throw new IllegalArgumentException(String.format("Tile entity type name %s has already been registered by vanilla! Try using another name", new Object[]{ typeName }));
        }
        if(TileEntityData.idSource.isNameIdUsed(typeName))
        {
            throw new IllegalArgumentException(String.format("Tile entity type name %s has already been registered before! Try using another name", new Object[]{ typeName }));
        }
        int typeId = TileEntityData.idSource.getOrGenerateId(typeName, 1024, Integer.MAX_VALUE, true);
        TileEntityNativeAPI.newType(typeName, typeId);
        TileEntityData.customTileEntityCreationCallbacks.put(typeId, callback);
        Logger.debug("KEX-TileEntityModule", String.format("Successfully assigned numeric ID %d to custom tile entity type name %s", new Object[]{ Integer.valueOf(typeId), typeName }));
        return typeId;
    }

    public static native void registerForBlock(int blockID, int type);

}
