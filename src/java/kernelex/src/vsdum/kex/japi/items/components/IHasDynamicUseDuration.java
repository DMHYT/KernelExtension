package vsdum.kex.japi.items.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

public interface IHasDynamicUseDuration {
    
    public int getUseDuration(ItemStack stack);

}
