package vsdum.kex.japi.blocks;

import org.json.JSONArray;
import org.json.JSONObject;

import com.zhekasmirnov.innercore.api.unlimited.IDRegistry;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import vsdum.kex.common.IdentifierHolder;
import vsdum.kex.japi.registry.*;

public class Block implements IRegistrable<Block>, IdentifierHolder {

    public final String nameID;
    public final int id;
    public final BlockProperties properties;
    @Nullable public JSONArray defineData = null;
    
    public Block(String nameID)
    {
        this(nameID, BlockProperties.DEFAULT);
    }

    public Block(String nameID, BlockProperties properties)
    {
        this.nameID = nameID;
        this.id = IDRegistry.genBlockID(nameID);
        this.properties = new BlockProperties(properties);
    }

    public final Block setDefineData(JSONArray defineData)
    {
        this.defineData = defineData;
        return this;
    }

    public final Block setDefineData(JSONObject variation)
    {
        this.defineData = new JSONArray().put(variation);
        return this;
    }

    public final Block addVariation(JSONObject variation)
    {
        this.defineData.put(variation);
        return this;
    }

    @Override @NonNull public RegistryObject<Block> getRegistryObject()
    {
        return new BlockRegistryObject<>(this);
    }
    
    @Override public final int getId()
    {
        return this.id;
    }

}
