package vsdum.kex.modules.loot;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import vsdum.kex.common.IJSONSerializable;
import vsdum.kex.util.CommonTypes;
import vsdum.kex.util.JsonUtils;

public class LootConditions implements IJSONSerializable {
    
    @Nullable public LootPool pool = null;
    public final JSONArray arr;

    public LootConditions()
    {
        this.arr = new JSONArray();
    }

    public LootConditions(LootPool pool)
    throws JSONException
    {
        this.pool = pool;
        this.arr = JsonUtils.getOrCreateArray(pool.obj, "conditions");
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

    public LootConditions addEntityOnFireCondition(boolean onFire)
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "entity_properties")
                .put("properties", new JSONObject()
                    .put("on_fire", onFire)));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addEntityOnGroundCondition(boolean onGround)
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "entity_properties")
                .put("properties", new JSONObject()
                    .put("on_ground", onGround)));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addEntityPropertiesCondition(boolean onFire, boolean onGround)
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

    public LootConditions addMarkVariantCondition(int markVariant)
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "has_mark_variant")
                .put("value", markVariant));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addKilledByPlayerCondition()
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "killed_by_player"));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addKilledByPlayerOrPetsCondition()
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "killed_by_player_or_pets"));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addRandomChanceCondition(float chance)
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "random_chance")
                .put("chance", chance));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addRandomChanceCondition(float chance, float maxChance)
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "random_chance")
                .put("chance", chance)
                .put("max_chance", maxChance));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addRandomChanceWithLootingCondition(float chance, float lootingMultiplier)
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "random_chance_with_looting")
                .put("chance", chance)
                .put("looting_multiplier", lootingMultiplier));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addRandomDifficultyChanceCondition(float defaultChance)
    {
        return addRandomDifficultyChanceCondition(defaultChance, defaultChance);
    }

    public LootConditions addRandomDifficultyChanceCondition(float defaultChance, float easy)
    {
        return addRandomDifficultyChanceCondition(defaultChance, easy, defaultChance);
    }

    public LootConditions addRandomDifficultyChanceCondition(float defaultChance, float easy, float normal)
    {
        return addRandomDifficultyChanceCondition(defaultChance, easy, normal, defaultChance);
    }

    public LootConditions addRandomDifficultyChanceCondition(float defaultChance, float easy, float normal, float hard)
    {
        return addRandomDifficultyChanceCondition(defaultChance, easy, normal, hard, defaultChance);
    }

    public LootConditions addRandomDifficultyChanceCondition(float defaultChance, float easy, float normal, float hard, float peaceful)
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
    
    public LootConditions addRandomRegionalDifficultyChanceCondition(float maxChance)
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "random_regional_difficulty_chance")
                .put("max_chance", maxChance));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addCustomCondition(String conditionName, JSONObject json)
    {
        try {
            if(json.optString("condition") != conditionName) json.put("condition", conditionName);
            this.arr.put(json);
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addCustomCondition(String conditionName, ScriptableObject json)
    {
        return this.addCustomCondition(conditionName, CommonTypes.scriptableToJson(json));
    }

    public LootConditions addANDCondition(LootConditions clauses)
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "and")
                .put("clauses", clauses.arr));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addORCondition(LootConditions clauses)
    {
        try {
            this.arr.put(new JSONObject()
                .put("condition", "or")
                .put("clauses", clauses.arr));
        } catch(JSONException ex) {}
        return this;
    }

    public LootConditions addNOTCondition(LootConditions clause)
    {
        if(clause.arr.length() == 0) return this;
        try {
            JSONObject clauseJSON = clause.arr.length() == 1 ?
                clause.arr.getJSONObject(0) :
                new JSONObject()
                    .put("condition", "and")
                    .put("clauses", clause.arr);
            this.arr.put(new JSONObject()
                .put("condition", "not")
                .put("clause", clauseJSON));
        } catch(JSONException ex) {}
        return this;
    }

    public LootPool endConditions()
    {
        if(this.pool == null)
            throw new IllegalStateException("The following loot table conditions object can\'t return its LootPool, because it was created without it!");
        return this.pool;
    }

}
