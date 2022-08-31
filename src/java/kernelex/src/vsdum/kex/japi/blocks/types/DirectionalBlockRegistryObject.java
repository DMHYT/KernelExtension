package vsdum.kex.japi.blocks.types;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.innercore.api.runtime.saver.serializer.ScriptableSerializer;
import com.zhekasmirnov.innercore.api.unlimited.BlockRegistry;

import android.support.annotation.NonNull;
import vsdum.kex.japi.blocks.Block;
import vsdum.kex.japi.blocks.BlockRegistryObject;

public class DirectionalBlockRegistryObject<T extends Block> extends BlockRegistryObject<T> {
    
    public DirectionalBlockRegistryObject(@NonNull T block)
    {
        super(block);
    }

    @Override protected void createBlock()
    {
        try {
            JSONObject block = this.object.defineData.getJSONObject(0);
            JSONArray td = block.getJSONArray("texture");
            JSONArray rotated = new JSONArray()
                .put(new JSONArray()
                    .put(td.optJSONArray(0))
                    .put(td.optJSONArray(1))
                    .put(td.optJSONArray(2))
                    .put(td.optJSONArray(3))
                    .put(td.optJSONArray(4))
                    .put(td.optJSONArray(5)))
                .put(new JSONArray()
                    .put(td.optJSONArray(0))
                    .put(td.optJSONArray(1))
                    .put(td.optJSONArray(3))
                    .put(td.optJSONArray(2))
                    .put(td.optJSONArray(5))
                    .put(td.optJSONArray(4)))
                .put(new JSONArray()
                    .put(td.optJSONArray(0))
                    .put(td.optJSONArray(1))
                    .put(td.optJSONArray(5))
                    .put(td.optJSONArray(4))
                    .put(td.optJSONArray(2))
                    .put(td.optJSONArray(3)))
                .put(new JSONArray()
                    .put(td.optJSONArray(0))
                    .put(td.optJSONArray(1))
                    .put(td.optJSONArray(4))
                    .put(td.optJSONArray(5))
                    .put(td.optJSONArray(3))
                    .put(td.optJSONArray(2)));
            JSONArray rotatedBlocks = new JSONArray();
            for(int i = 0; i < rotated.length(); i++)
            {
                rotatedBlocks.put(new JSONObject()
                    .put("name", block.getString("name"))
                    .put("texture", rotated.getJSONArray(i))
                    .put("inCreative", block.optBoolean("inCreative", true) && i == 0));
            }
            BlockRegistry.createBlock(this.object.id, this.object.nameID, (ScriptableObject) ScriptableSerializer.scriptableFromJson(rotatedBlocks));
        } catch(JSONException ex) { ex.printStackTrace(); }
    }
    
}
