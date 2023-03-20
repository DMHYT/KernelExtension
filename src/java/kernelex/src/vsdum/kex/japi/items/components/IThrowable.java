package vsdum.kex.japi.items.components;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;

import vsdum.kex.natives.Actor;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Direction;
import vsdum.kex.util.mcmath.Vec3d;

public interface IThrowable {
    
    default public void onProjectileHitBlock(Actor projectile, ItemStack item, Vec3d hitCoords, BlockPos blockCoords, Direction blockSide) {}

    default public void onProjectileHitEntity(Actor projectile, ItemStack item, Vec3d hitCoords, Actor hitEntity) {}

}
