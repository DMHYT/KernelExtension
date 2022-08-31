package vsdum.kex.japi.blocks.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;

import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public interface IExplosionListener {
    
    public void popResources(BlockPos pos, ExtendedBlockSource world, BlockState brokenBlock);

}
