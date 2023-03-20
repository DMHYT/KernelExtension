package vsdum.kex.japi.items;

import java.util.Optional;

import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.unlimited.IDRegistry;

import android.support.annotation.NonNull;
import vsdum.kex.common.IdentifierHolder;
import vsdum.kex.japi.registry.IRegistrable;
import vsdum.kex.japi.registry.RegistryObject;

public class Item implements IRegistrable<Item>, IdentifierHolder {
    
    public final String nameID;
    public final int id;
    public final ItemProperties properties;
    public Optional<String> iconName = Optional.empty();
    public int iconIndex = 0;
    public String displayedName;

    public Item(String nameID)
    {
        this(nameID, ItemProperties.DEFAULT);
    }

    public Item(String nameID, ItemProperties properties)
    {
        this.nameID = nameID;
        this.id = IDRegistry.genItemID(nameID);
        this.properties = new ItemProperties(properties);
        this.displayedName = "item." + NativeAPI.convertNameId(nameID) + ".name";
    }

    public final Item setIcon(String iconName)
    {
        return this.setIcon(iconName, 0);
    }

    public final Item setIcon(String iconName, int iconIndex)
    {
        this.iconName = Optional.of(iconName);
        this.iconIndex = iconIndex;
        return this;
    }

    public final Item setDisplayedName(String name)
    {
        this.displayedName = name;
        return this;
    }
    
    @Override @NonNull public RegistryObject<Item> getRegistryObject()
    {
        return new ItemRegistryObject<>(this);
    }

    @Override public final int getId()
    {
        return this.id;
    }

}
