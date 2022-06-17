package vsdum.kex.util;

import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.IDRegistry;
import com.zhekasmirnov.innercore.api.runtime.Callback;
import com.zhekasmirnov.innercore.utils.FileTools;

import org.json.JSONObject;

import android.support.annotation.Nullable;
import vsdum.kex.modules.LootModule;

public final class AddonUtils {

    private static final Map<Integer, String> vanillaNumericToStringIdMap = new HashMap<>();

    private static void parseVanillaIdsFrom(String fileName)
    {
        try {
            JSONObject idsJson = FileTools.readJSON(FileTools.DIR_PACK + "/assets/innercore/id/" + fileName);
            Iterator<String> keysIter = idsJson.keys();
            while(keysIter.hasNext())
            {
                String key = keysIter.next();
                JSONObject obj = idsJson.getJSONObject(key);
                Iterator<String> idsIter = obj.keys();
                while(idsIter.hasNext())
                {
                    String stringId = idsIter.next();
                    int numericId = obj.getInt(stringId);
                    if(key.equals("blocks") && numericId > 255)
                    {
                        numericId = 255 - numericId;
                    }
                    Integer numericIdO = Integer.valueOf(numericId);
                    if(!vanillaNumericToStringIdMap.containsKey(numericIdO))
                    {
                        vanillaNumericToStringIdMap.put(numericIdO, stringId);
                    }
                }
            }
        } catch(Exception ex) {}
    }

    static {
        parseVanillaIdsFrom("numeric_ids.json");
        String[] files = FileTools.listDirectory(FileTools.DIR_PACK + "/assets/innercore/id/");
        for(int i = 0; i < files.length; ++i)
        {
            String filePath = files[i];
            if(filePath.matches("^numeric_ids_override_[0-9]{1,}.json$"))
            {
                parseVanillaIdsFrom(filePath);
            }
        }
    }
    
    public static String getAddonItemIdentifier(int id)
    {
        if(IDRegistry.isVanilla(id))
        {
            return "minecraft:" + vanillaNumericToStringIdMap.get(Integer.valueOf(id));
        } else return "minecraft:" + NativeAPI.convertNameId(IDRegistry.getNameByID(id));
    }

    public static String getAddonItemIdentifier(String namespace, String identifier)
    {
        return namespace + ":" + identifier;
    }

    @Nullable public static String getBlockNameId(int id)
    {
        if(IDRegistry.isVanilla(id))
        {
            if(id > 255) id = 255 - id;
            Integer idO = Integer.valueOf(id);
            if(!vanillaNumericToStringIdMap.containsKey(idO)) return null;
            return vanillaNumericToStringIdMap.get(idO);
        } else return NativeAPI.convertNameId(IDRegistry.getNameByID(id));
    }

    private static final HashMap<String, Integer> vanillaIdShortcut = getVanillaIdShortcut();

    @SuppressWarnings("unchecked")
    private static final HashMap<String, Integer> getVanillaIdShortcut()
    {
        try {
            Field field = com.zhekasmirnov.innercore.api.unlimited.IDRegistry.class.getDeclaredField("vanillaIdShortcut");
            field.setAccessible(true);
            return (HashMap<String, Integer>) field.get(null);
        } catch(Throwable ex) {}
        return null;
    }

    private static final Map<String, Integer> innercoreIdentifierToNumeric = new HashMap<>();

    public static void onLevelDisplayed()
    {
        try {
            JSONObject json = FileTools.readJSON(FileTools.DIR_PACK + "/innercore/mods/.staticids").getJSONObject("id");
            JSONObject blocks = json.getJSONObject("blocks");
            JSONObject items = json.getJSONObject("items");
            Iterator<String> blocksIter = blocks.keys();
            Iterator<String> itemsIter = items.keys();
            while(blocksIter.hasNext())
            {
                String k = blocksIter.next();
                innercoreIdentifierToNumeric.put("block_" + NativeAPI.convertNameId(k), blocks.getInt(k));
            }
            while(itemsIter.hasNext())
            {
                String k = itemsIter.next();
                innercoreIdentifierToNumeric.put("item_" + NativeAPI.convertNameId(k), items.getInt(k));
            }
            Callback.invokeAPICallback("KEX-InnerCoreIdsCached", new Object[]{});
        } catch(Throwable ex) {}
        LootModule.onLevelDisplayed();
    }

    public static int getNumericIdFromIdentifier(String identifier)
    {
        if(vanillaIdShortcut.containsKey(identifier)) return vanillaIdShortcut.get(identifier);
        if(innercoreIdentifierToNumeric.containsKey(identifier)) return innercoreIdentifierToNumeric.get(identifier);
        return -1;
    }

}
