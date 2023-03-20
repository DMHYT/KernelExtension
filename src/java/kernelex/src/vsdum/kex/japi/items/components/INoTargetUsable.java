package vsdum.kex.japi.items.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import vsdum.kex.natives.Player;

public interface INoTargetUsable {
    
    public void onUseNoTarget(ItemStack item, Player player);

}
