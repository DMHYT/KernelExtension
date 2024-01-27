package vsdum.kex.modules.tools;

import java.util.HashMap;
import java.util.Map;

import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;

import android.support.annotation.Nullable;
import vsdum.kex.modules.ToolsModule.ItemTier;
import vsdum.kex.util.MapBuilder;

public class DataSets {
    
    private static final long[] vanillaTierPointers = ToolsNativeAPI.nativeGrabVanillaItemTiers();
    public static final Map<String, ItemTier> tiersByName = new MapBuilder<String, ItemTier>()
        .add("wood", new ItemTier(vanillaTierPointers[0]))
        .add("stone", new ItemTier(vanillaTierPointers[1]))
        .add("iron", new ItemTier(vanillaTierPointers[2]))
        .add("diamond", new ItemTier(vanillaTierPointers[3]))
        .add("gold", new ItemTier(vanillaTierPointers[4]))
        .add("golden", new ItemTier(vanillaTierPointers[4]))
        .add("netherite", new ItemTier(vanillaTierPointers[5]))
        .build();

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

    public static boolean isWeapon(int id)
    {
        return toolData.containsKey(id) ? ScriptableObjectHelper.getBooleanProperty(toolData.get(id), "isWeapon", false) : false;
    }
    
}
