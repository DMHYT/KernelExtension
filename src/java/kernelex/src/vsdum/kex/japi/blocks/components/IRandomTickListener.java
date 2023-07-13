package vsdum.kex.japi.blocks.components;

import vsdum.kex.modules.states.BlockState;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public interface IRandomTickListener {
    
    public void randomTick(BlockState state, BlockPos pos, ExtendedBlockSource world);

}
