package vsdum.kex.modules.loot;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import com.zhekasmirnov.innercore.utils.FileTools;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.mozilla.javascript.ScriptableObject;

import android.util.Pair;
import vsdum.kex.common.IJSONSerializable;
import vsdum.kex.util.CommonTypes;
import vsdum.kex.util.JsonUtils;

public class LootModifier implements IJSONSerializable {
    
    public final List<LootPool> pools = new ArrayList<>();

    public LootModifier() {}

    public LootPool createNewPool()
    {
        return createNewPool(1);
    }
    
    public LootPool createNewPool(int rolls)
    {
        LootPool pool = new LootPool(this);
        try {
            pool.obj.put("rolls", rolls);
        } catch(JSONException ex) {}
        this.pools.add(pool);
        return pool;
    }

    public LootPool createNewPool(int minRolls, int maxRolls)
    {
        LootPool pool = new LootPool(this);
        try {
            pool.obj.put("rolls", new JSONObject()
                .put("min", minRolls)
                .put("max", maxRolls));
        } catch(JSONException ex) {}
        this.pools.add(pool);
        return pool;
    }

    public LootModifier modifyWithAnotherLootTable(String path)
    {
        try {
            JSONObject tableJson = FileTools.readJSON(path);
            if(tableJson.has("pools"))
            {
                JSONArray poolsArray = tableJson.optJSONArray("pools");
                if(poolsArray != null)
                {
                    for(int i = 0; i < poolsArray.length(); ++i)
                    {
                        JSONObject poolJson = poolsArray.optJSONObject(i);
                        if(poolJson != null)
                        {
                            LootPool pool = new LootPool(this);
                            pool.obj.remove("entries");
                            Iterator<String> poolKeys = poolJson.keys();
                            if(poolKeys.hasNext())
                            {
                                while(poolKeys.hasNext())
                                {
                                    String poolKey = poolKeys.next();
                                    pool.obj.put(poolKey, poolJson.get(poolKey));
                                }
                                this.pools.add(pool);
                            }
                        }
                    }
                }
            }
        } catch(Exception ex) {}
        return this;            
    }

    public LootModifier modifyWithJSON(ScriptableObject scr)
    {
        JSONObject scrJson = CommonTypes.scriptableToJson(scr);
        try {
            JSONArray poolsArray = scrJson.getJSONArray("pools");
            for(int i = 0; i < poolsArray.length(); ++i)
            {
                JSONObject poolJson = poolsArray.getJSONObject(i);
                LootPool pool = new LootPool(this);
                pool.obj.remove("entries");
                Iterator<String> poolKeys = poolJson.keys();
                if(poolKeys.hasNext())
                {
                    while(poolKeys.hasNext())
                    {
                        String poolKey = poolKeys.next();
                        pool.obj.put(poolKey, poolJson.get(poolKey));
                    }
                    this.pools.add(pool);
                }
            }
        } catch(JSONException ex) {}
        return this;
    }

    public LootModifier addItem(int id, int count, int data, float chance)
    {
        return addItem(id, count, data, chance, 1);
    }

    public LootModifier addItem(int id, int count, int data, float chance, int rolls)
    {
        LootPool pool = this.createNewPool(rolls)
            .addEntry()
                .describeItem(id)
                .setCount(count)
                .setData(data)
                .endEntry();
        if(chance < 1.0f)
        {
            pool.beginConditions()
                .addRandomChanceCondition(chance)
            .endConditions();
        }
        return this;
    }

    public LootModifier addItem(int id, int count, int data, float chance, ScriptableObject rolls)
    {
        Pair<Integer, Integer> drolls = CommonTypes.deserializeMinMaxScriptable(rolls);
        LootPool pool = this.createNewPool(drolls.first.intValue(), drolls.second.intValue())
            .addEntry()
                .describeItem(id)
                .setCount(count)
                .setData(data)
                .endEntry();
        if(chance < 1.0f)
        {
            pool.beginConditions()
                .addRandomChanceCondition(chance)
            .endConditions();
        }
        return this;
    }

    public LootModifier addItem(int id, ScriptableObject count, int data, float chance)
    {
        return addItem(id, count, data, chance, 1);
    }

    public LootModifier addItem(int id, ScriptableObject count, int data, float chance, int rolls)
    {
        Pair<Integer, Integer> dcount = CommonTypes.deserializeMinMaxScriptable(count);
        LootPool pool = this.createNewPool(rolls)
            .addEntry()
                .describeItem(id)
                .setCount(dcount.first.intValue(), dcount.second.intValue())
                .setData(data)
                .endEntry();
        if(chance < 1.0f)
        {
            pool.beginConditions()
                .addRandomChanceCondition(chance)
            .endConditions();
        }
        return this;
    }

    public LootModifier addItem(int id, ScriptableObject count, int data, float chance, ScriptableObject rolls)
    {
        Pair<Integer, Integer> dcount = CommonTypes.deserializeMinMaxScriptable(count);
        Pair<Integer, Integer> drolls = CommonTypes.deserializeMinMaxScriptable(rolls);
        LootPool pool = this.createNewPool(drolls.first.intValue(), drolls.second.intValue())
            .addEntry()
                .describeItem(id)
                .setCount(dcount.first.intValue(), dcount.second.intValue())
                .setData(data)
                .endEntry();
        if(chance < 1.0f)
        {
            pool.beginConditions()
                .addRandomChanceCondition(chance)
            .endConditions();
        }
        return this;
    }

    public LootModifier addAddonItem(String namespace, String identifier, int count, int data, float chance)
    {
        return addAddonItem(namespace, identifier, count, data, chance, 1);
    }

    public LootModifier addAddonItem(String namespace, String identifier, int count, int data, float chance, int rolls)
    {
        LootPool pool = this.createNewPool(rolls)
            .addEntry()
                .describeItem(namespace, identifier)
                .setCount(count)
                .setData(data)
                .endEntry();
        if(chance < 1.0f)
        {
            pool.beginConditions()
                .addRandomChanceCondition(chance)
            .endConditions();
        }
        return this;
    }

    public LootModifier addAddonItem(String namespace, String identifier, int count, int data, float chance, ScriptableObject rolls)
    {
        Pair<Integer, Integer> drolls = CommonTypes.deserializeMinMaxScriptable(rolls);
        LootPool pool = this.createNewPool(drolls.first.intValue(), drolls.second.intValue())
            .addEntry()
                .describeItem(namespace, identifier)
                .setCount(count)
                .setData(data)
                .endEntry();
        if(chance < 1.0f)
        {
            pool.beginConditions()
                .addRandomChanceCondition(chance)
            .endConditions();
        }
        return this;
    }

    public LootModifier addAddonItem(String namespace, String identifier, ScriptableObject count, int data, float chance)
    {
        return addAddonItem(namespace, identifier, count, data, chance, 1);
    }

    public LootModifier addAddonItem(String namespace, String identifier, ScriptableObject count, int data, float chance, int rolls)
    {
        Pair<Integer, Integer> dcount = CommonTypes.deserializeMinMaxScriptable(count);
        LootPool pool = this.createNewPool(rolls)
            .addEntry()
                .describeItem(namespace, identifier)
                .setCount(dcount.first.intValue(), dcount.second.intValue())
                .setData(data)
                .endEntry();
        if(chance < 1.0f)
        {
            pool.beginConditions()
                .addRandomChanceCondition(chance)
            .endConditions();
        }
        return this;
    }

    public LootModifier addAddonItem(String namespace, String identifier, ScriptableObject count, int data, float chance, ScriptableObject rolls)
    {
        Pair<Integer, Integer> dcount = CommonTypes.deserializeMinMaxScriptable(count);
        Pair<Integer, Integer> drolls = CommonTypes.deserializeMinMaxScriptable(rolls);
        LootPool pool = this.createNewPool(drolls.first.intValue(), drolls.second.intValue())
            .addEntry()
                .describeItem(namespace, identifier)
                .setCount(dcount.first.intValue(), dcount.second.intValue())
                .setData(data)
                .endEntry();
        if(chance < 1.0f)
        {
            pool.beginConditions()
                .addRandomChanceCondition(chance)
            .endConditions();
        }
        return this;
    }

    public void serialize(JSONObject obj)
    {
        try {
            JSONArray poolsArray = JsonUtils.getOrCreateArray(obj, "pools");
            Iterator<LootPool> iter = this.pools.iterator();
            while(iter.hasNext())
            {
                LootPool pool = iter.next();
                poolsArray.put(pool.obj);
            }
        } catch(JSONException ex) {}
    }

}
