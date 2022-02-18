package vsdum.kex.modules.loot;

import org.json.JSONException;
import org.json.JSONObject;

import vsdum.kex.util.AddonUtils;
import vsdum.kex.util.JsonUtils;

public class LootPoolEntry {
    
    public final LootPool pool;
    public final JSONObject obj;

    public LootPoolEntry(LootPool pool, JSONObject obj)
    {
        this.pool = pool;
        this.obj = obj;
        try {
            this.obj.put("type", "item");
        } catch(JSONException ex) {}
    }

    public LootPoolEntryFunctions beginFunctions()
    {
        try {
            JsonUtils.getOrCreateArray(this.obj, "functions");
        } catch(JSONException ex) {}
        return new LootPoolEntryFunctions(this);
    }

    public LootPool endEntry()
    {
        return this.pool;
    }

    public LootPoolEntry describeItem(String namespace, String identifier)
    {
        try {
            this.obj.put("name", AddonUtils.getAddonItemIdentifier(namespace, identifier));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntry describeItem(int numericId)
    {
        try {
            this.obj.put("name", AddonUtils.getAddonItemIdentifier(numericId));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntry setCount(int count)
    {
        try {
            this.obj.put("count", count);
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntry setCount(int min, int max)
    {
        try {
            JsonUtils.getOrCreateArray(this.obj, "functions")
                .put(new JSONObject()
                    .put("function", "set_count")
                    .put("count", new JSONObject()
                        .put("min", min)
                        .put("max", max)));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntry setData(int data)
    {
        if(data != 0)
        {
            try {
                JsonUtils.getOrCreateArray(this.obj, "functions")
                    .put(new JSONObject()
                        .put("function", "set_data")
                        .put("data", data));
            } catch(JSONException ex) {}
        }
        return this;
    }

    public LootPoolEntry setData(int min, int max)
    {
        if(!(min == max && min == 0))
        {
            try {
                JsonUtils.getOrCreateArray(this.obj, "functions")
                    .put(new JSONObject()
                        .put("function", "set_data")
                        .put("data", new JSONObject()
                            .put("min", min)
                            .put("max", max)));
            } catch(JSONException ex) {}
        }
        return this;
    }

    public LootPoolEntry setDamage(int damage)
    {
        if(damage != 0)
        {
            try {
                JsonUtils.getOrCreateArray(this.obj, "functions")
                    .put(new JSONObject()
                        .put("function", "set_damage")
                        .put("damage", damage));
            } catch(JSONException ex) {}
        }
        return this;
    }

    public LootPoolEntry setDamage(int min, int max)
    {
        if(!(min == max && min == 0))
        {
            try {
                JsonUtils.getOrCreateArray(this.obj, "functions")
                    .put(new JSONObject()
                        .put("function", "set_damage")
                        .put("damage", new JSONObject()
                            .put("min", min)
                            .put("max", max)));
            } catch(JSONException ex) {}
        }
        return this;
    }

    public LootPoolEntry setCustomName(String name)
    {
        try {
            JsonUtils.getOrCreateArray(this.obj, "functions")
                .put(new JSONObject()
                    .put("function", "set_name")
                    .put("name", name));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntry setWeight(int weight)
    {
        try {
            this.obj.put("weight", weight);
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntry setQuality(int quality)
    {
        try {
            this.obj.put("quality", quality);
        } catch(JSONException ex) {}
        return this;
    }

}
