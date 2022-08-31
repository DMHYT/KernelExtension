package vsdum.kex.japi.registry;

import android.support.annotation.NonNull;

public interface IRegistrable<T> {
    
    @NonNull public RegistryObject<T> getRegistryObject();

}
