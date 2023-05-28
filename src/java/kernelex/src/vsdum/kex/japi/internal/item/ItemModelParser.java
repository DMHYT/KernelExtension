package vsdum.kex.japi.internal.item;

import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.NativeItemModel;

import vsdum.kex.japi.internal.ResourceManager;
import vsdum.kex.japi.internal.block.model.BakedBlockModel;
import vsdum.kex.japi.internal.block.model.BlockModelManager;
import vsdum.kex.util.AddonUtils;

public class ItemModelParser {
    
    public static void onModsLoaded()
    {
        ResourceManager.forEachFileIn("models/item", file -> {
            String fileName = file.getName();
            if(fileName.toLowerCase().endsWith(".json"))
            {
                fileName = fileName.substring(0, fileName.length() - 5);
                String itemNameID = "item_" + NativeAPI.convertNameId(fileName);
                int itemID = AddonUtils.getNumericIdFromIdentifier(itemNameID);
                if(itemID != -1)
                {
                    BakedBlockModel bakedModel = BlockModelManager.getBakedModelByResourceLocation("item/" + fileName);
                    if(bakedModel == null) return;
                    NativeItemModel itemModel = NativeItemModel.getFor(itemID, 0)
                        .setModel(bakedModel.mesh);
                    if(bakedModel.handModel.isPresent()) itemModel.setHandModel(bakedModel.handMesh);
                    if(bakedModel.guiModel.isPresent()) itemModel.setUiModel(bakedModel.guiMesh);
                }
            }
        });
    }

}
