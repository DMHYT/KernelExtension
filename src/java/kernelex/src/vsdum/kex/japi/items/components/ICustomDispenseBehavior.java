package vsdum.kex.japi.items.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Direction;
import vsdum.kex.util.mcmath.Vec3d;

public interface ICustomDispenseBehavior {
    
    public void onDispense(BlockPos coords, Direction side, Vec3d vecCoords, ItemStack item, ExtendedBlockSource world, int dispenserSlot);

}
