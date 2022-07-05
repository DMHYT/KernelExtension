package vsdum.kex.modules;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

import android.support.annotation.Nullable;
import vsdum.kex.common.CallbackFunction;
import vsdum.kex.modules.misc.ReachDistanceModifier;
import vsdum.kex.natives.FoodItemComponent;
import vsdum.kex.natives.Level;
import vsdum.kex.natives.MobEffectInstance;
import vsdum.kex.util.MapBuilder;

public class ItemsModule {

    protected static native long nativeGetFood(int id);
    protected static native void nativeNewFoodSaturationModifier(String name, float value);
    protected static native void nativeEnableDynamicUseDuration(int id);
    protected static native void nativeEnableDynamicFoodValues(int id);
    
    public static native void setRequiresWorldBuilder(int id, boolean requiresWorldBuilder);
    public static native void setExplodable(int id, boolean explodable);
    public static native void setFireResistant(int id, boolean fireResistant);
    public static native void setShouldDespawn(int id, boolean shouldDespawn);
    public static native void setIsMirroredArt(int id, boolean isMirroredArt);
    public static native void setFurnaceBurnIntervalMultiplier(int id, float multiplier);
    public static native void setFurnaceXPMultiplier(int id, float multiplier);
    public static native void setCannotBeRepairedInAnvil(int id);

    public static native boolean isFood(int id);

    private static final Map<Integer, FoodItemComponent> food = new HashMap<>();

    @Nullable public static FoodItemComponent getFood(int id)
    {
        if(food.containsKey(id)) return food.get(id);
        if(!isFood(id)) return null;
        long ptr = nativeGetFood(id);
        if(ptr == 0L) return null;
        FoodItemComponent component = new FoodItemComponent(ptr, false);
        food.put(id, component);
        return component;
    }

    private static final Map<String, Float> foodSaturationModifiers = new MapBuilder<String, Float>()
        .add("poor", 0.2f)
        .add("low", 0.6f)
        .add("normal", 1.2f)
        .add("good", 1.6f)
        .add("max", 2.0f)
        .add("supernatural", 2.4f)
        .build();
    
    public static void newFoodSaturationModifier(String name, float value)
    {
        if(foodSaturationModifiers.containsKey(name))
        {
            Logger.debug("KEX-WARNING", String.format("Food saturation modifier %s has already been registered before!", new Object[]{ name }));
        } else {
            nativeNewFoodSaturationModifier(name, value / 2.0f);
            foodSaturationModifiers.put(name, value);
        }
    }

    public static float saturationModifierFromString(String name)
    {
        if(foodSaturationModifiers.containsKey(name)) return foodSaturationModifiers.get(name);
        Logger.debug("KEX-WARNING", String.format("Food saturation modifier %s does not exist, returning default value 1.2 (as for normal modifier)", new Object[]{ name }));
        return 1.2f;
    }

    public static interface UseDurationCallback {
        public int getUseDuration(ItemStack stack);
    }

    private static final Map<Integer, UseDurationCallback> itemUseDurationCallbacks = new HashMap<>();

    public static void setMaxUseDurationDynamic(int id, UseDurationCallback callback)
    {
        nativeEnableDynamicUseDuration(id);
        itemUseDurationCallbacks.put(id, callback);
    }

    public static int getUseDurationDynamic(long stackPtr)
    {
        ItemStack stack = ItemStack.fromPtr(stackPtr);
        if(stack == null) return 0;
        if(!itemUseDurationCallbacks.containsKey(stack.id)) return 0;
        return itemUseDurationCallbacks.get(stack.id).getUseDuration(stack);
    }

    public static interface OnTooltipCallback {
        public void onTooltip(ItemStack item, StringBuilder textBuilder, Level level);
    }

    private static final Map<Integer, List<CallbackFunction<OnTooltipCallback>>> itemOnTooltipCallbacks = new HashMap<>();

    public static String appendFormattedHovertext(long stackPtr, long levelPtr, String text)
    {
        ItemStack stack = ItemStack.fromPtr(stackPtr);
        if(stack == null) return text;
        Level level = new Level(levelPtr);
        StringBuilder textBuilder = new StringBuilder(text);
        if(itemOnTooltipCallbacks.containsKey(stack.id))
        {
            Iterator<CallbackFunction<OnTooltipCallback>> iter = itemOnTooltipCallbacks.get(stack.id).iterator();
            while(iter.hasNext()) iter.next().function.onTooltip(stack, textBuilder, level);
        }
        CallbacksModule.onItemTooltip(stack, level, textBuilder);
        return textBuilder.toString();
    }

    public static void addTooltip(int id, OnTooltipCallback cb)
    {
        addTooltip(id, cb, 0);
    }

    public static void addTooltip(int id, OnTooltipCallback cb, int priority)
    {
        itemOnTooltipCallbacks.putIfAbsent(id, new ArrayList<>());
        CallbackFunction.addToList(new CallbackFunction<OnTooltipCallback>(cb, priority), itemOnTooltipCallbacks.get(id));
    }

    public static interface FoodValuesCallback {
        public FoodItemComponent.Builder onEaten(ItemStack stack);
    }

    private static final Map<Integer, FoodValuesCallback> foodValuesCallbacks = new HashMap<>();

    public static void setDynamicFoodValues(int id, FoodValuesCallback callback)
    {
        nativeEnableDynamicFoodValues(id);
        foodValuesCallbacks.put(id, callback);
    }

    public static void getDynamicFoodValues(long stackPtr, long foodPtr)
    {
        ItemStack stack = ItemStack.fromPtr(stackPtr);
        if(stack == null) return;
        if(!foodValuesCallbacks.containsKey(stack.id)) return;
        FoodItemComponent food = new FoodItemComponent(foodPtr, true);
        FoodItemComponent.Builder foodBuilder = foodValuesCallbacks.get(stack.id).onEaten(stack);
        food.setNutrition(foodBuilder.getNutrition());
        food.setSaturationModifier(foodBuilder.getSaturationMod());
        food.setCanAlwaysEat(foodBuilder.getAlwaysEat());
        food.clearEffects();
        Iterator<Map.Entry<MobEffectInstance, Float>> iter = foodBuilder.getEffects().entrySet().iterator();
        while(iter.hasNext())
        {
            Map.Entry<MobEffectInstance, Float> entry = iter.next();
            food.addEffect(entry.getKey(), entry.getValue());
        }
    }

    private static final Map<Integer, List<ReachDistanceModifier>> reachDistanceModifiers = new HashMap<>();

    public static void registerReachDistanceModifierFor(int id, ReachDistanceModifier modifier)
    {
        reachDistanceModifiers.putIfAbsent(id, new ArrayList<>());
        reachDistanceModifiers.get(id).add(modifier);
    }

    public static void onChangeCarriedItem(ItemStack oldStack, ItemStack newStack)
    {
        if(reachDistanceModifiers.containsKey(oldStack.id))
        {
            Iterator<ReachDistanceModifier> iter = reachDistanceModifiers.get(oldStack.id).iterator();
            while(iter.hasNext()) iter.next().disable();
        }
        if(reachDistanceModifiers.containsKey(newStack.id))
        {
            Iterator<ReachDistanceModifier> iter = reachDistanceModifiers.get(newStack.id).iterator();
            while(iter.hasNext()) iter.next().enable();
        }
    }
    
}
