package vsdum.kex.util;

import android.support.annotation.Nullable;

public class ItemFabricHelper {
    
    protected static native Object nativeKillItem(int id);
    protected static native void nativeSetItem(int id, String nameId, String ntd, String t, int i, int d, int s, int a, int m, int c, int et, int ev, int[] r, boolean g, boolean he, boolean l, boolean ic, boolean ad, boolean sd, boolean o, String ip);

    @Nullable public static ItemFactoryInterface killItem(int id)
    {
        Object factoryInterface = nativeKillItem(id);
        return factoryInterface != null ? (ItemFactoryInterface) factoryInterface : null;
    }

    public static class ItemFactoryInterface {
        
        public final String nameId;
        public final String nameToDisplay;
        public final String iconName;
        public final int iconIndex;
        public final int durability;
        public final int stack;
        public final int animationId;
        public final int maxUseDuration;
        public final int creativeCategory;
        public final int enchantType;
        public final int enchantValue;
        public final int[] repairItemIds;
        public final boolean isGlint;
        public final boolean isHandEquipped;
        public final boolean isLiquidClip;
        public final boolean isIconControlled;
        public final boolean isArmorDamageable;
        public final boolean isStackedByData;
        public final boolean isAllowedInOffhand;
        public final String initProperties;

        public ItemFactoryInterface(String n, String ntd, String t, int i, int d, int s, int a, int m, int c, int et, int ev, int[] r, boolean g, boolean he, boolean l, boolean ic, boolean ad, boolean sd, boolean o, String ip)
        {
            this.nameId = n;
            this.nameToDisplay = ntd;
            this.iconName = t;
            this.iconIndex = i;
            this.durability = d;
            this.stack = s;
            this.animationId = a;
            this.maxUseDuration = m;
            this.creativeCategory = c;
            this.enchantType = et;
            this.enchantValue = ev;
            this.repairItemIds = r;
            this.isGlint = g;
            this.isHandEquipped = he;
            this.isLiquidClip = l;
            this.isIconControlled = ic;
            this.isArmorDamageable = ad;
            this.isStackedByData = sd;
            this.isAllowedInOffhand = o;
            this.initProperties = ip;
        }

        public void setFactoryProperties(int id)
        {
            nativeSetItem(id, this.nameId, this.nameToDisplay, this.iconName, this.iconIndex, this.durability, this.stack, this.animationId, this.maxUseDuration, this.creativeCategory, this.enchantType, this.enchantValue, this.repairItemIds, this.isGlint, this.isHandEquipped, this.isLiquidClip, this.isIconControlled, this.isArmorDamageable, this.isStackedByData, this.isAllowedInOffhand, this.initProperties);
        }

    }

}
