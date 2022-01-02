package vsdum.kex.common;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.IDRegistry;
import com.zhekasmirnov.innercore.utils.FileTools;

import org.json.JSONObject;

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
                    Integer numericId = Integer.valueOf(obj.getInt(stringId));
                    if(!vanillaNumericToStringIdMap.containsKey(numericId))
                    {
                        vanillaNumericToStringIdMap.put(numericId, stringId);
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
            return vanillaNumericToStringIdMap.get(Integer.valueOf(id));
        } else return "minecraft:" + NativeAPI.convertNameId(IDRegistry.getNameByID(id));
    }

    public static String getAddonItemIdentifier(String namespace, String identifier)
    {
        return namespace + ":" + identifier;
    }

}
