package vsdum.kex.japi.blocks;

import vsdum.kex.japi.registry.RegistryObject;

import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.innercore.api.runtime.saver.serializer.ScriptableSerializer;
import com.zhekasmirnov.innercore.api.unlimited.BlockRegistry;

import android.support.annotation.NonNull;

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
        if(this.object.defineData == null)
        {
            throw new IllegalStateException("Cannot create block " + this.object.nameID + " because its define data was not specified");
        }
        this.createBlock();
        this.object.properties.apply(this.object);
        componentFactory.apply(this.object);
        return this.object;
    }

}
