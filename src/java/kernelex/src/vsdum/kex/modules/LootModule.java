package vsdum.kex.modules;

import java.util.HashMap;
import java.util.Map;

import org.json.JSONException;
import org.json.JSONObject;

import android.support.annotation.Nullable;
import vsdum.kex.modules.loot.LootConditions;
import vsdum.kex.modules.loot.LootModifier;

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

    public static final LootConditions createConditionsList()
    {
        return new LootConditions();
    }

}
