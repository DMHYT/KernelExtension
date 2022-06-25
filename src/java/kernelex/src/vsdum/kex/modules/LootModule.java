package vsdum.kex.modules;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.NativeCallback;
import com.zhekasmirnov.innercore.api.NativeTileEntity;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import vsdum.kex.common.CallbackFunction;
import vsdum.kex.modules.loot.LootConditions;
import vsdum.kex.modules.loot.LootModifier;
import vsdum.kex.modules.loot.LootPoolEntry;
import vsdum.kex.modules.loot.RandomItemsList;
import vsdum.kex.natives.Actor;
import vsdum.kex.natives.LootTableContext;
import vsdum.kex.util.CommonTypes;

public class LootModule {

    private static native void enableOnDropCallbackFor(String table);
    protected static native void nativeFillContainer(long bsPtr, int x, int y, int z, String tableName, long actorPtr);
    protected static native long nativeGetRandomItems(String tableName, long contextPtr);
    protected static native int nativeGetVectorSize(long vectorPtr);
    protected static native void nativeDeleteVector(long vectorPtr);
    protected static native void nativeForceLoad(String tableName);
    protected static native void nativeNewCustomLootFunction(String functionName);
    protected static native void nativeModifyStack(long stackPointer, int id, int count, int data, long extra);
    
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
                    if(!piglinBarteringItems.isEmpty())
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

    public static interface OnDropCallback {
        public void onDrop(RandomItemsList drops, LootTableContext context);
    }

    private static final Map<String, List<CallbackFunction<OnDropCallback>>> onDropCallbacks = new HashMap<>();

    public static void addOnDropCallbackFor(String tableName, OnDropCallback cb)
    {
        addOnDropCallbackFor(tableName, cb, 0);
    }

    public static void addOnDropCallbackFor(String tableName, OnDropCallback cb, int priority)
    {
        enableOnDropCallbackFor(tableName);
        if(!onDropCallbacks.containsKey(tableName)) onDropCallbacks.put(tableName, new ArrayList<>());
        CallbackFunction.addToList(new CallbackFunction<OnDropCallback>(cb, priority), onDropCallbacks.get(tableName));
    }

    public static void onDrop(String tableName, long vectorPtr, int vectorSize, long contextPtr)
    {
        if(onDropCallbacks.containsKey(tableName))
        {
            RandomItemsList drops = new RandomItemsList(vectorPtr, vectorSize);
            LootTableContext context = new LootTableContext(contextPtr);
            Iterator<CallbackFunction<OnDropCallback>> iter = onDropCallbacks.get(tableName).iterator();
            while(iter.hasNext()) iter.next().function.onDrop(drops, context);
            drops.modifyNative();
        }
    }

    private static final List<Integer> supportedFillingContainers = new ArrayList<>();

    static {
        supportedFillingContainers.add(0);
        supportedFillingContainers.add(2);
        supportedFillingContainers.add(13);
        supportedFillingContainers.add(14);
        supportedFillingContainers.add(42);
    }

    private static String validateTableName(String tableName)
    {
        String result = tableName;
        if(!result.startsWith("loot_tables/")) result = "loot_tables/" + result;
        if(!result.startsWith("loot_tables/chests/") && !result.startsWith("loot_tables/entities/"))
            throw new IllegalArgumentException("Loot table name must be [loot_tables/](chests|entities)/{path and name}[.json]");
        if(!result.endsWith(".json")) result += ".json";
        if(!result.matches("^loot_tables/(chests|entities)/([\\w-/]+).json$"))
            throw new IllegalArgumentException("NOT MATCHING REGEX: Loot table name must be [loot_tables/](chests|entities)/{path and name}[.json]");
        return result;
    }

    public static void fillContainer(NativeBlockSource region, int x, int y, int z, String tableName, @Nullable Actor actor)
    {
        NativeTileEntity tile = region.getBlockEntity(x, y, z);
        if(tile != null && supportedFillingContainers.contains(tile.getType()))
        {
            String tableDir = validateTableName(tableName);
            nativeFillContainer(region.getPointer(), x, y, z, tableDir, actor != null ? actor.getPointer() : 0L);
        } else throw new IllegalStateException(String.format("Cannot fill container on %d %d %d, because the tile entity %s!", new Object[]{ Integer.valueOf(x), Integer.valueOf(y), Integer.valueOf(z), tile == null ? "is null" : "is not of supported type" }));
    }

    public static List<ItemStack> getRandomItems(String tableName, LootTableContext context)
    {
        String tableDir = validateTableName(tableName);
        List<ItemStack> result = new ArrayList<>();
        long vectorPtr = nativeGetRandomItems(tableDir, context.getPointer());
        if(vectorPtr != 0L)
        {
            RandomItemsList list = new RandomItemsList(vectorPtr, nativeGetVectorSize(vectorPtr));
            result.addAll(list);
            nativeDeleteVector(vectorPtr);
        }
        return result;
    }

    private static final Set<String> forceLoaded = new HashSet<>();

    public static void forceLoad(String tableName)
    {
        String tableDir = validateTableName(tableName);
        if(NativeCallback.isLevelDisplayed()) nativeForceLoad(tableDir);
        if(!forceLoaded.contains(tableName)) forceLoaded.add(tableDir);
    }

    public static void onLevelDisplayed()
    {
        if(!forceLoaded.isEmpty())
        {
            long start = System.currentTimeMillis();
            Logger.debug("KEX", String.format("The level has been displayed, force loading %d loot tables...", new Object[]{ Integer.valueOf(forceLoaded.size()) }));
            Iterator<String> iter = forceLoaded.iterator();
            while(iter.hasNext()) nativeForceLoad(iter.next());
            Logger.debug("KEX", String.format("Finished in %d ms!", new Object[]{ Long.valueOf(System.currentTimeMillis() - start) }));
        } else Logger.debug("KEX", "The level has been displayed, no loot tables to force load.");
    }

    public static interface CustomLootFunctionCallback {
        public void apply(JSONObject json, ItemStack stack, LootTableContext context);
    }

    public static interface CustomLootFunctionCallbackJS {
        public void apply(ScriptableObject json, ItemStack stack, LootTableContext context);
    }

    private static final Map<String, CustomLootFunctionCallback> customLootFunctions = new HashMap<>();
    private static final Map<String, CustomLootFunctionCallbackJS> customLootFunctionsJS = new HashMap<>();

    public static void registerCustomLootFunction(String functionName, CustomLootFunctionCallback callback)
    {
        customLootFunctions.put(functionName, callback);
        nativeNewCustomLootFunction(functionName);
    }

    public static void registerCustomLootFunctionJS(String functionName, CustomLootFunctionCallbackJS callback)
    {
        customLootFunctionsJS.put(functionName, callback);
        nativeNewCustomLootFunction(functionName);
    }

    public static void applyCustomLootFunction(String functionName, String jsonString, long stackPointer, long contextPointer)
    {
        ItemStack stack = ItemStack.fromPtr(stackPointer);
        LootTableContext context = new LootTableContext(contextPointer);
        try {
            if(customLootFunctions.containsKey(functionName))
            {
                customLootFunctions.get(functionName).apply(new JSONObject(jsonString), stack, context);
            } else if(customLootFunctionsJS.containsKey(functionName)) {
                customLootFunctionsJS.get(functionName).apply(CommonTypes.jsonToScriptable(new JSONObject(jsonString)), stack, context);
            }
        } catch(JSONException ex) { ex.printStackTrace(); }
        nativeModifyStack(stackPointer, stack.id, stack.count, stack.data, stack.extra == null ? 0L : stack.extra.getValue());
    }

}
