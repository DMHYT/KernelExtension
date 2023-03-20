package vsdum.kex.japi.component;

import java.util.function.BiConsumer;
import java.util.function.Consumer;

import vsdum.kex.common.IdentifierHolder;

public class IdentifiedComponentFactory<T extends IdentifierHolder> extends ComponentFactory<T> {

    @Override public IdentifiedComponentFactory<T> registerComponent(Class<?> componentClass, Consumer<T> applier)
    {
        super.registerComponent(componentClass, applier);
        return this;
    }
    
    @SuppressWarnings("unchecked")
    public <C> IdentifiedComponentFactory<T> registerIdentifiedComponent(Class<C> componentClass, BiConsumer<Integer, C> applier)
    {
        this.registerComponent(componentClass, holder -> applier.accept(holder.getId(), (C) holder));
        return this;
    }

}
