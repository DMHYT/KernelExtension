package vsdum.kex.japi.internal.block.model;

import java.util.HashMap;
import java.util.Map;

import org.json.JSONObject;

import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Logger;
import com.zhekasmirnov.innercore.utils.FileTools;

import android.support.annotation.Nullable;
import vsdum.kex.japi.internal.ResourceManager;

public class BlockModelManager {

    private static final Map<String, BakedBlockModel> bakedModels = new HashMap<>();

    @Nullable public static BakedBlockModel getBakedModelByResourceLocation(String resourceLocation)
    {
        if(bakedModels.containsKey(resourceLocation)) return bakedModels.get(resourceLocation);
        String modelJsonPath = ResourceManager.findFile("models/" + resourceLocation + ".json");
        if(modelJsonPath == null) return null;
        try {
            JSONObject modelJson = FileTools.readJSON(modelJsonPath);
            BakedBlockModel bakedModel = new BlockModelParser(resourceLocation, modelJson).parse().bake();
            if(bakedModel == null) return null;
            bakedModels.put(resourceLocation, bakedModel);
            return getBakedModelByResourceLocation(resourceLocation);
        } catch(Throwable ex) { ex.printStackTrace(); }
        return null;
    }

    @Nullable public static BakedBlockModel getBakedModelWithRotation(String resourceLocation, int x, int y, boolean uvLock)
    {
        String modelKey = String.format("%s:%d:%d:%s", resourceLocation, x, y, uvLock);
        if(bakedModels.containsKey(modelKey)) return bakedModels.get(modelKey);
        BakedBlockModel original = getBakedModelByResourceLocation(resourceLocation);
        if(original == null) return null;
        if(x == 0 && y == 0 && !uvLock) return original;
        BakedBlockModel result = original.copy().rotate(x, y, uvLock);
        bakedModels.put(modelKey, result);
        return result;
    }

    public static void onLevelDisplayed()
    {
        if(!bakedModels.isEmpty())
        {
            long start = System.currentTimeMillis();
            Logger.debug("KEX-BlockModelManager", String.format("The level has been displayed, building %d block models...", bakedModels.size()));
            bakedModels.values().forEach(BakedBlockModel::onLevelDisplayed);
            Logger.debug("KEX-BlockModelManager", String.format("Finished in %d ms!", System.currentTimeMillis() - start));
        } else Logger.debug("KEX-BlockModelManager", String.format("The level has been displayed, no block models to build."));
    }
    
}
