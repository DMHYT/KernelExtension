package vsdum.kex.japi.component;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Consumer;

public class ComponentFactory<T> {

    private final Map<Class<?>, Consumer<T>> components = new HashMap<>();

    public ComponentFactory<T> registerComponent(Class<?> componentClass, Consumer<T> applier)
    {
        this.components.put(componentClass, applier);
        return this;
    }

    public final void apply(T componentHolder)
    {
        this.components.forEach((componentClass, applier) -> {
            if(componentClass.isInstance(componentHolder))
            {
                applier.accept(componentHolder);
            }
        });
    }

}
