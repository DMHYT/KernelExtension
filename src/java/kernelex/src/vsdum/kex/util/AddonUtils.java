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
                    vanillaNumericToStringIdMap.putIfAbsent(numericId, stringId);
                }
            }
        } catch(Throwable ex) {}
    }

    static {
        parseVanillaIdsFrom("numeric_ids.json");
        for(String filePath : FileTools.listDirectory(FileTools.DIR_PACK + "/assets/innercore/id/"))
        {
            if(filePath.matches("^numeric_ids_override_[0-9]{1,}.json$"))
            {
                parseVanillaIdsFrom(filePath);
            }
        }
    }
    
    public static String getAddonItemIdentifier(int id)
    {
        return IDRegistry.isVanilla(id) ? "minecraft:" + vanillaNumericToStringIdMap.get(id) : "minecraft:" + NativeAPI.convertNameId(IDRegistry.getNameByID(id));
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
            return vanillaNumericToStringIdMap.getOrDefault(id, null);
        } else return NativeAPI.convertNameId(IDRegistry.getNameByID(id));
    }

    private static final Map<String, Integer> identifierToNumeric = new HashMap<>();

    @SuppressWarnings("unchecked") public static void onModsLoaded()
    {
        new MapBuilder<String, String>()
            .add("vanillaIdShortcut", "")
            .add("blockIdShortcut", "block_")
            .add("itemIdShortcut", "block_")
            .build()
            .forEach((fieldName, prefix) -> {
                try {
                    Field field = com.zhekasmirnov.innercore.api.unlimited.IDRegistry.class.getDeclaredField(fieldName);
                    field.setAccessible(true);
                    ((HashMap<String, Integer>) field.get(null))
                        .forEach((stringID, numericID) -> identifierToNumeric.put(prefix + NativeAPI.convertNameId(stringID), numericID));
                } catch(Throwable ex) {}
            });
        Callback.invokeAPICallback("KEX-InnerCoreIdsCached", new Object[]{});
    }

    public static int getNumericIdFromIdentifier(String identifier)
    {
        String identifierWithoutNamespace = identifier.startsWith("minecraft:") ? identifier.substring(10) : identifier;
        return identifierToNumeric.getOrDefault(identifierWithoutNamespace, -1);
    }

}
