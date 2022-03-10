package vsdum.kex.modules;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.NativeItemInstance;
import com.zhekasmirnov.innercore.api.NativeItemInstanceExtra;
import com.zhekasmirnov.innercore.api.commontypes.Coords;
import com.zhekasmirnov.innercore.api.commontypes.FullBlock;
import com.zhekasmirnov.innercore.api.commontypes.ItemInstance;
import com.zhekasmirnov.innercore.api.constants.Enchantment;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Entity;

import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import android.util.Pair;
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
    public static native void enableDynamicDamageFor(int id);
    protected static native void nativeDamageToolInHand(long player, int damage);
    protected static native void nativeRegisterShears(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech, int durabilityIfWithoutTier);

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

    private static Random rand = new Random();

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

    public static void registerShears(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerShears(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerShears(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        nativeRegisterShears(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech, 0);
    }

    public static void registerShears(int id, String nameId, String name, String textureName, int textureMeta, int durability)
    {
        registerShears(id, nameId, name, textureName, textureMeta, durability, true);
    }

    public static void registerShears(int id, String nameId, String name, String textureName, int textureMeta, int durability, boolean isTech)
    {
        nativeRegisterShears(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, 0L, isTech, durability);
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

    public static float getDestroyTimeViaTool(Object tile, int x, int y, int z, int side, NativeItemInstance stack)
    {
        Pair<Integer, Integer> block = CommonTypes.deserializeFullBlockOrBlockState(tile);
        if(block == null) return 0.0f;
        return nativeGetDestroyTimeViaTool(block.first.intValue(), block.second.intValue(), stack.getPointer(), x, y, z, side);
    }

    private static final Map<Integer, ScriptableObject> toolData = new HashMap<>();

    private static boolean isWeapon(int id) {
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

    public static float calcDestroyTime(int id, int data, int x, int y, int z, byte side, float baseDestroyTime, float divider, float modifier, float defaultTime)
    {
        ItemInstance stack = Entity.getCarriedItem(NativeAPI.getLocalPlayer());
        Integer idO = Integer.valueOf(stack.getId());
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
                    CommonTypes.createEnchantDataScriptable(new ItemStack(stack))
                }, defaultTime);
            }
        }
        return defaultTime;
    }

    public static boolean onDestroy(Coords coords, ItemInstance item, Object tile, long player)
    {
        Pair<Integer, Integer> block = CommonTypes.deserializeFullBlockOrBlockState(tile);
        if(block == null) return false;
        Integer idO = Integer.valueOf(item.getId());
        if(toolData.containsKey(idO))
        {
            ScriptableObject obj = toolData.get(idO);
            if(ScriptableObject.hasProperty(obj, "onDestroy"))
            {
                boolean result = CommonTypes.callBooleanJSFunction(obj, "onDestroy", new Object[]{
                    item, coords, new FullBlock(block.first.intValue(), block.second.intValue()), Long.valueOf(player)
                }, false);
                Entity.setCarriedItem(player, item.getId(), item.getCount(), item.getData(), CommonTypes.getExtraFromInstance(item));
                return result;
            }
        }
        return false;
    }

    public static boolean onAttack(long victim, long attacker, ItemInstance item)
    {
        Integer idO = Integer.valueOf(item.getId());
        if(toolData.containsKey(idO))
        {
            ScriptableObject obj = toolData.get(idO);
            if(ScriptableObject.hasProperty(obj, "onAttack"))
            {
                boolean result = CommonTypes.callBooleanJSFunction(obj, "onAttack", new Object[]{
                    item, Long.valueOf(victim), Long.valueOf(attacker)
                }, false);
                Entity.setCarriedItem(attacker, item.getId(), item.getCount(), item.getData(), CommonTypes.getExtraFromInstance(item));
                return result;
            }
        }
        return false;
    }

    public static boolean onBroke()
    {
        ItemInstance stack = Entity.getCarriedItem(NativeAPI.getLocalPlayer());
        Integer idO = Integer.valueOf(stack.getId());
        if(toolData.containsKey(idO))
        {
            ScriptableObject obj = toolData.get(idO);
            if(ScriptableObject.hasProperty(obj, "onBroke"))
            {
                return CommonTypes.callBooleanJSFunction(obj, "onBroke", new Object[]{ stack }, false);
            }
        }
        return false;
    }

    public static void modifyEnchant(Coords coords, ItemInstance item, Object tile, long player)
    {
        Pair<Integer, Integer> block = CommonTypes.deserializeFullBlockOrBlockState(tile);
        if(block != null)
        {
            Integer idO = Integer.valueOf(item.getId());
            if(toolData.containsKey(idO))
            {
                ScriptableObject obj = toolData.get(idO);
                if(ScriptableObject.hasProperty(obj, "modifyEnchant"))
                {
                    NativeItemInstanceExtra extra = CommonTypes.getExtraFromInstance(item);
                    if(extra == null) extra = new NativeItemInstanceExtra();
                    extra.removeAllEnchants();
                    ScriptableObject enchantData = CommonTypes.createEnchantDataScriptable(new ItemStack(item));
                    CommonTypes.callVoidJSFunction(obj, "modifyEnchant", new Object[]{ enchantData, item, coords, new FullBlock(block.first.intValue(), block.second.intValue()) });
                    short[] modified = CommonTypes.enchantDataScriptableToArray(enchantData);
                    if(modified[0] > 0) extra.addEnchant(Enchantment.SILK_TOUCH, modified[0]); else extra.removeEnchant(Enchantment.SILK_TOUCH);
                    if(modified[1] > 0) extra.addEnchant(Enchantment.FORTUNE, modified[1]); else extra.removeEnchant(Enchantment.FORTUNE);
                    if(modified[2] > 0) extra.addEnchant(Enchantment.EFFICIENCY, modified[2]); else extra.removeEnchant(Enchantment.EFFICIENCY);
                    if(modified[3] > 0) extra.addEnchant(Enchantment.UNBREAKING, modified[3]); else extra.removeEnchant(Enchantment.UNBREAKING);
                    Entity.setCarriedItem(player, item.getId(), item.getCount(), item.getData(), extra);
                }
            }
        }
    }

    public static void onMineBlock(int x, int y, int z, byte side, int id, int data, long player)
    {
        ItemInstance stack = Entity.getCarriedItem(player);
        int idO = Integer.valueOf(stack.getId());
        if(toolData.containsKey(idO))
        {
            ScriptableObject obj = toolData.get(idO);
            if(ScriptableObject.hasProperty(obj, "onMineBlock"))
            {
                CommonTypes.callVoidJSFunction(obj, "onMineBlock", new Object[]{
                    new Coords(x, y, z, side),
                    stack,
                    new FullBlock(id, data)
                });
                Entity.setCarriedItem(player, stack.getId(), stack.getCount(), stack.getData(), CommonTypes.getExtraFromInstance(stack));
            }
        }
    }

    public static int getAttackDamageBonus(int id, int count, int data, long extraPtr, int defaultValue)
    {
        ItemInstance stack = new ItemInstance(id, count, data, new NativeItemInstanceExtra(extraPtr));
        int idO = Integer.valueOf(id);
        if(toolData.containsKey(idO))
        {
            ScriptableObject obj = toolData.get(idO);
            if(ScriptableObject.hasProperty(obj, "getAttackDamageBonus"))
            {
                return CommonTypes.callIntJSFunction(obj, "getAttackDamageBonus", new Object[]{ stack }, defaultValue);
            }
        }
        return defaultValue;
    } 

    public static void registerCustomTool(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech, boolean isWeapon, String[] blockMaterials, int brokenId, int baseAttackDamage, int enchantType, ScriptableObject data)
    {
        nativeRegisterCustomTool(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech, isWeapon, blockMaterials, brokenId, baseAttackDamage, enchantType);
        toolData.put(Integer.valueOf(id), data);
    }

    public static void destroyBlockHook(Coords coords, Object tile, ItemInstance item, long player)
    {
        Pair<Integer, Integer> block = CommonTypes.deserializeFullBlockOrBlockState(tile);
        if(block != null)
        {
            if(toolData.containsKey(Integer.valueOf(item.getId())))
            {
                if(onDestroy(coords, item, tile, player))
                {
                    modifyEnchant(coords, item, tile, player);
                    NativeItemInstanceExtra extra = CommonTypes.getExtraFromInstance(item);
                    if(extra == null) extra = new NativeItemInstanceExtra();
                    int unbreaking = extra.getEnchantLevel(Enchantment.UNBREAKING);
                    if((getBlockDestroyTime(block.first.intValue()) > 0 || getToolLevelViaBlock(item.getId(), block.first.intValue()) > 0) && rand.nextFloat() < 1.0f / (unbreaking + 1))
                    {
                        nativeDamageToolInHand(player, isWeapon(item.getId()) ? 2 : 1);
                    }
                }
            }
        }
    }

    public static void playerAttackHook(long attacker, long victim, ItemInstance item)
    {
        if(toolData.containsKey(Integer.valueOf(item.getId())))
        {
            if(onAttack(victim, attacker, item))
            {
                modifyEnchant(null, item, null, attacker);
                NativeItemInstanceExtra extra = CommonTypes.getExtraFromInstance(item);
                if(extra == null) extra = new NativeItemInstanceExtra();
                int unbreaking = extra.getEnchantLevel(Enchantment.UNBREAKING);
                if(rand.nextFloat() < 1.0f / (unbreaking + 1))
                {
                    nativeDamageToolInHand(attacker, isWeapon(item.getId()) ? 1 : 2);
                }
            }
        }
    }

}
