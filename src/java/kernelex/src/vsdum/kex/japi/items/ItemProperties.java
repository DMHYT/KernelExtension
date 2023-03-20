package vsdum.kex.japi.items;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Optional;
import java.util.Set;

import org.json.JSONException;
import org.json.JSONObject;

import com.zhekasmirnov.innercore.api.NativeItem;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import vsdum.kex.japi.items.enums.ItemCategory;
import vsdum.kex.modules.ItemsModule;

public final class ItemProperties {

    public static final ItemProperties DEFAULT = new ItemProperties();

    private boolean allowedInOffhand = false;
    private boolean cannotBeRepairedInAnvil = false;
    private Optional<ItemCategory> category = Optional.empty();
    private int enchantType = 0;
    private boolean explodable = true;
    private boolean fireResistant = false;
    private float furnaceBurnIntervalMultiplier = 0.0f;
    private float furnaceXPMultiplier = 0.0f;
    private boolean glint = false;
    private boolean handEquipped = false;
    private boolean liquidClip = false;
    private int maxDamage = 0;
    private int maxUseDuration = 0;
    private boolean mirroredArt = false;
    private final JSONObject properties = new JSONObject();
    private final Set<Integer> repairItemIds = new HashSet<>();
    private boolean requiresWorldBuilder = false;
    private boolean shouldDespawn = true;
    private int useAnimation = 0;
    
    public ItemProperties() {}

    public ItemProperties(ItemProperties parent)
    {
        this.allowedInOffhand = parent.allowedInOffhand;
        this.cannotBeRepairedInAnvil = parent.cannotBeRepairedInAnvil;
        if(parent.category.isPresent()) this.category = Optional.of(parent.category.get());
        this.enchantType = parent.enchantType;
        this.explodable = parent.explodable;
        this.fireResistant = parent.fireResistant;
        this.furnaceBurnIntervalMultiplier = parent.furnaceBurnIntervalMultiplier;
        this.furnaceXPMultiplier = parent.furnaceXPMultiplier;
        this.glint = parent.glint;
        this.handEquipped = parent.handEquipped;
        this.liquidClip = parent.liquidClip;
        this.maxDamage = parent.maxDamage;
        this.maxUseDuration = parent.maxUseDuration;
        this.mirroredArt = parent.mirroredArt;
        parent.properties.keys().forEachRemaining(key -> {
            try {
                this.properties.put(key, parent.properties.get(key));
            } catch(JSONException ex) { ex.printStackTrace(); }
        });
        this.repairItemIds.addAll(parent.repairItemIds);
        this.requiresWorldBuilder = parent.requiresWorldBuilder;
        this.shouldDespawn = parent.shouldDespawn;
        this.useAnimation = parent.useAnimation;
    }

    public ItemProperties copy()
    {
        return new ItemProperties(this);
    }

    public void apply(Item item)
    {
        NativeItem nativeItem = NativeItem.getItemById(item.id);
        nativeItem.setAllowedInOffhand(this.allowedInOffhand);
        if(this.cannotBeRepairedInAnvil) ItemsModule.setCannotBeRepairedInAnvil(item.id);
        if(this.category.isPresent()) nativeItem.setCreativeCategory(this.category.get().ordinal());
        nativeItem.setEnchantType(this.enchantType);
        ItemsModule.setExplodable(item.id, this.explodable);
        ItemsModule.setFireResistant(item.id, this.fireResistant);
        ItemsModule.setFurnaceBurnIntervalMultiplier(item.id, this.furnaceBurnIntervalMultiplier);
        ItemsModule.setFurnaceXPMultiplier(item.id, this.furnaceXPMultiplier);
        nativeItem.setGlint(this.glint);
        nativeItem.setLiquidClip(this.liquidClip);
        nativeItem.setMaxDamage(this.maxDamage);
        nativeItem.setMaxUseDuration(this.maxUseDuration);
        ItemsModule.setIsMirroredArt(item.id, this.mirroredArt);
        nativeItem.setProperties(this.properties.toString());
        repairItemIds.forEach(nativeItem::addRepairItem);
        ItemsModule.setRequiresWorldBuilder(item.id, this.requiresWorldBuilder);
        ItemsModule.setShouldDespawn(item.id, this.shouldDespawn);
        nativeItem.setUseAnimation(this.useAnimation);
    }

    public ItemProperties setAllowedInOffhand(boolean allowed)
    {
        this.allowedInOffhand = allowed;
        return this;
    }

    public ItemProperties setCannotBeRepairedInAnvil(boolean cannot)
    {
        this.cannotBeRepairedInAnvil = cannot;
        return this;
    }

    public ItemProperties setCreativeCategory(ItemCategory category)
    {
        this.category = Optional.of(category);
        return this;
    }

    public ItemProperties setEnchantType(int enchantType)
    {
        this.enchantType = enchantType;
        return this;
    }

    public ItemProperties setExplodable(boolean explodable)
    {
        this.explodable = explodable;
        return this;
    }

    public ItemProperties setFireResistant(boolean fireResistant)
    {
        this.fireResistant = fireResistant;
        return this;
    }

    public ItemProperties setFurnaceBurnIntervalMultiplier(float multiplier)
    {
        this.furnaceBurnIntervalMultiplier = multiplier;
        return this;
    }

    public ItemProperties setFurnaceXPMultiplier(float multiplier)
    {
        this.furnaceXPMultiplier = multiplier;
        return this;
    }

    public ItemProperties setGlint(boolean glint)
    {
        this.glint = glint;
        return this;
    }

    public ItemProperties setLiquidClip(boolean clip)
    {
        this.liquidClip = clip;
        return this;
    }

    public ItemProperties setMaxDamage(int maxDamage)
    {
        this.maxDamage = maxDamage;
        return this;
    }

    public ItemProperties setMaxUseDuration(int maxUseDuration)
    {
        this.maxUseDuration = maxUseDuration;
        return this;
    }

    public ItemProperties setIsMirroredArt(boolean mirrored)
    {
        this.mirroredArt = mirrored;
        return this;
    }

    public JSONObject getJSONProperties()
    {
        return this.properties;
    }

    public ItemProperties addRepairItemID(int id)
    {
        this.repairItemIds.add(id);
        return this;
    }

    public ItemProperties addRepairItem(@NonNull Item item)
    {
        this.repairItemIds.add(item.id);
        return this;
    }

    public ItemProperties setRequiresWorldBuilder(boolean requires)
    {
        this.requiresWorldBuilder = requires;
        return this;
    }

    public ItemProperties setShouldDespawn(boolean shouldDespawn)
    {
        this.shouldDespawn = shouldDespawn;
        return this;
    }

    public ItemProperties setUseAnimation(int useAnimation)
    {
        this.useAnimation = useAnimation;
        return this;
    }

    public boolean getAllowedInOffhand()
    {
        return this.allowedInOffhand;
    }

    public boolean getCannotBeRepairedInAnvil()
    {
        return this.cannotBeRepairedInAnvil;
    }

    @Nullable public ItemCategory getCreativeCategory()
    {
        return this.category.isPresent() ? this.category.get() : null;
    }

    public int getEnchantType()
    {
        return this.enchantType;
    }

    public boolean getExplodable()
    {
        return this.explodable;
    }

    public boolean getFireResistant()
    {
        return this.fireResistant;
    }

    public float getFurnaceBurnIntervalMultiplier()
    {
        return this.furnaceBurnIntervalMultiplier;
    }

    public float getFurnaceXPMultiplier()
    {
        return this.furnaceXPMultiplier;
    }

    public boolean getGlint()
    {
        return this.glint;
    }

    public boolean getHandEquipped()
    {
        return this.handEquipped;
    }

    public boolean getLiquidClip()
    {
        return this.liquidClip;
    }

    public int getMaxDamage()
    {
        return this.maxDamage;
    }

    public int getMaxUseDuration()
    {
        return this.maxUseDuration;
    }

    public boolean getMirroredArt()
    {
        return this.mirroredArt;
    }

    public Iterator<Integer> getRepairItemIds()
    {
        return this.repairItemIds.iterator();
    }

    public boolean getRequiresWorldBuilder()
    {
        return this.requiresWorldBuilder;
    }

    public boolean getShouldDespawn()
    {
        return this.shouldDespawn;
    }

    public int getUseAnimation()
    {
        return this.useAnimation;
    }

}
