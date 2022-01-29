package vsdum.kex.modules;

import java.util.HashMap;
import java.util.Map;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.NativeItemInstance;
import com.zhekasmirnov.innercore.api.commontypes.Coords;
import com.zhekasmirnov.innercore.api.commontypes.FullBlock;
import com.zhekasmirnov.innercore.api.commontypes.ItemInstance;
import com.zhekasmirnov.innercore.api.constants.Enchantment;

import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;
import vsdum.kex.util.CommonTypes;

public class ToolsModule {

    protected static native long[] nativeGrabVanillaItemTiers();
    protected static native long nativeNewItemTier(int level, int uses, float speed, int attackDamageBonus, int enchantmentValue);
    protected static native int nativeGetItemTierLevel(long ptr);
    protected static native int nativeGetItemTierUses(long ptr);
    protected static native float nativeGetItemTierSpeed(long ptr);
    protected static native int nativeGetItemTierAttackDamageBonus(long ptr);
    protected static native int nativeGetItemTierEnchantmentValue(long ptr);
    protected static native void nativeRegisterSword(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    protected static native void nativeRegisterAxe(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    protected static native void nativeRegisterPickaxe(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    protected static native void nativeRegisterShovel(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    protected static native void nativeRegisterHoe(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    public static native float getBlockDestroyTime(int id);
    @Nullable protected static native String nativeGetBlockMaterialName(int id);
    protected static native int nativeGetBlockDestroyLevel(int id);
    protected static native boolean nativeGetBlockIsNative(int id);
    protected static native void nativeSetBlockMaterialName(int id, String materialName);
    protected static native void nativeSetBlockDestroyLevel(int id, int destroyLevel);
    protected static native void nativeSetBlockIsNative(int id, boolean isNative);
    protected static native Object nativeGetBlockData(int id);
    protected static native void nativeSetBlockData(int id, String materialName, int destroyLevel, boolean isNative);
    public static native int getToolLevel(int id);
    public static native int getToolLevelViaBlock(int itemID, int blockID);
    protected static native void nativeRegisterCustomTool(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech, boolean isWeapon, String[] blockMaterials, int brokenId, int baseAttackDamage, int enchantType);
    protected static native float nativeGetDestroyTimeViaTool(int id, int data, long stackptr, int x, int y, int z, int side);

    private static final Map<String, ItemTier> tiersByName = new HashMap<>();

    static {
        long[] vanillaTiers = nativeGrabVanillaItemTiers();
        tiersByName.put("wood", new ItemTier(vanillaTiers[0]));
        tiersByName.put("stone", new ItemTier(vanillaTiers[1]));
        tiersByName.put("iron", new ItemTier(vanillaTiers[2]));
        tiersByName.put("diamond", new ItemTier(vanillaTiers[3]));
        ItemTier gold = new ItemTier(vanillaTiers[4]);
        tiersByName.put("gold", gold);
        tiersByName.put("golden", gold);
        tiersByName.put("netherite", new ItemTier(vanillaTiers[5]));
    }

    @Nullable public static final ItemTier getTierByName(String name)
    {
        if(!tiersByName.containsKey(name)) return null;
        return tiersByName.get(name);
    }

    public static class ItemTier implements INativeInterface {

        protected final long pointer;

        public final long getPointer()
        {
            return this.pointer;
        }

        public ItemTier(String name, int level, int uses, float speed, int attackDamageBonus, int enchantmentValue)
        {
            if(tiersByName.containsKey(name))
                throw new IllegalArgumentException("Item tier with name " + name + " has already been registered! Consider using another name!");
            this.pointer = nativeNewItemTier(level, uses, speed, attackDamageBonus, enchantmentValue);
            tiersByName.put(name, this);
        }

        private ItemTier(long ptr)
        {
            this.pointer = ptr;
        }

        public final int getLevel()
        {
            return nativeGetItemTierLevel(this.pointer);
        }

        public final int getUses()
        {
            return nativeGetItemTierUses(this.pointer);
        }

        public final float getSpeed()
        {
            return nativeGetItemTierSpeed(this.pointer);
        }

        public final int getAttackDamageBonus()
        {
            return nativeGetItemTierAttackDamageBonus(this.pointer);
        }

        public final int getEnchantmentValue()
        {
            return nativeGetItemTierEnchantmentValue(this.pointer);
        }

    }

    public static void registerSword(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerSword(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier, true);
    }

    public static void registerSword(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterSword(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerAxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerAxe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier, true);
    }

    public static void registerAxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterAxe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerPickaxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerPickaxe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier, true);
    }

    public static void registerPickaxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterPickaxe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerShovel(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerShovel(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier, true);
    }

    public static void registerShovel(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterShovel(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerHoe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerHoe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier, true);
    }

    public static void registerHoe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterHoe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    private static final Map<String, Float> materialNameToBreakingMultiplier = new HashMap<>();

    /** --- --- --- BACKWARD COMPATIBILITY --- --- --- */

    static {
        materialNameToBreakingMultiplier.put("stone", Float.valueOf(10/3));
        materialNameToBreakingMultiplier.put("wood", Float.valueOf(1.0f));
        materialNameToBreakingMultiplier.put("dirt", Float.valueOf(1.0f));
        materialNameToBreakingMultiplier.put("plant", Float.valueOf(1.0f));
        materialNameToBreakingMultiplier.put("fibre", Float.valueOf(1.0f));
        materialNameToBreakingMultiplier.put("cobweb", Float.valueOf(10/3));
        materialNameToBreakingMultiplier.put("unbreaking", Float.valueOf(999999999));
    }

    public static void addBlockMaterial(String name, float breakingMultiplier)
    {
        if(!materialNameToBreakingMultiplier.containsKey(name))
        {
            materialNameToBreakingMultiplier.put(name, Float.valueOf(breakingMultiplier));
        }
    }

    public static float getBlockMaterialBreakingMultiplier(String name)
    {
        if(!materialNameToBreakingMultiplier.containsKey(name)) return 0.0f;
        return materialNameToBreakingMultiplier.get(name).floatValue();
    }
     
    /** ---------------------------------------------- */

    public static class BlockData {
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

    public static BlockData getBlockData(int blockID)
    {
        return (BlockData) nativeGetBlockData(blockID);
    }

    @Nullable public static String getBlockMaterialName(int blockID)
    {
        return nativeGetBlockMaterialName(blockID);
    }

    public static int getBlockDestroyLevel(int blockID)
    {
        return nativeGetBlockDestroyLevel(blockID);
    }

    public static boolean getBlockIsNative(int blockID)
    {
        return nativeGetBlockIsNative(blockID);
    }

    public static void setBlockData(int blockID, String materialName, int destroyLevel, boolean isNative)
    {
        nativeSetBlockData(blockID, materialName, destroyLevel, isNative);
    }

    public static void setBlockMaterialName(int blockID, String materialName)
    {
        nativeSetBlockMaterialName(blockID, materialName);
    }

    public static void setBlockDestroyLevel(int blockID, int destroyLevel)
    {
        nativeSetBlockDestroyLevel(blockID, destroyLevel);
    }

    public static void setBlockIsNative(int blockID, boolean isNative)
    {
        nativeSetBlockIsNative(blockID, isNative);
    }

    public static float getDestroyTimeViaTool(FullBlock block, int x, int y, int z, int side, NativeItemInstance stack)
    {
        return nativeGetDestroyTimeViaTool(block.id, block.data, stack.getPointer(), x, y, z, side);
    }

    private static final Map<Integer, ScriptableObject> toolData = new HashMap<>();

    public static float calcDestroyTime(long stackPtr, int id, int data, int x, int y, int z, byte side, float baseDestroyTime, float divider, float modifier, float defaultTime)
    {
        try {
            ItemStack stack = ItemStack.fromPtr(stackPtr);
            if(stack != null)
            {
                Integer idO = Integer.valueOf(stack.id);
                if(toolData.containsKey(idO))
                {
                    ScriptableObject obj = toolData.get(idO);
                    if(ScriptableObject.hasProperty(obj, "calcDestroyTime"))
                    {
                        return CommonTypes.callFloatJSFunction(obj, "calcDestroyTime", new Object[]{
                            new Coords(x, y, z, side),
                            new FullBlock(id, data),
                            CommonTypes.createTimeDataScriptable(baseDestroyTime, divider, modifier),
                            Float.valueOf(defaultTime),
                            CommonTypes.createEnchantDataScriptable(stack)
                        }, defaultTime);
                    }
                }
            }
        } catch(Throwable ex) {
            ex.printStackTrace();
        }
        return defaultTime;
    }

    public static boolean onDestroy(long stackPtr, int x, int y, int z, byte side, int id, int data, long player)
    {
        try {
            ItemStack stack = ItemStack.fromPtr(stackPtr);
            if(stack != null)
            {
                Integer idO = Integer.valueOf(stack.id);
                if(toolData.containsKey(idO))
                {
                    ScriptableObject obj = toolData.get(idO);
                    if(ScriptableObject.hasProperty(obj, "onDestroy"))
                    {
                        return CommonTypes.callBooleanJSFunction(obj, "onDestroy", new Object[]{
                            new ItemInstance(stack.id, stack.count, stack.data, stack.extra),
                            new Coords(x, y, z, side),
                            new FullBlock(id, data),
                            Long.valueOf(player)
                        }, false);
                    }
                }
            }
        } catch(Throwable ex) {
            ex.printStackTrace();
        }
        return false;
    }

    public static boolean onAttack(long stackPtr, long victim, long attacker)
    {
        try {
            ItemStack stack = ItemStack.fromPtr(stackPtr);
            if(stack != null)
            {
                Integer idO = Integer.valueOf(stack.id);
                if(toolData.containsKey(idO))
                {
                    ScriptableObject obj = toolData.get(idO);
                    if(ScriptableObject.hasProperty(obj, "onAttack"))
                    {
                        return CommonTypes.callBooleanJSFunction(obj, "onAttack", new Object[]{
                            new ItemInstance(stack.id, stack.count, stack.data, stack.extra),
                            Long.valueOf(victim), Long.valueOf(attacker)
                        }, false);
                    }
                }
            }
        } catch(Throwable ex) {
            ex.printStackTrace();
        }
        return false;
    }

    public static boolean onBroke(long stackPtr)
    {
        try {
            ItemStack stack = ItemStack.fromPtr(stackPtr);
            if(stack != null)
            {
                Integer idO = Integer.valueOf(stack.id);
                if(toolData.containsKey(idO))
                {
                    ScriptableObject obj = toolData.get(idO);
                    if(ScriptableObject.hasProperty(obj, "onBroke"))
                    {
                        return CommonTypes.callBooleanJSFunction(obj, "onBroke", new Object[]{
                            new ItemInstance(stack.id, stack.count, stack.data, stack.extra)
                        }, false);
                    }
                }
            }
        } catch(Throwable ex) {
            ex.printStackTrace();
        }
        return false;
    }

    public static void modifyEnchant(long stackPtr, int x, int y, int z, byte side, int id, int data)
    {
        try {
            ItemStack stack = ItemStack.fromPtr(stackPtr);
            if(stack != null)
            {
                int idO = Integer.valueOf(stack.id);
                if(toolData.containsKey(idO))
                {
                    ScriptableObject obj = toolData.get(idO);
                    if(ScriptableObject.hasProperty(obj, "modifyEnchant"))
                    {
                        ScriptableObject enchantData = CommonTypes.createEnchantDataScriptable(stack);
                        CommonTypes.callVoidJSFunction(obj, "modifyEnchant", new Object[]{
                            enchantData,
                            new ItemInstance(stack.id, stack.count, stack.data, stack.extra),
                            new Coords(x, y, z, side),
                            new FullBlock(id, data)
                        });
                        short[] modified = CommonTypes.enchantDataScriptableToArray(enchantData);
                        stack.extra.addEnchant(Enchantment.SILK_TOUCH, modified[0]);
                        stack.extra.addEnchant(Enchantment.FORTUNE, modified[1]);
                        stack.extra.addEnchant(Enchantment.EFFICIENCY, modified[2]);
                        stack.extra.addEnchant(Enchantment.UNBREAKING, modified[3]);
                    }
                }
            }
        } catch(Throwable ex) {
            ex.printStackTrace();
        }
    }

    public static void onMineBlock(long stackPtr, int x, int y, int z, byte side, int id, int data)
    {
        try {
            ItemStack stack = ItemStack.fromPtr(stackPtr);
            if(stack != null)
            {
                int idO = Integer.valueOf(stack.id);
                if(toolData.containsKey(idO))
                {
                    ScriptableObject obj = toolData.get(idO);
                    if(ScriptableObject.hasProperty(obj, "onMineBlock"))
                    {
                        CommonTypes.callVoidJSFunction(obj, "onMineBlock", new Object[]{
                            new Coords(x, y, z, side),
                            new ItemInstance(stack.id, stack.count, stack.data, stack.extra),
                            new FullBlock(id, data)
                        });
                    }
                }
            }
        } catch(Throwable ex) {
            ex.printStackTrace();
        }
    }

    public static void registerCustomTool(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech, boolean isWeapon, String[] blockMaterials, int brokenId, int baseAttackDamage, int enchantType, ScriptableObject data)
    {
        nativeRegisterCustomTool(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech, isWeapon, blockMaterials, brokenId, baseAttackDamage, enchantType);
        toolData.put(Integer.valueOf(id), data);
    }

}
