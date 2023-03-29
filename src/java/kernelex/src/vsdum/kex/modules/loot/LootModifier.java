package vsdum.kex.modules.loot;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import com.zhekasmirnov.innercore.utils.FileTools;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import android.util.Pair;
import vsdum.kex.common.CallbackFunction;
import vsdum.kex.common.IJSONSerializable;
import vsdum.kex.util.CommonTypes;
import vsdum.kex.util.JsonUtils;

public class LootModifier implements IJSONSerializable {

    public static interface JSModifyCallback {
        public void onModify(ScriptableObject obj);
    }

    public static interface JSONModifyCallback {
        public void onModify(JSONObject obj);
    }

    private boolean locked = false;
    
    public final List<LootPool> pools = new ArrayList<>();
    public final List<CallbackFunction<JSModifyCallback>> jsCallbacks = new ArrayList<>();
    public final List<CallbackFunction<JSONModifyCallback>> jsonCallbacks = new ArrayList<>();
    public final Set<JSModifyCallback> jsPostCallbacks = new HashSet<>();
    public final Set<JSONModifyCallback> jsonPostCallbacks = new HashSet<>();

    public LootModifier() {}

    public LootModifier lock()
    {
        this.locked = true;
        return this;
    }

    public boolean isLocked()
    {
        return this.locked;
    }

    @Nullable public LootPool createNewPool()
    {
        return createNewPool(1);
    }
    
    @Nullable public LootPool createNewPool(int rolls)
    {
        if(this.locked) return null;
        LootPool pool = new LootPool(this);
        try {
            pool.obj.put("rolls", rolls);
        } catch(JSONException ex) {}
        this.pools.add(pool);
        return pool;
    }

    @Nullable public LootPool createNewPool(int minRolls, int maxRolls)
    {
        if(this.locked) return null;
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
        if(this.locked) return this;
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
        if(this.locked) return this;
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
        if(this.locked) return this;
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
        if(this.locked) return this;
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
        if(this.locked) return this;
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
        if(this.locked) return this;
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
        if(this.locked) return this;
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
        if(this.locked) return this;
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
        if(this.locked) return this;
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
        if(this.locked) return this;
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

    public LootModifier addJSModifyCallback(JSModifyCallback cb)
    {
        return this.addJSModifyCallback(cb, 0);
    }

    public LootModifier addJSModifyCallback(JSModifyCallback cb, int priority)
    {
        if(this.locked) return this;
        CallbackFunction.addToList(new CallbackFunction<JSModifyCallback>(cb, priority), this.jsCallbacks);
        return this;
    }

    public LootModifier addJSONModifyCallback(JSONModifyCallback cb)
    {
        return this.addJSONModifyCallback(cb, 0);
    }

    public LootModifier addJSONModifyCallback(JSONModifyCallback cb, int priority)
    {
        if(this.locked) return this;
        CallbackFunction.addToList(new CallbackFunction<JSONModifyCallback>(cb, priority), this.jsonCallbacks);
        return this;
    }

    public LootModifier addJSPostModifyCallback(JSModifyCallback cb)
    {
        if(this.locked) return this;
        this.jsPostCallbacks.add(cb);
        return this;
    }

    public LootModifier addJSONPostModifyCallback(JSONModifyCallback cb)
    {
        if(this.locked) return this;
        this.jsonPostCallbacks.add(cb);
        return this;
    }

    public void serialize(JSONObject obj)
    {
        try {
            JSONArray poolsArray = JsonUtils.getOrCreateArray(obj, "pools");
            this.pools.forEach(pool -> poolsArray.put(pool.obj));
        } catch(JSONException ex) {}
        if(!this.jsonCallbacks.isEmpty())
        {
            this.jsonCallbacks.forEach(cb -> cb.function.onModify(obj));
        }
        if(!this.jsCallbacks.isEmpty())
        {
            ScriptableObject scr = CommonTypes.jsonToScriptable(obj);
            this.jsCallbacks.forEach(cb -> cb.function.onModify(scr));
            JSONObject modifiedObj = CommonTypes.scriptableToJson(scr);
            try {
                obj.remove("pools");
                obj.put("pools", modifiedObj.getJSONArray("pools"));
            } catch (JSONException e) {}
        }
        if(!this.jsonPostCallbacks.isEmpty())
        {
            this.jsonPostCallbacks.forEach(cb -> {
                try {
                    cb.onModify(new JSONObject(obj.toString()));
                } catch(JSONException ex) { ex.printStackTrace(); }
            });
        }
        if(!this.jsPostCallbacks.isEmpty())
        {
            this.jsPostCallbacks.forEach(cb -> cb.onModify(CommonTypes.jsonToScriptable(obj)));
        }
    }

}
