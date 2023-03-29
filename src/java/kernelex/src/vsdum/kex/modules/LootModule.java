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
import vsdum.kex.util.SetBuilder;

public class LootModule {

    private static native void enableOnDropCallbackFor(String table);
    protected static native void nativeFillContainer(long bsPtr, int x, int y, int z, String tableName, long actorPtr);
    protected static native long nativeGetRandomItems(String tableName, long contextPtr);
    protected static native int nativeGetVectorSize(long vectorPtr);
    protected static native void nativeDeleteVector(long vectorPtr);
    protected static native void nativeForceLoad(String tableName);
    protected static native void nativeNewCustomLootFunction(String functionName);
    protected static native void nativeModifyStack(long stackPointer, int id, int count, int data, long extra);

    public static interface OnDropCallback {
        public void onDrop(RandomItemsList drops, LootTableContext context);
    }

    public static interface CustomLootFunctionCallback {
        public void apply(JSONObject json, ItemStack stack, LootTableContext context);
    }

    public static interface CustomLootFunctionCallbackJS {
        public void apply(ScriptableObject json, ItemStack stack, LootTableContext context);
    }
    
    private static final Map<String, LootModifier> modifiers = new HashMap<>();
    private static final List<LootPoolEntry> piglinBarteringItems = new ArrayList<>();
    private static final Map<String, List<CallbackFunction<OnDropCallback>>> onDropCallbacks = new HashMap<>();
    private static final Set<Integer> supportedFillingContainers = new SetBuilder<Integer>().add(0).add(2).add(13).add(14).add(42).build();
    private static final Set<String> forceLoaded = new HashSet<>();
    private static final Map<String, CustomLootFunctionCallback> customLootFunctions = new HashMap<>();
    private static final Map<String, CustomLootFunctionCallbackJS> customLootFunctionsJS = new HashMap<>();

    public static final LootModifier createLootTableModifier(String tableName)
    {
        String tableDir = validateTableName(tableName);
        modifiers.putIfAbsent(tableDir, new LootModifier());
        return modifiers.get(tableDir);
    }

    public static final LootConditions createConditionsList()
    {
        return new LootConditions();
    }

    public static void addOnDropCallbackFor(String tableName, OnDropCallback cb)
    {
        addOnDropCallbackFor(tableName, cb, 0);
    }

    public static void addOnDropCallbackFor(String tableName, OnDropCallback cb, int priority)
    {
        String tableDir = validateTableName(tableName);
        enableOnDropCallbackFor(tableDir);
        onDropCallbacks.putIfAbsent(tableDir, new ArrayList<>());
        CallbackFunction.addToList(new CallbackFunction<OnDropCallback>(cb, priority), onDropCallbacks.get(tableDir));
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

    public static final LootPoolEntry addPiglinBarteringItem()
    {
        LootPoolEntry entry = new LootPoolEntry(null, new JSONObject());
        piglinBarteringItems.add(entry);
        return entry;
    }

    public static void forceLoad(String tableName)
    {
        String tableDir = validateTableName(tableName);
        if(NativeCallback.isLevelDisplayed()) nativeForceLoad(tableDir);
        forceLoaded.add(tableDir);
    }

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

    static {
        createLootTableModifier("entities/piglin_barter")
            .addJSONModifyCallback(obj -> {
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
            });
        forceLoad("entities/piglin_barter");
    }

    @Nullable public static String modify(String tableDir, String json)
    {
        if(!modifiers.containsKey(tableDir))
        {
            return null;
        } else try {
            JSONObject obj = new JSONObject(json);
            modifiers.get(tableDir).serialize(obj);
            return obj.toString();
        } catch(JSONException ex) {
            return null;
        }
    }

    public static void onDrop(String tableDir, long vectorPtr, int vectorSize, long contextPtr)
    {
        if(onDropCallbacks.containsKey(tableDir))
        {
            RandomItemsList drops = new RandomItemsList(vectorPtr, vectorSize);
            LootTableContext context = new LootTableContext(contextPtr);
            Iterator<CallbackFunction<OnDropCallback>> iter = onDropCallbacks.get(tableDir).iterator();
            while(iter.hasNext()) iter.next().function.onDrop(drops, context);
            drops.modifyNative();
        }
    }

    public static void onLevelDisplayed()
    {
        if(!forceLoaded.isEmpty())
        {
            long start = System.currentTimeMillis();
            Logger.debug("KEX-LootModule", String.format("The level has been displayed, force loading %d loot tables...", new Object[]{ Integer.valueOf(forceLoaded.size()) }));
            Iterator<String> iter = forceLoaded.iterator();
            while(iter.hasNext()) nativeForceLoad(iter.next());
            Logger.debug("KEX-LootModule", String.format("Finished in %d ms!", new Object[]{ Long.valueOf(System.currentTimeMillis() - start) }));
        } else Logger.debug("KEX-LootModule", "The level has been displayed, no loot tables to force load.");
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

    private static boolean validatePiglinBarteringEntry(LootPoolEntry entry)
    {
        if(entry == null) return false;
        if(!entry.obj.has("name"))
        {
            Logger.warning("[KEX-LootModule] One of the added piglin bartering entries has no item name ID specified. This entry is being skipped! (TIP: The item name ID can be specified using entry.describeItem method)");
            return false;
        }
        if(!entry.obj.has("weight"))
        {
            Logger.warning(String.format("[KEX-LootModule] The piglin bartering entry with name ID \"%s\" has no weight specified. This entry is being skipped! (TIP: The item weight is the value that is used in weighted random logics when the item from piglin bartering process is being chosen. The larger this value, the greater the chance for this item to be dropped. In vanilla piglin bartering items list, weight values vary from 1 (netherite hoe) to 40 (gravel, leather, nether brick etc.). The item weight can be specified using entry.setWeight method)", new Object[]{ entry.obj.optString("name") }));
            return false;
        }
        return true;
    }

    private static String validateTableName(String tableName)
    {
        String result = tableName;
        if(!result.startsWith("loot_tables/")) result = "loot_tables/" + result;
        if(!result.endsWith(".json")) result = result + ".json";
        if(!result.matches("^loot_tables/[\\w_-]+/[\\w/_-]+.json$"))
            throw new IllegalArgumentException("Invalid loot table dir: " + tableName);
        return result;
    }

}
