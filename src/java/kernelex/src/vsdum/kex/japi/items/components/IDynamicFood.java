package vsdum.kex.japi.items.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import android.support.annotation.NonNull;
import vsdum.kex.natives.FoodItemComponent;

public interface IDynamicFood {
    
    @NonNull public FoodItemComponent.Builder getFoodValues(ItemStack stack);

}
