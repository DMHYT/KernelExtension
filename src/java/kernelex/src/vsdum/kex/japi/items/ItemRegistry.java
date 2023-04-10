package vsdum.kex.japi.items;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

import com.zhekasmirnov.innercore.api.NativeItem;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import vsdum.kex.japi.component.IdentifiedComponentFactory;
import vsdum.kex.japi.items.components.*;
import vsdum.kex.japi.items.types.FoodItem;
import vsdum.kex.modules.ItemsModule;

public class ItemRegistry {

    private static final Map<Integer, Item> customItems = new HashMap<>();

    public static final IdentifiedComponentFactory<Item> componentFactory = new IdentifiedComponentFactory<Item>()
        .registerIdentifiedComponent(ICustomDispenseBehavior.class, ItemEvents.onDispenseEvents::put)
        .registerIdentifiedComponent(ICustomUsingReleasedBehavior.class, ItemEvents.onReleaseUsingEvents::put)
        .registerComponent(IDynamicFood.class, item -> {
            if(item instanceof FoodItem)
            {
                ItemsModule.setDynamicFoodValues(item.id, ((IDynamicFood) item)::getFoodValues);
            }
        })
        .registerIdentifiedComponent(IHasDynamicIcon.class, (id, component) -> {
            NativeItem.setItemRequiresIconOverride(id, true);
            ItemEvents.getIconEvents.put(id, component);
        })
        .registerIdentifiedComponent(ItemsModule.UseDurationCallback.class, ItemsModule::setMaxUseDurationDynamic)
        .registerIdentifiedComponent(IHasTooltip.class, (id, component) -> ItemsModule.addTooltip(id, component, 0, component.isTooltipCallbackForced()))
        .registerIdentifiedComponent(IHasUseResult.class, ItemEvents.onCompleteUsingEvents::put)
        .registerIdentifiedComponent(INoTargetUsable.class, ItemEvents.onUseNoTargetEvents::put)
        .registerIdentifiedComponent(IThrowable.class, ItemEvents.onProjectileHitEvents::put)
        .registerIdentifiedComponent(IUsable.class, ItemEvents.onUseEvents::put);

    @NonNull public static <T extends Item> T register(@NonNull T item)
    {
        Objects.requireNonNull(item, "Cannot register custom item from null Item object!");
        customItems.put(item.id, item.getRegistryObject().register());
        return item;
    }

    @Nullable public static Item getItemById(int id)
    {
        return customItems.get(id);
    }
    
}
