package vsdum.kex.modules;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.support.annotation.Nullable;
import vsdum.kex.modules.loot.LootConditions;
import vsdum.kex.modules.loot.LootModifier;
import vsdum.kex.modules.loot.LootPoolEntry;

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

    private static final List<LootPoolEntry> piglinBarteringItems = new ArrayList<>();

    public static final LootPoolEntry addPiglinBarteringItem()
    {
        LootPoolEntry entry = new LootPoolEntry(null, new JSONObject());
        piglinBarteringItems.add(entry);
        return entry;
    }

    private static boolean validatePiglinBarteringEntry(LootPoolEntry entry)
    {
        if(entry == null) return false;
        if(!entry.obj.has("name"))
        {
            Logger.warning("One of the added piglin bartering entries has no item name ID specified. This entry is being skipped! (TIP: The item name ID can be specified using entry.describeItem method)");
            return false;
        }
        if(!entry.obj.has("weight"))
        {
            Logger.warning(String.format("The piglin bartering entry with name ID \"%s\" has no weight specified. This entry is being skipped! (TIP: The item weight is the value that is used in weighted random logics when the item from piglin bartering process is being chosen. The larger this value, the greater the chance for this item to be dropped. In vanilla piglin bartering items list, weight values vary from 1 (netherite hoe) to 40 (gravel, leather, nether brick etc.). The item weight can be specified using entry.setWeight method)", new Object[]{ entry.obj.optString("name") }));
            return false;
        }
        return true;
    }

    static {
        createLootTableModifier("entities/piglin_barter")
            .addJSONModifyCallback(new LootModifier.JSONModifyCallback() {
                public void onModify(JSONObject obj)
                {
                    if(piglinBarteringItems.size() > 0)
                    {
                        try {
                            JSONArray entriesArray = obj.getJSONArray("pools")
                                .getJSONObject(0)
                                .getJSONArray("entries");
                            for(int i = 0; i < piglinBarteringItems.size(); ++i)
                            {
                                LootPoolEntry entry = piglinBarteringItems.get(i);
                                if(validatePiglinBarteringEntry(entry))
                                {
                                    entriesArray.put(entry.obj);
                                }
                            }
                        } catch(JSONException ex) {}
                    }
                }
            });
    }

}
