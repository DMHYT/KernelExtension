package vsdum.kex.japi.blocks.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.natives.Player;
import vsdum.kex.util.mcmath.BlockPos;

public interface ICustomPlaceBehavior {
    
    public void onPlace(BlockPos pos, ItemStack item, BlockState touchedBlock, Player player, ExtendedBlockSource world);

}
