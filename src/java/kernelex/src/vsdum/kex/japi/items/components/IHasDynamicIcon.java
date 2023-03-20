package vsdum.kex.japi.items.components;

import java.util.Objects;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import android.support.annotation.NonNull;
import android.util.Pair;

public interface IHasDynamicIcon {

    @NonNull public String getIconName(ItemStack stack, boolean isModUI);
    
    @NonNull default public Pair<String, Integer> getIcon(ItemStack stack, boolean isModUI)
    {
        return new Pair<>(Objects.requireNonNull(this.getIconName(stack, isModUI), "Cannot override custom item's icon, the null texture name was given"), 0);
    }

}
