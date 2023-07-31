package vsdum.kex.japi.config.value;

import java.util.List;
import java.util.function.Supplier;

import com.electronwill.nightconfig.core.Config;

import vsdum.kex.japi.config.builder.ConfigBuilder;

public class LongValue extends ConfigValue<Long> {

    public LongValue(ConfigBuilder parent, List<String> path, Supplier<Long> defaultSupplier)
    {
        super(parent, path, defaultSupplier);
    }

    @Override protected Long getRaw(Config config, List<String> path, Supplier<Long> defaultSupplier)
    {
        return config.getLongOrElse(path, () -> defaultSupplier.get());
    }

}
