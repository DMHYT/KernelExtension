package vsdum.kex.modules.loot;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.support.annotation.Nullable;
import vsdum.kex.util.JsonUtils;

public class LootPool {
    
    public final JSONObject obj = new JSONObject();
    public final LootModifier modifier;

    public LootPool(LootModifier modifier)
    {
        this.modifier = modifier;
        try {
            this.obj.put("entries", new JSONArray());
        } catch(JSONException ex) {}
    }

    @Nullable public LootConditions beginConditions()
    {
        try {
            JsonUtils.getOrCreateArray(this.obj, "conditions");
            return new LootConditions(this);
        } catch(JSONException ex) {
            return null;
        }
    }

    @Nullable public LootPoolTiers beginTiers()
    {
        try {
            JsonUtils.getOrCreateObject(this.obj, "tiers");
            return new LootPoolTiers(this);
        } catch(JSONException ex) {
            return null;
        }
    }

    @Nullable public LootPoolEntry addEntry()
    {
        try {
            JSONObject entryObj = new JSONObject();
            JSONArray entriesArray = JsonUtils.getOrCreateArray(this.obj, "entries");
            if(entriesArray == null) return null;
            entriesArray.put(entryObj);
            return new LootPoolEntry(this, entryObj);
        } catch(JSONException ex) { return null; }
    }

    public LootModifier endPool()
    {
        return this.modifier;
    }

}
