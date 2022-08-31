package vsdum.kex.japi.blocks.types;

import android.support.annotation.NonNull;
import vsdum.kex.japi.blocks.Block;
import vsdum.kex.japi.blocks.BlockRegistryObject;

public class LiquidBlockRegistryObject<T extends Block> extends BlockRegistryObject<T> {
    
    public LiquidBlockRegistryObject(@NonNull T block)
    {
        super(block);
    }

    @Override protected void createBlock()
    {
        // TODO
    }

}
