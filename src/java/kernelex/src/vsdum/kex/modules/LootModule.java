package vsdum.kex.modules;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import com.zhekasmirnov.innercore.utils.FileTools;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import android.util.Pair;
import vsdum.kex.common.IJSONSerializable;
import vsdum.kex.util.AddonUtils;
import vsdum.kex.util.CommonTypes;
import vsdum.kex.util.JsonUtils;

public class LootModule {
    
    private static final Map<String, LootModifier> modifiers = new HashMap<>();

    @Nullable public static String modify(String tableName, String json)
    {
        if(!modifiers.containsKey(tableName))
        {
            return null;
        } else try {
            JSONObject obj = new JSONObject(json);
            modifiers.get(tableName).serialize(obj);
            return obj.toString();
        } catch(JSONException ex) {
            return null;
        }
    }

    public static class LootModifier implements IJSONSerializable {

        private final List<LootPool> pools = new ArrayList<>();

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

        public static class LootPool {

            private final JSONObject obj = new JSONObject();
            private final LootModifier modifier;

            public LootPool(LootModifier modifier)
            {
                this.modifier = modifier;
                try {
                    this.obj.put("entries", new JSONArray());
                } catch(JSONException ex) {}
            }

            public Conditions beginConditions()
            {
                try {
                    JsonUtils.getOrCreateArray(this.obj, "conditions");
                } catch(JSONException ex) { return null; } // mustn't happen
                return new Conditions(this);
            }

            public static class Conditions implements IJSONSerializable {

                @Nullable private LootPool pool = null;
                private final JSONArray arr = new JSONArray();

                public Conditions() {}

                public Conditions(LootPool pool)
                {
                    this.pool = pool;
                }

                public void serialize(JSONObject obj)
                {
                    try {
                        JSONArray conditionsArray = JsonUtils.getOrCreateArray(obj, "conditions");
                        for(int i = 0; i < this.arr.length(); i++)
                        {
                            conditionsArray.put(this.arr.get(i));
                        }
                    } catch(JSONException ex) {}
                }

                public Conditions addEntityOnFireCondition(boolean onFire)
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "entity_properties")
                            .put("properties", new JSONObject()
                                .put("on_fire", onFire)));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addEntityOnGroundCondition(boolean onGround)
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "entity_properties")
                            .put("properties", new JSONObject()
                                .put("on_ground", onGround)));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addEntityPropertiesCondition(boolean onFire, boolean onGround)
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "entity_properties")
                            .put("properties", new JSONObject()
                                .put("on_fire", onFire)
                                .put("on_ground", onGround)));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addMarkVariantCondition(int markVariant)
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "has_mark_variant")
                            .put("value", markVariant));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addKilledByPlayerCondition()
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "killed_by_player"));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addKilledByPlayerOrPetsCondition()
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "killed_by_player_or_pets"));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addRandomChanceCondition(float chance)
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "random_chance")
                            .put("chance", chance));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addRandomChanceCondition(float chance, float maxChance)
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "random_chance")
                            .put("chance", chance)
                            .put("max_chance", maxChance));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addRandomChanceWithLootingCondition(float chance, float lootingMultiplier)
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "random_chance_with_looting")
                            .put("chance", chance)
                            .put("looting_multiplier", lootingMultiplier));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addRandomDifficultyChanceCondition(float defaultChance)
                {
                    return addRandomDifficultyChanceCondition(defaultChance, defaultChance);
                }

                public Conditions addRandomDifficultyChanceCondition(float defaultChance, float easy)
                {
                    return addRandomDifficultyChanceCondition(defaultChance, easy, defaultChance);
                }

                public Conditions addRandomDifficultyChanceCondition(float defaultChance, float easy, float normal)
                {
                    return addRandomDifficultyChanceCondition(defaultChance, easy, normal, defaultChance);
                }

                public Conditions addRandomDifficultyChanceCondition(float defaultChance, float easy, float normal, float hard)
                {
                    return addRandomDifficultyChanceCondition(defaultChance, easy, normal, hard, defaultChance);
                }

                public Conditions addRandomDifficultyChanceCondition(float defaultChance, float easy, float normal, float hard, float peaceful)
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "random_difficulty_chance")
                            .put("default_chance", defaultChance)
                            .put("easy", easy)
                            .put("normal", normal)
                            .put("hard", hard)
                            .put("peaceful", peaceful));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Conditions addRandomRegionalDifficultyChanceCondition(float defaultChance)
                {
                    return addRandomRegionalDifficultyChanceCondition(defaultChance, defaultChance);
                }

                public Conditions addRandomRegionalDifficultyChanceCondition(float defaultChance, float easy)
                {
                    return addRandomRegionalDifficultyChanceCondition(defaultChance, easy, defaultChance);
                }

                public Conditions addRandomRegionalDifficultyChanceCondition(float defaultChance, float easy, float normal)
                {
                    return addRandomRegionalDifficultyChanceCondition(defaultChance, easy, normal, defaultChance);
                }

                public Conditions addRandomRegionalDifficultyChanceCondition(float defaultChance, float easy, float normal, float hard)
                {
                    return addRandomRegionalDifficultyChanceCondition(defaultChance, easy, normal, hard, defaultChance);
                }

                public Conditions addRandomRegionalDifficultyChanceCondition(float defaultChance, float easy, float normal, float hard, float peaceful)
                {
                    try {
                        this.arr.put(new JSONObject()
                            .put("condition", "random_regional_difficulty_chance")
                            .put("default_chance", defaultChance)
                            .put("easy", easy)
                            .put("normal", normal)
                            .put("hard", hard)
                            .put("peaceful", peaceful));
                    } catch(JSONException ex) {}
                    return this;
                }

                public LootPool endConditions()
                {
                    if(this.pool == null)
                        throw new IllegalStateException("The following loot table conditions object can\'t return its LootPool, because it was created without it!");
                    this.serialize(this.pool.obj);
                    return this.pool;
                }

            }

            public Tiers beginTiers()
            {
                return new Tiers(this);
            }

            public static class Tiers implements IJSONSerializable {
                
                @Nullable private LootPool pool = null;
                private final JSONObject obj = new JSONObject();

                public Tiers() {}

                public Tiers(LootPool pool)
                {
                    this.pool = pool;
                }

                public void serialize(JSONObject obj)
                {
                    try {
                        if(obj.has("tiers")) obj.remove("tiers");
                        obj.put("tiers", this.obj);
                    } catch(JSONException ex) {}
                }

                public Tiers setBonusChance(float bonusChance)
                {
                    try {
                        this.obj.put("bonus_chance", bonusChance);
                    } catch(JSONException ex) {}
                    return this;
                }

                public Tiers setBonusRolls(int bonusRolls)
                {
                    try {
                        this.obj.put("bonus_rolls", bonusRolls);
                    } catch(JSONException ex) {}
                    return this;
                }

                public Tiers setInitialRange(int range)
                {
                    try {
                        this.obj.put("initial_range", range);
                    } catch(JSONException ex) {}
                    return this;
                }

                public LootPool endTiers()
                {
                    if(this.pool == null)
                        throw new IllegalStateException("The following loot table conditions object can\'t return its LootPool, because it was created without it!");
                    this.serialize(this.pool.obj);
                    return this.pool;
                }

            }

            public Entry addEntry()
            {
                try {
                    JsonUtils.getOrCreateArray(this.obj, "entries");
                } catch(JSONException ex) { return null; }
                return new Entry(this);
            }

            public static class Entry {
                
                private final LootPool pool;
                private final JSONObject obj = new JSONObject();

                public Entry(LootPool pool)
                {
                    this.pool = pool;
                    try {
                        this.obj.put("type", "item");
                    } catch(JSONException ex) {}
                }

                public Entry describeItem(String namespace, String identifier)
                {
                    try {
                        this.obj.put("name", AddonUtils.getAddonItemIdentifier(namespace, identifier));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Entry describeItem(int numericId)
                {
                    try {
                        this.obj.put("name", AddonUtils.getAddonItemIdentifier(numericId));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Entry setCount(int count)
                {
                    try {
                        this.obj.put("count", count);
                    } catch(JSONException ex) {}
                    return this;
                }

                public Entry setCount(int min, int max)
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

                public Entry setData(int data)
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

                public Entry setData(int min, int max)
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

                public Entry setDamage(int damage)
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

                public Entry setDamage(int min, int max)
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

                public Entry setCustomName(String name)
                {
                    try {
                        JsonUtils.getOrCreateArray(this.obj, "functions")
                            .put(new JSONObject()
                                .put("function", "set_name")
                                .put("name", name));
                    } catch(JSONException ex) {}
                    return this;
                }

                public Entry setWeight(int weight)
                {
                    try {
                        this.obj.put("weight", weight);
                    } catch(JSONException ex) {}
                    return this;
                }

                public Entry setQuality(int quality)
                {
                    try {
                        this.obj.put("quality", quality);
                    } catch(JSONException ex) {}
                    return this;
                }

                public Functions beginFunctions()
                {
                    try {
                        JsonUtils.getOrCreateArray(this.obj, "functions");
                    } catch(JSONException ex) {}
                    return new Functions(this);
                }

                public static class Functions {

                    private final Entry entry;

                    public Functions(Entry entry)
                    {
                        this.entry = entry;
                    }

                    public Functions addEnchantBookForTradingFunction(int baseCost, int baseRandomCost, int perLevelCost, int perLevelRandomCost)
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

                    public Functions addEnchantRandomGearFunction()
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "enchant_random_gear"));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addEnchantRandomGearFunction(float chance)
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "enchant_random_gear")
                                    .put("chance", chance));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addEnchantRandomlyFunction()
                    {
                        return addEnchantRandomlyFunction(false);
                    }

                    public Functions addEnchantRandomlyFunction(boolean treasure)
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "enchant_randomly")
                                    .put("treasure", true));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addEnchantWithLevelsFunction(int levels)
                    {
                        return addEnchantWithLevelsFunction(levels, false);
                    }

                    public Functions addEnchantWithLevelsFunction(int levels, boolean treasure)
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

                    public Functions addEnchantWithLevelsFunction(int minLevels, int maxLevels)
                    {
                        return addEnchantWithLevelsFunction(minLevels, maxLevels, false);
                    }

                    public Functions addEnchantWithLevelsFunction(int minLevels, int maxLevels, boolean treasure)
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

                    public Functions addExplorationMapFunction(String destination)
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                            .put(new JSONObject()
                                .put("function", "exploration_map")
                                .put("destination", destination));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addFillContainerFunction(String lootTable)
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "fill_container")
                                    .put("loot_table", lootTable));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addFurnaceSmeltFunction()
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "furnace_smelt"));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addFurnaceSmeltFunction(Conditions conditions)
                    {
                        try {
                            JSONObject functionObj = new JSONObject()
                                .put("function", "furnace_smelt");
                            conditions.serialize(functionObj);
                            this.entry.obj.getJSONArray("functions").put(functionObj);
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addLootingEnchantFunction()
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "looting_enchant"));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addLootingEnchantFunction(int minCount, int maxCount)
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

                    public Functions addRandomAuxValueFunction()
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "random_aux_value"));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addRandomAuxValueFunction(int minValue, int maxValue)
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

                    // TODO manage with random_block_state

                    public Functions addRandomDyeFunction()
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "random_dye"));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addActorIdFunction(String actorId)
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "set_actor_id")
                                    .put("id", actorId));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addBannerDetailsFunction(int type)
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "set_banner_details")
                                    .put("type", type));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addBookContentsFunction(String author, String title, String[] pages)
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

                    public Functions addDataFromColorIndexFunction()
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "set_data_from_color_index"));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addLoreFunction(String[] lore)
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "set_lore")
                                    .put("lore", new JSONArray(Arrays.asList(lore))));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Functions addSpecificEnchantsFunction(Map<String, Integer> enchants)
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

                    public Functions addTraderMaterialTypeFunction()
                    {
                        try {
                            this.entry.obj.getJSONArray("functions")
                                .put(new JSONObject()
                                    .put("function", "trader_material_type"));
                        } catch(JSONException ex) {}
                        return this;
                    }

                    public Entry endFunctions()
                    {
                        return this.entry;
                    }

                }

                public LootPool endEntry()
                {
                    try {
                        this.pool.obj.getJSONArray("entries").put(this.obj);
                    } catch(JSONException ex) {}
                    return this.pool;
                }
                
            }

            public LootModifier endPool()
            {
                return this.modifier;
            }

        }

    }

    public static final LootModifier createLootTableModifier(String tableName)
    {
        if(modifiers.containsKey(tableName))
        {
            return modifiers.get(tableName);
        } else {
            LootModifier modifier = new LootModifier();
            modifiers.put(tableName, modifier);
            return modifier;
        }
    }

    public static final LootModifier.LootPool.Conditions createConditionsList()
    {
        return new LootModifier.LootPool.Conditions();
    }

}
