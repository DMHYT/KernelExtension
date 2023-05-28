package vsdum.kex.japi.blocks;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

import org.json.JSONObject;
import org.mozilla.javascript.Context;
import org.mozilla.javascript.Scriptable;

import com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState;
import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.NativeBlock;
import com.zhekasmirnov.innercore.api.NativeBlockRenderer;
import com.zhekasmirnov.innercore.api.NativeICRender.CollisionShape;
import com.zhekasmirnov.innercore.api.mod.util.ScriptableFunctionImpl;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import vsdum.kex.japi.blocks.components.*;
import vsdum.kex.japi.component.IdentifiedComponentFactory;
import vsdum.kex.modules.BlocksModule;
import vsdum.kex.modules.TileEntityModule;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public class BlockRegistry {

    private static final CollisionShape emptyCollisionShape = new CollisionShape();
    private static final Map<Integer, Block> customBlocks = new HashMap<>();

    public static final IdentifiedComponentFactory<Block> preComponentFactory = new IdentifiedComponentFactory<Block>()
        .registerComponent(ITechBlock.class, block -> {
            try {
                if(block.defineData != null)
                    for(int variant = 0; variant < Math.min(block.defineData.length(), 16); variant++)
                    {
                        Object variantJson = block.defineData.get(variant);
                        if(variantJson instanceof JSONObject)
                            ((JSONObject) variantJson).put("inCreative", ((ITechBlock) block).isInCreative(variant));
                    }
            } catch(Throwable ex) { ex.printStackTrace(); }
        });

    public static final IdentifiedComponentFactory<Block> componentFactory = new IdentifiedComponentFactory<Block>()
        .registerIdentifiedComponent(IAnimateTickListener.class, (id, component) -> {
            NativeBlock.setAnimateTickCallback(id, new ScriptableFunctionImpl() {
                @Override public Object call(Context cx, Scriptable scope, Scriptable thisObj, Object[] args)
                {
                    component.animateTick(new BlockState((int) args[3], (int) args[4]), new BlockPos((int) args[0], (int) args[1], (int) args[2]));
                    return null;
                }
            });
        })
        .registerIdentifiedComponent(ICustomPlaceBehavior.class, BlockEvents.onPlaceEvents::put)
        .registerIdentifiedComponent(IEntityInsideListener.class, (id, component) -> {
            NativeBlock.setReceivingEntityInsideEvent(id, true);
            BlockEvents.entityInsideEvents.put(id, component);
        })
        .registerIdentifiedComponent(IHasDrops.class, BlockEvents.getDropsEvents::put)
        .registerIdentifiedComponent(IExplosionListener.class, BlockEvents.popResourcesEvents::put)
        .registerIdentifiedComponent(IHasBlockActor.class, (id, component) -> TileEntityModule.registerForBlock(id, component.getTileEntityType()))
        .registerIdentifiedComponent(INeighborChangeListener.class, (id, component) -> {
            NativeBlock.setReceivingNeighbourChangeEvent(id, true);
            BlockEvents.neighborChangedEvents.put(id, component);
        })
        .registerIdentifiedComponent(IRandomTickListener.class, (id, component) -> {
            NativeBlock.setRandomTickCallback(id, new ScriptableFunctionImpl() {
                @Override public Object call(Context cx, Scriptable scope, Scriptable thisObj, Object[] args)
                {
                    component.randomTick(new BlockState((int) args[3], (int) args[4]), new BlockPos((int) args[0], (int) args[1], (int) args[2]), ExtendedBlockSource.toKEXBlockSource((NativeBlockSource) args[5]));
                    return null;
                }
            });
        })
        .registerIdentifiedComponent(IStepOnListener.class, (id, component) -> {
            NativeBlock.setReceivingEntityStepOnEvent(id, true);
            BlockEvents.stepOnEvents.put(id, component);
        })
        .registerIdentifiedComponent(IUsable.class, BlockEvents.onUseEvents::put)
        .registerIdentifiedComponent(IComparatorSignalEmitter.class, (id, component) -> BlocksModule.registerComparatorSignalCallback(id, component, component.isComparatorCallbackForced()))
        .registerComponent(ICustomCollisionShape.class, block -> {
            ICustomCollisionShape component = (ICustomCollisionShape) block;
            for(int variant = 0; variant < Math.min(block.defineData.length(), 16); variant++)
            {
                if(!component.hasCollision(variant))
                    NativeBlockRenderer.setCustomCollisionAndRaycastShape(block.id, variant, emptyCollisionShape);
                else {
                    CollisionShape shape = component.getCollisionShape(variant);
                    if(shape != null) NativeBlockRenderer.setCustomCollisionAndRaycastShape(block.id, variant, shape);
                }
            }
        });

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

    public static void onModsLoaded()
    {
        customBlocks.values().forEach(block -> {
            if(block.defineData == null)
            {
                Logger.warning(String.format("[KEX-BlockRegistry] Block %s (%d) has not been registered, because its variants had not been defined either programmatically or via JSON", block.nameID, block.id));
            }
        });
    }
    
}
