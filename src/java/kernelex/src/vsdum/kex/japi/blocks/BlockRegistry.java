package vsdum.kex.japi.blocks;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Scriptable;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.innercore.api.NativeBlock;
import com.zhekasmirnov.innercore.api.mod.util.ScriptableFunctionImpl;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import vsdum.kex.japi.blocks.components.IAnimateTickListener;
import vsdum.kex.japi.blocks.components.ICustomPlaceBehavior;
import vsdum.kex.japi.blocks.components.IEntityInsideListener;
import vsdum.kex.japi.blocks.components.IExplosionListener;
import vsdum.kex.japi.blocks.components.IHasBlockActor;
import vsdum.kex.japi.blocks.components.IHasDrops;
import vsdum.kex.japi.blocks.components.INeighborChangeListener;
import vsdum.kex.japi.blocks.components.IRandomTickListener;
import vsdum.kex.japi.blocks.components.IStepOnListener;
import vsdum.kex.japi.blocks.components.IUsable;
import vsdum.kex.japi.component.ComponentFactory;
import vsdum.kex.modules.TileEntityModule;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public class BlockRegistry {

    private static final Map<Integer, Block> customBlocks = new HashMap<>();

    public static final ComponentFactory<Block> componentFactory = new ComponentFactory<Block>()
        .registerComponent(IAnimateTickListener.class, block -> {
            NativeBlock.setAnimateTickCallback(block.id, new ScriptableFunctionImpl() {
                @Override public Object call(Context cx, Scriptable scope, Scriptable thisObj, Object[] args)
                {
                    ((IAnimateTickListener) block).animateTick(new BlockState((int) args[3], (int) args[4]), new BlockPos((int) args[0], (int) args[1], (int) args[2]));
                    return null;
                }
            });
        })
        .registerComponent(ICustomPlaceBehavior.class, block -> BlockEvents.onPlaceEvents.put(block.id, (ICustomPlaceBehavior) block))
        .registerComponent(IEntityInsideListener.class, block -> {
            NativeBlock.setReceivingEntityInsideEvent(block.id, true);
            BlockEvents.entityInsideEvents.put(block.id, (IEntityInsideListener) block);
        })
        .registerComponent(IExplosionListener.class, block -> BlockEvents.popResourcesEvents.put(block.id, (IExplosionListener) block))
        .registerComponent(IHasBlockActor.class, block -> TileEntityModule.registerForBlock(block.id, ((IHasBlockActor) block).getTileEntityType()))
        .registerComponent(IHasDrops.class, block -> BlockEvents.getDropsEvents.put(block.id, (IHasDrops) block))
        .registerComponent(INeighborChangeListener.class, block -> {
            NativeBlock.setReceivingNeighbourChangeEvent(block.id, true);
            BlockEvents.neighborChangedEvents.put(block.id, (INeighborChangeListener) block);
        })
        .registerComponent(IRandomTickListener.class, block -> {
            NativeBlock.setRandomTickCallback(block.id, new ScriptableFunctionImpl() {
                @Override public Object call(Context cx, Scriptable scope, Scriptable thisObj, Object[] args)
                {
                    ((IRandomTickListener) block).randomTick(new BlockState((int) args[3], (int) args[4]), new BlockPos((int) args[0], (int) args[1], (int) args[2]), ExtendedBlockSource.toKEXBlockSource((NativeBlockSource) args[5]));
                    return null;
                }
            });
        })
        .registerComponent(IStepOnListener.class, block -> {
            NativeBlock.setReceivingEntityStepOnEvent(block.id, true);
            BlockEvents.stepOnEvents.put(block.id, (IStepOnListener) block);
        })
        .registerComponent(IUsable.class, block -> BlockEvents.onUseEvents.put(block.id, (IUsable) block));

    @NonNull public static <T extends Block> T register(@NonNull T block)
    {
        Objects.requireNonNull(block, "Cannot register custom block from null Block object!");
        customBlocks.put(block.id, block.getRegistryObject().register());
        return block;
    }

    @Nullable public static Block getBlockById(int id)
    {
        return customBlocks.get(id);
    }
    
}
