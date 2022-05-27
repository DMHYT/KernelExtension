package vsdum.kex.modules.tools;

import java.util.HashMap;
import java.util.Map;

import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import vsdum.kex.modules.ToolsModule.ItemTier;

public class DataSets {
    
    public static final Map<String, ItemTier> tiersByName = new HashMap<>();

    static {
        long[] vanillaTiers = ToolsNativeAPI.nativeGrabVanillaItemTiers();
        tiersByName.put("wood", new ItemTier(vanillaTiers[0]));
        tiersByName.put("stone", new ItemTier(vanillaTiers[1]));
        tiersByName.put("iron", new ItemTier(vanillaTiers[2]));
        tiersByName.put("diamond", new ItemTier(vanillaTiers[3]));
        ItemTier gold = new ItemTier(vanillaTiers[4]);
        tiersByName.put("gold", gold);
        tiersByName.put("golden", gold);
        tiersByName.put("netherite", new ItemTier(vanillaTiers[5]));
    }

    public static final Map<String, Float> materialNameToBreakingMultiplier = new HashMap<>();

    static {
        materialNameToBreakingMultiplier.put("stone", Float.valueOf(10/3));
        materialNameToBreakingMultiplier.put("wood", Float.valueOf(1.0f));
        materialNameToBreakingMultiplier.put("dirt", Float.valueOf(1.0f));
        materialNameToBreakingMultiplier.put("plant", Float.valueOf(1.0f));
        materialNameToBreakingMultiplier.put("fibre", Float.valueOf(1.0f));
        materialNameToBreakingMultiplier.put("cobweb", Float.valueOf(10/3));
        materialNameToBreakingMultiplier.put("unbreaking", Float.valueOf(999999999));
    }

    public static final class BlockData {

        @Nullable public final String materialName;
        public final int destroyLevel;
        public final boolean isNative;

        public BlockData(@Nullable String materialName, int destroyLevel, boolean isNative)
        {
            this.materialName = materialName;
            this.destroyLevel = destroyLevel;
            this.isNative = isNative;
        }
        
    }

    public static final Map<Integer, ScriptableObject> toolData = new HashMap<>();

    public static boolean isWeapon(int id) {
        ScriptableObject obj = toolData.get(Integer.valueOf(id));
        if(ScriptableObject.hasProperty(obj, "isWeapon"))
        {
            Object isWeapon = ScriptableObject.getProperty(obj, "isWeapon");
            if(isWeapon instanceof Boolean)
            {
                return ((Boolean) isWeapon).booleanValue();
            }
        }
        return false;
    }
    
}
