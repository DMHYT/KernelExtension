package vsdum.kex.modules.tools;

import android.support.annotation.Nullable;

public class ToolsNativeAPI {
    
    public static native long[] nativeGrabVanillaItemTiers();
    public static native long nativeNewItemTier(int level, int uses, float speed, int attackDamageBonus, int enchantmentValue);
    public static native int nativeGetItemTierLevel(long ptr);
    public static native int nativeGetItemTierUses(long ptr);
    public static native float nativeGetItemTierSpeed(long ptr);
    public static native int nativeGetItemTierAttackDamageBonus(long ptr);
    public static native int nativeGetItemTierEnchantmentValue(long ptr);
    public static native void nativeRegisterSword(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    public static native void nativeRegisterAxe(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    public static native void nativeRegisterPickaxe(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    public static native void nativeRegisterShovel(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    public static native void nativeRegisterHoe(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech);
    @Nullable public static native String nativeGetBlockMaterialName(int id);
    public static native int nativeGetBlockDestroyLevel(int id);
    public static native boolean nativeGetBlockIsNative(int id);
    public static native void nativeSetBlockMaterialName(int id, String materialName);
    public static native void nativeSetBlockDestroyLevel(int id, int destroyLevel);
    public static native void nativeSetBlockIsNative(int id, boolean isNative);
    public static native Object nativeGetBlockData(int id);
    public static native void nativeSetBlockData(int id, String materialName, int destroyLevel, boolean isNative);
    public static native void nativeRegisterCustomTool(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech, boolean isWeapon, String[] blockMaterials, int brokenId, int baseAttackDamage, int enchantType);
    public static native float nativeGetDestroyTimeViaTool(int id, int data, int itemID, int itemCount, int itemData, long itemExtra, int x, int y, int z, int side);
    public static native void nativeRegisterShears(int id, String nameId, String name, String textureName, int textureMeta, long tierPtr, boolean isTech, int durabilityIfWithoutTier);
    public static native void nativeRegisterFlintAndSteel(int id, String nameId, String name, String textureName, int textureMeta, boolean isTech, int durability);

}
