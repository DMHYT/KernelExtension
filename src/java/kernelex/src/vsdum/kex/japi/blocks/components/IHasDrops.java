package vsdum.kex.japi.blocks.components;

import java.util.List;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import android.support.annotation.NonNull;
import vsdum.kex.modules.states.BlockState;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public interface IHasDrops {
    
    @NonNull public List<ItemStack> getDrops(BlockState state, BlockPos pos, ExtendedBlockSource world, ItemStack item);

}
