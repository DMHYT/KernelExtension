package vsdum.kex.japi.blocks.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;

import vsdum.kex.util.mcmath.BlockPos;

public interface IAnimateTickListener {
    
    public void animateTick(BlockState state, BlockPos pos);

}
