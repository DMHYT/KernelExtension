package vsdum.kex.japi.items.components;

import vsdum.kex.modules.ItemsModule.OnTooltipCallback;

public interface IHasTooltip extends OnTooltipCallback {
    
    public default boolean isTooltipCallbackForced()
    {
        return true;
    }

}
