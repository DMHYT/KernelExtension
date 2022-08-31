package vsdum.kex.japi.registry;

import java.util.Objects;

import android.support.annotation.NonNull;

public abstract class RegistryObject<T> {

    @NonNull protected final T object;

    public RegistryObject(@NonNull T obj)
    {
        this.object = Objects.requireNonNull(obj);
    }
    
    @NonNull public abstract T register();

}
