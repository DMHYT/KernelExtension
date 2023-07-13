package vsdum.kex.japi.blocks.components;

import vsdum.kex.modules.states.BlockState;
import vsdum.kex.util.mcmath.BlockPos;

public interface IAnimateTickListener {
    
    public void animateTick(BlockState state, BlockPos pos);

}
