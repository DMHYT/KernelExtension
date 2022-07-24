package vsdum.kex.modules.loot;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;

import vsdum.kex.util.CommonTypes;
import vsdum.kex.util.JsonUtils;

public class LootPoolEntryFunctions {
    
    public final LootPoolEntry entry;

    public LootPoolEntryFunctions(LootPoolEntry entry)
    {
        this.entry = entry;
        try {
            JsonUtils.getOrCreateArray(this.entry.obj, "functions");
        } catch(JSONException ex) {}
    }

    public LootPoolEntryFunctions addEnchantBookForTradingFunction(int baseCost, int baseRandomCost, int perLevelCost, int perLevelRandomCost)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "enchant_book_for_trading")
                    .put("base_cost", baseCost)
                    .put("base_random_cost", baseRandomCost)
                    .put("per_level_cost", perLevelCost)
                    .put("per_level_random_cost", perLevelRandomCost));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addEnchantRandomGearFunction()
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "enchant_random_gear"));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addEnchantRandomGearFunction(float chance)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "enchant_random_gear")
                    .put("chance", chance));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addEnchantRandomlyFunction()
    {
        return addEnchantRandomlyFunction(false);
    }

    public LootPoolEntryFunctions addEnchantRandomlyFunction(boolean treasure)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "enchant_randomly")
                    .put("treasure", true));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addEnchantWithLevelsFunction(int levels)
    {
        return addEnchantWithLevelsFunction(levels, false);
    }

    public LootPoolEntryFunctions addEnchantWithLevelsFunction(int levels, boolean treasure)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "enchant_with_levels")
                    .put("levels", levels)
                    .put("treasure", treasure));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addEnchantWithLevelsFunction(int minLevels, int maxLevels)
    {
        return addEnchantWithLevelsFunction(minLevels, maxLevels, false);
    }

    public LootPoolEntryFunctions addEnchantWithLevelsFunction(int minLevels, int maxLevels, boolean treasure)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "enchant_with_levels")
                    .put("levels", new JSONObject()
                        .put("min", minLevels)
                        .put("max", maxLevels))
                    .put("treasure", treasure));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addExplorationMapFunction(String destination)
    {
        try {
            this.entry.obj.getJSONArray("functions")
            .put(new JSONObject()
                .put("function", "exploration_map")
                .put("destination", destination));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addFillContainerFunction(String lootTable)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "fill_container")
                    .put("loot_table", lootTable));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addFurnaceSmeltFunction()
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "furnace_smelt"));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addFurnaceSmeltFunction(LootConditions conditions)
    {
        try {
            JSONObject functionObj = new JSONObject()
                .put("function", "furnace_smelt");
            conditions.serialize(functionObj);
            this.entry.obj.getJSONArray("functions").put(functionObj);
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addLootingEnchantFunction()
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "looting_enchant"));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addLootingEnchantFunction(int minCount, int maxCount)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "looting_enchant")
                    .put("count", new JSONObject()
                        .put("min", minCount)
                        .put("max", maxCount)));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addRandomAuxValueFunction()
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "random_aux_value"));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addRandomAuxValueFunction(int minValue, int maxValue)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "random_aux_value")
                    .put("values", new JSONObject()
                        .put("min", minValue)
                        .put("max", maxValue)));
        } catch(JSONException ex) {}
        return this;
    }

    // TODO manage with random_block_state and banner details

    public LootPoolEntryFunctions addRandomDyeFunction()
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "random_dye"));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addActorIdFunction(String actorId)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "set_actor_id")
                    .put("id", actorId));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addBookContentsFunction(String author, String title, String[] pages)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "set_book_contents")
                    .put("author", author)
                    .put("title", title)
                    .put("pages", new JSONArray(Arrays.asList(pages))));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addDataFromColorIndexFunction()
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "set_data_from_color_index"));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addLoreFunction(String[] lore)
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "set_lore")
                    .put("lore", new JSONArray(Arrays.asList(lore))));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addSpecificEnchantsFunction(ScriptableObject enchants)
    {
        Map<String, Integer> map = new HashMap<>();
        Object[] keys = enchants.getAllIds();
        for(int i = 0; i < keys.length; i++)
        {
            Object key = keys[i];
            if(key instanceof String)
            {
                String name = (String) key;
                int level = ScriptableObjectHelper.getIntProperty(enchants, name, -1);
                if(level != -1) map.put(name, level);
            }
        }
        return this.addSpecificEnchantsFunction(map);
    }

    public LootPoolEntryFunctions addSpecificEnchantsFunction(Map<String, Integer> enchants)
    {
        try {
            JSONArray enchantsArray = new JSONArray();
            Iterator<String> iter = enchants.keySet().iterator();
            while(iter.hasNext())
            {
                String id = iter.next();
                enchantsArray.put(new JSONObject()
                    .put("id", id)
                    .put("level", enchants.get(id).intValue()));
            }
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "specific_enchants")
                    .put("enchants", enchantsArray));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addTraderMaterialTypeFunction()
    {
        try {
            this.entry.obj.getJSONArray("functions")
                .put(new JSONObject()
                    .put("function", "trader_material_type"));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addCustomFunction(String functionName, JSONObject json)
    {
        try {
            if(json.optString("function") != functionName) json.put("function", functionName);
            this.entry.obj.getJSONArray("functions").put(json);
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolEntryFunctions addCustomFunction(String functionName, ScriptableObject json)
    {
        return this.addCustomFunction(functionName, CommonTypes.scriptableToJson(json));
    }

    public LootPoolEntry endFunctions()
    {
        return this.entry;
    }

}
