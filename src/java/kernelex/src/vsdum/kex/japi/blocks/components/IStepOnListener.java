package vsdum.kex.japi.blocks.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;

import vsdum.kex.natives.Actor;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public interface IStepOnListener {
    
    public void stepOn(ExtendedBlockSource world, BlockPos pos, BlockState state, Actor entity);

}
