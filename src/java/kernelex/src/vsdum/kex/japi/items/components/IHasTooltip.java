package vsdum.kex.japi.items.components;

import java.util.List;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import vsdum.kex.natives.Level;

public interface IHasTooltip {
    
    public void addInformation(ItemStack item, List<String> tooltip, Level level);

}
