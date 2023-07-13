package vsdum.kex.japi.blocks.components;

import vsdum.kex.modules.states.BlockState;
import vsdum.kex.natives.Actor;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public interface IEntityInsideListener {
    
    public void entityInside(BlockState state, ExtendedBlockSource world, BlockPos pos, Actor entity);

}
