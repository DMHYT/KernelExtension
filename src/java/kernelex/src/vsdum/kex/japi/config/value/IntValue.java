package vsdum.kex.japi.config.value;

import java.util.List;
import java.util.function.Supplier;

import com.electronwill.nightconfig.core.Config;

import vsdum.kex.japi.config.builder.ConfigBuilder;

public class IntValue extends ConfigValue<Integer> {

    public IntValue(ConfigBuilder parent, List<String> path, Supplier<Integer> defaultSupplier)
    {
        super(parent, path, defaultSupplier);
    }

    @Override protected Integer getRaw(Config config, List<String> path, Supplier<Integer> defaultSupplier)
    {
        return config.getIntOrElse(path, () -> defaultSupplier.get());
    }

}
