package vsdum.kex.japi.items.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import vsdum.kex.natives.Player;

public interface ICustomUsingReleasedBehavior {
    
    public void onReleaseUsing(ItemStack stack, int ticksLeft, Player player);

}
