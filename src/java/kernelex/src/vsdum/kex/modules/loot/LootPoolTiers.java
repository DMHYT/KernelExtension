package vsdum.kex.modules.loot;

import org.json.JSONException;
import org.json.JSONObject;

import vsdum.kex.util.JsonUtils;

public class LootPoolTiers {
    
    public final LootPool pool;
    public final JSONObject obj;

    public LootPoolTiers(LootPool pool)
    throws JSONException
    {
        this.pool = pool;
        this.obj = JsonUtils.getOrCreateObject(this.pool.obj, "tiers");
    }

    public LootPoolTiers setBonusChance(float bonusChance)
    {
        try {
            this.obj.put("bonus_chance", bonusChance);
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolTiers setBonusRolls(int bonusRolls)
    {
        try {
            this.obj.put("bonus_rolls", bonusRolls);
        } catch(JSONException ex) {}
        return this;
    }

    public LootPoolTiers setInitialRange(int range)
    {
        try {
            this.obj.put("initial_range", range);
        } catch(JSONException ex) {}
        return this;
    }

    public LootPool endTiers()
    {
        return this.pool;
    }

}
