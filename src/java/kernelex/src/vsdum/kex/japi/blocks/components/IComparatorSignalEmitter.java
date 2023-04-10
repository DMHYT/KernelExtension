package vsdum.kex.japi.blocks.components;

import vsdum.kex.modules.BlocksModule.ComparatorSignalCallback;

public interface IComparatorSignalEmitter extends ComparatorSignalCallback {
    
    public default boolean isComparatorCallbackForced()
    {
        return false;
    }

}
