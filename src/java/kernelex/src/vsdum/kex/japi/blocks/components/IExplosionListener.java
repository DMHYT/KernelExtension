package vsdum.kex.japi.blocks.components;

import vsdum.kex.modules.states.BlockState;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public interface IExplosionListener {
    
    public void popResources(BlockPos pos, ExtendedBlockSource world, BlockState brokenBlock);

}
