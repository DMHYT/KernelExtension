package vsdum.kex.japi.items;

import android.support.annotation.NonNull;
import vsdum.kex.japi.registry.RegistryObject;

import static vsdum.kex.japi.items.ItemRegistry.componentFactory;

import com.zhekasmirnov.innercore.api.NativeItem;

public class ItemRegistryObject<T extends Item> extends RegistryObject<T> {
    
    public ItemRegistryObject(@NonNull T block)
    {
        super(block);
    }

    protected void createItem()
    {
        NativeItem.createItem(this.object.id, this.object.nameID, this.object.displayedName, this.object.iconName.get(), this.object.iconIndex);
    }

    @Override @NonNull public final T register()
    {
        if(!this.object.iconName.isPresent())
        {
            throw new IllegalStateException("Cannot create item " + this.object.nameID + " because its icon was not specified");
        }
        this.createItem();
        this.object.properties.apply(this.object);
        componentFactory.apply(this.object);
        return this.object;
    }

}
