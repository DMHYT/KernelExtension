package vsdum.kex.modules;

import java.util.Random;

import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.NativeBlock;
import com.zhekasmirnov.innercore.api.NativeItem;
import com.zhekasmirnov.innercore.api.NativeItemInstanceExtra;
import com.zhekasmirnov.innercore.api.commontypes.Coords;
import com.zhekasmirnov.innercore.api.commontypes.ItemInstance;
import com.zhekasmirnov.innercore.api.constants.Enchantment;
import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Entity;

import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import android.util.Pair;
import vsdum.kex.common.INativeInterface;
import vsdum.kex.modules.tools.*;
import vsdum.kex.util.CommonTypes;
import vsdum.kex.util.SoundEffect;

public class ToolsModule {

    public static native float getBlockDestroyTime(int id);
    public static native int getToolLevel(int id);
    public static native int getToolLevelViaBlock(int itemID, int blockID);
    public static native void enableDynamicDamageFor(int id);
    public static native void useCustomShearsOn(int x, int y, int z, byte side, float relX, float relY, float relZ, long actorUID);
    public static native void useCustomFlintAndSteelOn(int x, int y, int z, byte side, float relX, float relY, float relZ, long actorUID);
    public static native boolean isTool(int id);
    public static native boolean isSword(int id);
    public static native boolean isAxe(int id);
    public static native boolean isPickaxe(int id);
    public static native boolean isShovel(int id);
    public static native boolean isHoe(int id);
    public static native boolean isCustomTool(int id);
    public static native boolean isShears(int id);
    public static native boolean isFlintAndSteel(int id);

    @Nullable public static final ItemTier getTierByName(String name)
    {
        return DataSets.tiersByName.getOrDefault(name, null);
    }

    public static class ItemTier implements INativeInterface {

        protected final long pointer;

        public final long getPointer()
        {
            return this.pointer;
        }

        public ItemTier(String name, int level, int uses, float speed, int attackDamageBonus, int enchantmentValue)
        {
            if(DataSets.tiersByName.containsKey(name))
                throw new IllegalArgumentException("Item tier with name " + name + " has already been registered! Consider using another name!");
            this.pointer = ToolsNativeAPI.nativeNewItemTier(level - 1, uses, speed, attackDamageBonus, enchantmentValue);
            DataSets.tiersByName.put(name, this);
        }

        public ItemTier(long ptr)
        {
            this.pointer = ptr;
        }

        public final int getLevel()
        {
            return ToolsNativeAPI.nativeGetItemTierLevel(this.pointer) + 1;
        }

        public final int getUses()
        {
            return ToolsNativeAPI.nativeGetItemTierUses(this.pointer);
        }

        public final float getSpeed()
        {
            return ToolsNativeAPI.nativeGetItemTierSpeed(this.pointer);
        }

        public final int getAttackDamageBonus()
        {
            return ToolsNativeAPI.nativeGetItemTierAttackDamageBonus(this.pointer);
        }

        public final int getEnchantmentValue()
        {
            return ToolsNativeAPI.nativeGetItemTierEnchantmentValue(this.pointer);
        }

    }

    private static Random rand = new Random();

    public static void registerSword(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerSword(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerSword(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        ToolsNativeAPI.nativeRegisterSword(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerAxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerAxe(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerAxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        ToolsNativeAPI.nativeRegisterAxe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerPickaxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerPickaxe(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerPickaxe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        ToolsNativeAPI.nativeRegisterPickaxe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerShovel(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerShovel(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerShovel(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        ToolsNativeAPI.nativeRegisterShovel(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerHoe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerHoe(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerHoe(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        ToolsNativeAPI.nativeRegisterHoe(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech);
    }

    public static void registerShears(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier)
    {
        registerShears(id, nameId, name, textureName, textureMeta, tier, true);
    }

    public static void registerShears(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech)
    {
        ToolsNativeAPI.nativeRegisterShears(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech, 0);
    }

    public static void registerShears(int id, String nameId, String name, String textureName, int textureMeta, int durability)
    {
        registerShears(id, nameId, name, textureName, textureMeta, durability, true);
    }

    public static void registerShears(int id, String nameId, String name, String textureName, int textureMeta, int durability, boolean isTech)
    {
        ToolsNativeAPI.nativeRegisterShears(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, 0L, isTech, durability);
    }

    public static void registerFlintAndSteel(int id, String nameId, String name, String textureName, int textureMeta, int durability)
    {
        registerFlintAndSteel(id, nameId, name, textureName, textureMeta, durability, true);
    }

    public static void registerFlintAndSteel(int id, String nameId, String name, String textureName, int textureMeta, int durability, boolean isTech)
    {
        ToolsNativeAPI.nativeRegisterFlintAndSteel(id, nameId, name, textureName, textureMeta, isTech, durability);
    }

    public static void addBlockMaterial(String name, float breakingMultiplier)
    {
        DataSets.materialNameToBreakingMultiplier.putIfAbsent(name, breakingMultiplier);
    }

    public static float getBlockMaterialBreakingMultiplier(String name)
    {
        return DataSets.materialNameToBreakingMultiplier.getOrDefault(name, 0.0f).floatValue();
    }

    public static DataSets.BlockData getBlockData(int blockID)
    {
        blockID = blockID < 0 ? 255 - blockID : blockID;
        return (DataSets.BlockData) ToolsNativeAPI.nativeGetBlockData(blockID);
    }

    @Nullable public static String getBlockMaterialName(int blockID)
    {
        blockID = blockID < 0 ? 255 - blockID : blockID;
        return ToolsNativeAPI.nativeGetBlockMaterialName(blockID);
    }

    public static int getBlockDestroyLevel(int blockID)
    {
        return ToolsNativeAPI.nativeGetBlockDestroyLevel(blockID);
    }

    public static boolean getBlockIsNative(int blockID)
    {
        return ToolsNativeAPI.nativeGetBlockIsNative(blockID);
    }

    public static void setBlockData(int blockID, String materialName, int destroyLevel, boolean isNative)
    {
        ToolsNativeAPI.nativeSetBlockData(blockID, materialName, destroyLevel, isNative);
    }

    public static void setBlockMaterialName(int blockID, String materialName)
    {
        ToolsNativeAPI.nativeSetBlockMaterialName(blockID, materialName);
    }

    public static void setBlockDestroyLevel(int blockID, int destroyLevel)
    {
        ToolsNativeAPI.nativeSetBlockDestroyLevel(blockID, destroyLevel);
    }

    public static void setBlockIsNative(int blockID, boolean isNative)
    {
        ToolsNativeAPI.nativeSetBlockIsNative(blockID, isNative);
    }

    public static float getDestroyTimeViaTool(Object tile, int x, int y, int z, int side, int id, int count, int data, NativeItemInstanceExtra extra)
    {
        Pair<Integer, Integer> block = CommonTypes.deserializeFullBlockOrBlockState(tile);
        if(block == null) return 0.0f;
        return ToolsNativeAPI.nativeGetDestroyTimeViaTool(block.first.intValue(), block.second.intValue(), id, count, data, extra != null ? extra.getValue() : 0L, x, y, z, side);
    }

    public static void registerCustomTool(int id, String nameId, String name, String textureName, int textureMeta, ItemTier tier, boolean isTech, boolean isWeapon, String[] blockMaterials, int brokenId, int baseAttackDamage, int enchantType, ScriptableObject data)
    {
        ToolsNativeAPI.nativeRegisterCustomTool(id, NativeAPI.convertNameId(nameId), name, textureName, textureMeta, tier.getPointer(), isTech, isWeapon, blockMaterials, brokenId, baseAttackDamage, enchantType);
        DataSets.toolData.put(id, data);
    }

    public static void breakCarriedTool(long player, int damageValue, ItemInstance item)
    {
        if(item.getData() + damageValue >= NativeItem.getMaxDamageForId(item.getId(), item.getData()))
        {
            ScriptableObject toolData = DataSets.toolData.get(item.getId());
            int brokenId = toolData != null ? ScriptableObjectHelper.getIntProperty(toolData, "brokenId", 0) : 0;
            Entity.setCarriedItem(player, brokenId, brokenId == 0 ? 0 : 1, 0, brokenId == 0 ? null : item.getExtra());
            SoundEffect.create("random.break").playAt(player, 1.0f);
        } else Entity.setCarriedItem(player, item.getId(), item.getCount(), item.getData() + damageValue, item.getExtra());
    }

    public static void destroyBlockHook(Coords coords, Object tile, ItemInstance item, long player)
    {
        Pair<Integer, Integer> block = CommonTypes.deserializeFullBlockOrBlockState(tile);
        if(block != null)
        {
            if(!CustomToolEvents.onDestroy(coords, item, tile, player))
            {
                CustomToolEvents.modifyEnchant(coords, item, tile, player);
                NativeItemInstanceExtra extra = item.getExtra();
                if(extra == null) extra = new NativeItemInstanceExtra();
                int unbreaking = extra.getEnchantLevel(Enchantment.UNBREAKING);
                if(
                    NativeBlock.getDestroyTime(block.first.intValue()) > 0.0f && (
                        getBlockDestroyTime(block.first.intValue()) > 0 ||
                        getToolLevelViaBlock(item.getId(), block.first.intValue()) > 0
                    ) &&
                    rand.nextFloat() < 1.0f / (unbreaking + 1) &&
                    !CustomToolEvents.onBroke(player)
                ) {
                    breakCarriedTool(player, DataSets.isWeapon(item.getId()) ? 2 : 1, item);
                }
            }
        }
    }

    public static void playerAttackHook(long attacker, long victim, ItemInstance item)
    {
        if(!CustomToolEvents.onAttack(victim, attacker, item))
        {
            CustomToolEvents.modifyEnchant(null, item, null, attacker);
            NativeItemInstanceExtra extra = item.getExtra();
            if(extra == null) extra = new NativeItemInstanceExtra();
            int unbreaking = extra.getEnchantLevel(Enchantment.UNBREAKING);
            if(rand.nextFloat() < 1.0f / (unbreaking + 1) && !CustomToolEvents.onBroke(attacker))
            {
                breakCarriedTool(attacker, DataSets.isWeapon(item.getId()) ? 1 : 2, item);
            }
        }
    }

}
