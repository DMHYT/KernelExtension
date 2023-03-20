package vsdum.kex.japi.items.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import vsdum.kex.natives.Player;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Direction;
import vsdum.kex.util.mcmath.Vec3d;

public interface IUsable {
    
    public void onUse(BlockPos pos, Direction side, Vec3d vecCoords, ItemStack item, BlockState touchedState, Player player);

}
