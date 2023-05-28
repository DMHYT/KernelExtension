package vsdum.kex.japi.blocks.types;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import vsdum.kex.japi.blocks.Block;
import vsdum.kex.japi.blocks.BlockRegistryObject;

public class DirectionalBlockRegistryObject<T extends Block> extends BlockRegistryObject<T> {
    
    public DirectionalBlockRegistryObject(@NonNull T block)
    {
        super(block);
    }

    @Override protected void createBlock()
    {
        if(this.object.defineData != null && this.object.defineData.length() > 4)
        {
            Logger.warning(String.format("[KEX-BlockRegistry] Directional block %s (%d) has %d variants and exceeds the maximum number of 4 variants (for directional blocks). All the define data after the 4th variant will be ignored!", this.object.nameID, this.object.id, this.object.defineData.length()));
        }
        try {
            this.object.defineData = convertDefineData(this.object.defineData);
        } catch(JSONException ex) { ex.printStackTrace(); }
        super.createBlock();
    }

    @Nullable private static JSONArray convertDefineData(JSONArray defineData)
    throws JSONException
    {
        JSONArray result = new JSONArray();
        for(int variant = 0; variant < 4; variant++)
        {
            JSONObject block = defineData.getJSONObject(variant);
            JSONArray[] rotationVariants = convertTextures(block.getJSONArray("texture"));
            for(int rotationVariant = 0; rotationVariant < 4; rotationVariant++)
            {
                result.put(new JSONObject()
                    .put("name", block.getString("name"))
                    .put("texture", rotationVariants[rotationVariant])
                    .put("inCreative", block.optBoolean("inCreative", true) && rotationVariant == 0));
            }
        }
        return result;
    }

    private static JSONArray[] convertTextures(JSONArray textures)
    {
        return new JSONArray[] {
            new JSONArray()
                .put(textures.optJSONArray(0))
                .put(textures.optJSONArray(1))
                .put(textures.optJSONArray(2))
                .put(textures.optJSONArray(3))
                .put(textures.optJSONArray(4))
                .put(textures.optJSONArray(5)),
            new JSONArray()
                .put(textures.optJSONArray(0))
                .put(textures.optJSONArray(1))
                .put(textures.optJSONArray(3))
                .put(textures.optJSONArray(2))
                .put(textures.optJSONArray(5))
                .put(textures.optJSONArray(4)),
            new JSONArray()
                .put(textures.optJSONArray(0))
                .put(textures.optJSONArray(1))
                .put(textures.optJSONArray(5))
                .put(textures.optJSONArray(4))
                .put(textures.optJSONArray(2))
                .put(textures.optJSONArray(3)),
            new JSONArray()
                .put(textures.optJSONArray(0))
                .put(textures.optJSONArray(1))
                .put(textures.optJSONArray(4))
                .put(textures.optJSONArray(5))
                .put(textures.optJSONArray(3))
                .put(textures.optJSONArray(2))
        };
    }
    
}
