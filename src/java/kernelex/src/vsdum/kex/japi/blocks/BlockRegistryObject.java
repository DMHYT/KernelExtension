package vsdum.kex.japi.blocks;

import vsdum.kex.japi.registry.RegistryObject;

import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.innercore.api.runtime.saver.serializer.ScriptableSerializer;
import com.zhekasmirnov.innercore.api.unlimited.BlockRegistry;

import android.support.annotation.NonNull;

import static vsdum.kex.japi.blocks.BlockRegistry.preComponentFactory;
import static vsdum.kex.japi.blocks.BlockRegistry.componentFactory;

public class BlockRegistryObject<T extends Block> extends RegistryObject<T> {

    public BlockRegistryObject(@NonNull T block)
    {
        super(block);
    }

    protected void createBlock()
    {
        BlockRegistry.createBlock(this.object.id, this.object.nameID, (ScriptableObject) ScriptableSerializer.scriptableFromJson(this.object.defineData));
    }
    
    @Override @NonNull public final T register()
    {
        if(this.object.defineData != null)
        {
            preComponentFactory.apply(this.object);
            this.createBlock();
            this.object.properties.apply(this.object);
            componentFactory.apply(this.object);
        }
        return this.object;
    }

}
