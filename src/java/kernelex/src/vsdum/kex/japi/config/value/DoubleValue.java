package vsdum.kex.japi.config.value;

import java.util.List;
import java.util.function.Supplier;

import com.electronwill.nightconfig.core.Config;

import vsdum.kex.japi.config.builder.ConfigBuilder;

public class DoubleValue extends ConfigValue<Double> {

    public DoubleValue(ConfigBuilder parent, List<String> path, Supplier<Double> defaultSupplier)
    {
        super(parent, path, defaultSupplier);
    }

    @Override protected Double getRaw(Config config, List<String> path, Supplier<Double> defaultSupplier)
    {
        Number n = config.get(path);
        return n == null ? defaultSupplier.get() : n.doubleValue();
    }

}
