package vsdum.kex.modules;

import java.util.HashMap;
import java.util.Map;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

import android.support.annotation.Nullable;
import vsdum.kex.natives.FoodItemComponent;

public class ItemsModule {

    protected static native long nativeGetFood(int id);
    protected static native void nativeNewFoodSaturationModifier(String name, float value);
    
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
        FoodItemComponent component = new FoodItemComponent(ptr);
        food.put(id, component);
        return component;
    }

    private static final Map<String, Float> foodSaturationModifiers = new HashMap<>();

    static {
        foodSaturationModifiers.put("poor", 0.2f);
        foodSaturationModifiers.put("low", 0.6f);
        foodSaturationModifiers.put("normal", 1.2f);
        foodSaturationModifiers.put("good", 1.6f);
        foodSaturationModifiers.put("max", 2.0f);
        foodSaturationModifiers.put("supernatural", 2.4f);
    }
    
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
    
}
