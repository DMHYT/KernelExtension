package vsdum.kex.japi.blocks.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;

import vsdum.kex.natives.Actor;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public interface IEntityInsideListener {
    
    public void entityInside(BlockState state, ExtendedBlockSource world, BlockPos pos, Actor entity);

}
