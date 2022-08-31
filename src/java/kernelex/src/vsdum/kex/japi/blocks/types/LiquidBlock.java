package vsdum.kex.japi.blocks.types;

import android.support.annotation.NonNull;
import vsdum.kex.japi.blocks.Block;
import vsdum.kex.japi.blocks.BlockProperties;
import vsdum.kex.japi.registry.RegistryObject;

public class LiquidBlock extends Block {

    public boolean isRenewable = false;
    public int tickDelay = 10;
    
    public LiquidBlock(String nameID)
    {
        super(nameID);
    }

    public LiquidBlock(String nameID, BlockProperties properties)
    {
        super(nameID, properties);
    }

    public LiquidBlock setRenewable(boolean renewable)
    {
        this.isRenewable = renewable;
        return this;
    }

    public LiquidBlock setTickDelay(int delay)
    {
        this.tickDelay = delay;
        return this;
    }

    @Override @NonNull public RegistryObject<Block> getRegistryObject()
    {
        return new LiquidBlockRegistryObject<>(this);
    }

}
