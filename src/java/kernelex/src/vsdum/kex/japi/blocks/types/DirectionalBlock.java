package vsdum.kex.japi.blocks.types;

import java.util.Arrays;
import java.util.List;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Entity;

import android.support.annotation.NonNull;
import vsdum.kex.japi.blocks.Block;
import vsdum.kex.japi.blocks.BlockProperties;
import vsdum.kex.japi.blocks.components.ICustomPlaceBehavior;
import vsdum.kex.japi.blocks.components.IHasDrops;
import vsdum.kex.japi.registry.RegistryObject;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.natives.Player;
import vsdum.kex.util.mcmath.BlockPos;

public class DirectionalBlock extends Block implements ICustomPlaceBehavior, IHasDrops {
    
    public DirectionalBlock(String nameID)
    {
        super(nameID);
    }

    public DirectionalBlock(String nameID, BlockProperties properties)
    {
        super(nameID, properties);
    }
    
    @Override @NonNull public RegistryObject<Block> getRegistryObject()
    {
        return new DirectionalBlockRegistryObject<>(this);
    }

    @Override public void onPlace(BlockPos pos, ItemStack item, BlockState touchedBlock, Player player, ExtendedBlockSource world)
    {
        int yaw = (int) Math.floor((Entity.getYaw(player.getUniqueID()) - 45) / 90);
        while(yaw < 0) yaw += 4;
        while(yaw > 3) yaw -= 4;
        int meta = new int[]{ 2, 0, 3, 1 }[yaw];
        world.setBlock(pos.x, pos.y, pos.z, this.id, item.data / 4 * 4 + meta);
    }

    @Override @NonNull public List<ItemStack> getDrops(BlockState state, BlockPos pos, ExtendedBlockSource world, ItemStack item)
    {
        return Arrays.asList(new ItemStack(state.id, 1, state.data / 4 * 4));
    }

}
