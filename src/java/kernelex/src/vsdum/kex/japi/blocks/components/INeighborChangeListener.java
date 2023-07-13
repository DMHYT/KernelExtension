package vsdum.kex.japi.blocks.components;

import vsdum.kex.modules.states.BlockState;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public interface INeighborChangeListener {
    
    public void neighborChanged(BlockState state, ExtendedBlockSource world, BlockPos pos, BlockPos changedPos);

}
