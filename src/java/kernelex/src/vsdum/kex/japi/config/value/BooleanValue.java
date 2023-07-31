package vsdum.kex.japi.config.value;

import java.util.List;
import java.util.function.Supplier;

import vsdum.kex.japi.config.builder.ConfigBuilder;

public class BooleanValue extends ConfigValue<Boolean> {

    public BooleanValue(ConfigBuilder parent, List<String> path, Supplier<Boolean> defaultSupplier)
    {
        super(parent, path, defaultSupplier);
    }

}
