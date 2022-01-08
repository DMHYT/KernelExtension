package vsdum.kex.modules;

import java.util.HashMap;
import java.util.Map;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.NativeItemInstance;
import com.zhekasmirnov.innercore.api.commontypes.Coords;
import com.zhekasmirnov.innercore.api.commontypes.FullBlock;
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
    public static native int getToolLevelViaBlock(int id);
    protected static native void nativeRegisterCustomTool(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech, boolean isWeapon, String[] blockMaterials, int brokenId, int baseAttackDamage);
    protected static native float nativeGetDestroyTimeViaTool(int id, int data, long stackptr, int x, int y, int z, int side);

    private static final Map<String, ItemTier> tiersByName = new HashMap<>();

    static {
        long[] vanillaTiers = nativeGrabVanillaItemTiers();
        tiersByName.put("wood", new ItemTier(vanillaTiers[0]));
        tiersByName.put("stone", new ItemTier(vanillaTiers[1]));
        tiersByName.put("iron", new ItemTier(vanillaTiers[2]));
        tiersByName.put("diamond", new ItemTier(vanillaTiers[3]));
        tiersByName.put("gold", new ItemTier(vanillaTiers[4]));
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
        registerSword(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerSword(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterSword(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerAxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerAxe(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerAxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterAxe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerPickaxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerPickaxe(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerPickaxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterPickaxe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerShovel(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerShovel(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerShovel(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterShovel(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerHoe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerHoe(id, nameId, name, textureName, textureMeta, tier, true);
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

    @Nullable public static Integer getBlockDestroyLevel(int blockID)
    {
        return (Integer) nativeGetBlockDestroyLevel(blockID);
    }

    @Nullable public static Boolean getBlockIsNative(int blockID)
    {
        return (Boolean) nativeGetBlockIsNative(blockID);
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

    public static interface CalcDestroyTimeFunction {
        public float calc(ItemStack stack, Coords itemUseCoords, FullBlock block, ScriptableObject timeData, float defaultTime, ScriptableObject enchantData);
    }

    public static interface OnDestroyFunction {
        public boolean onDestroy(ItemStack stack, Coords itemUseCoords, FullBlock block, long player);
    }

    public static interface OnAttackFunction {
        public boolean onAttack(ItemStack stack, long victim, long attacker);
    }

    public static interface OnBrokeFunction {
        public boolean onBroke(ItemStack stack);
    }

    public static interface ModifyEnchantFunction {
        public void modify(ScriptableObject enchantData, ItemStack stack, Coords itemUseCoords, FullBlock block);
    }

    public static interface OnMineBlockFunction {
        public void onMine(Coords itemUseCoords, ItemStack carried, FullBlock block);
    }

    private static final Map<Integer, CalcDestroyTimeFunction> calcDestroyTimeCallbacks = new HashMap<>();
    private static final Map<Integer, OnDestroyFunction> onDestroyCallbacks = new HashMap<>();
    private static final Map<Integer, OnAttackFunction> onAttackCallbacks = new HashMap<>();
    private static final Map<Integer, OnBrokeFunction> onBrokeCallbacks = new HashMap<>();
    private static final Map<Integer, ModifyEnchantFunction> modifyEnchantCallbacks = new HashMap<>();
    private static final Map<Integer, OnMineBlockFunction> onMineBlockCallbacks = new HashMap<>();

    public static void addCalcDestroyTimeCallback(int id, CalcDestroyTimeFunction func) { calcDestroyTimeCallbacks.put(Integer.valueOf(id), func); }
    public static void addOnDestroyCallback(int id, OnDestroyFunction func) { onDestroyCallbacks.put(Integer.valueOf(id), func); }
    public static void addOnAttackCallback(int id, OnAttackFunction func) { onAttackCallbacks.put(Integer.valueOf(id), func); }
    public static void addOnBrokeCallback(int id, OnBrokeFunction func) { onBrokeCallbacks.put(Integer.valueOf(id), func); }
    public static void addModifyEnchantCallback(int id, ModifyEnchantFunction func) { modifyEnchantCallbacks.put(Integer.valueOf(id), func); }
    public static void addOnMineBlockCallback(int id, OnMineBlockFunction func) { onMineBlockCallbacks.put(Integer.valueOf(id), func); }

    public static float calcDestroyTime(long stackPtr, int id, int data, int x, int y, int z, byte side, float baseDestroyTime, float divider, float modifier, float defaultTime)
    {
        ItemStack stack = ItemStack.fromPtr(stackPtr);
        if(stack != null)
        {
            Integer idO = Integer.valueOf(stack.id);
            if(calcDestroyTimeCallbacks.containsKey(idO))
            {
                return calcDestroyTimeCallbacks.get(idO).calc(stack, new Coords(x, y, z, side), new FullBlock(id, data), CommonTypes.createTimeDataScriptable(baseDestroyTime, divider, modifier), defaultTime, CommonTypes.createEnchantDataScriptable(stack));
            }
        }
        return defaultTime;
    }

    public static boolean onDestroy(long stackPtr, int x, int y, int z, int side, int id, int data, long player)
    {
        ItemStack stack = ItemStack.fromPtr(stackPtr);
        if(stack != null)
        {
            Integer idO = Integer.valueOf(stack.id);
            if(onDestroyCallbacks.containsKey(idO))
            {
                return onDestroyCallbacks.get(idO).onDestroy(stack, new Coords(x, y, z, side), new FullBlock(id, data), player);
            }
        }
        return false;
    }

    public static boolean onAttack(long stackPtr, long victim, long attacker)
    {
        ItemStack stack = ItemStack.fromPtr(stackPtr);
        if(stack != null)
        {
            Integer idO = Integer.valueOf(stack.id);
            if(onAttackCallbacks.containsKey(idO))
            {
                return onAttackCallbacks.get(idO).onAttack(stack, victim, attacker);
            }
        }
        return false;
    }

    public static boolean onBroke(long stackPtr)
    {
        ItemStack stack = ItemStack.fromPtr(stackPtr);
        if(stack != null)
        {
            Integer idO = Integer.valueOf(stack.id);
            if(onBrokeCallbacks.containsKey(idO))
            {
                return onBrokeCallbacks.get(idO).onBroke(stack);
            }
        }
        return false;
    }

    public static void modifyEnchant(long stackPtr, int x, int y, int z, byte side, int id, int data)
    {
        ItemStack stack = ItemStack.fromPtr(stackPtr);
        if(stack != null)
        {
            int idO = Integer.valueOf(stack.id);
            if(modifyEnchantCallbacks.containsKey(idO))
            {
                ScriptableObject enchantData = CommonTypes.createEnchantDataScriptable(stack);
                modifyEnchantCallbacks.get(idO).modify(enchantData, stack, new Coords(x, y, z, side), new FullBlock(id, data));
                short[] modified = CommonTypes.enchantDataScriptableToArray(enchantData);
                stack.extra.addEnchant(Enchantment.SILK_TOUCH, modified[0]);
                stack.extra.addEnchant(Enchantment.FORTUNE, modified[1]);
                stack.extra.addEnchant(Enchantment.EFFICIENCY, modified[2]);
                stack.extra.addEnchant(Enchantment.UNBREAKING, modified[3]);
            }
        }
    }

    public static void onMineBlock(long stackPtr, int x, int y, int z, byte side, int id, int data)
    {
        ItemStack stack = ItemStack.fromPtr(stackPtr);
        if(stack != null)
        {
            int idO = Integer.valueOf(stack.id);
            if(onMineBlockCallbacks.containsKey(idO))
            {
                onMineBlockCallbacks.get(idO).onMine(new Coords(x, y, z, side), stack, new FullBlock(id, data));
            }
        }
    }

    public static void registerCustomTool(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech, boolean isWeapon, String[] blockMaterials, int brokenId, int baseAttackDamage)
    {
        nativeRegisterCustomTool(id, nameId, name, textureName, textureMeta, tier.getPointer(), isTech, isWeapon, blockMaterials, brokenId, baseAttackDamage);
    }

}
