package vsdum.kex.japi.blocks;

import vsdum.kex.japi.registry.RegistryObject;

import java.lang.reflect.Field;
import java.util.HashMap;

import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.innercore.api.runtime.saver.serializer.ScriptableSerializer;
import com.zhekasmirnov.innercore.api.unlimited.BlockRegistry;
import com.zhekasmirnov.innercore.api.unlimited.BlockVariant;
import com.zhekasmirnov.innercore.api.unlimited.IDDataPair;

import android.support.annotation.NonNull;

import static vsdum.kex.japi.blocks.BlockRegistry.componentFactory;

public class BlockRegistryObject<T extends Block> extends RegistryObject<T> {

    @SuppressWarnings("unchecked")
    private static final HashMap<IDDataPair, BlockVariant> getBlockVariantMap()
    {
        try {
            Field field = BlockRegistry.class.getDeclaredField("blockVariantMap");
            field.setAccessible(false);
            return (HashMap<IDDataPair, BlockVariant>) field.get(null);
        } catch(Throwable ex) { ex.printStackTrace(); }
        return null;
    }

    protected static final HashMap<IDDataPair, BlockVariant> blockVariantMap = getBlockVariantMap();

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
