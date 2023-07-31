package vsdum.kex.japi.config.value;

import java.util.List;
import java.util.function.Supplier;

import com.electronwill.nightconfig.core.Config;
import com.electronwill.nightconfig.core.EnumGetMethod;

import vsdum.kex.japi.config.builder.ConfigBuilder;

public class EnumValue<T extends Enum<T>> extends ConfigValue<T> {

    private final EnumGetMethod converter;
    private final Class<T> clazz;

    public EnumValue(ConfigBuilder parent, List<String> path, Supplier<T> defaultSupplier, EnumGetMethod converter, Class<T> clazz)
    {
        super(parent, path, defaultSupplier);
        this.converter = converter;
        this.clazz = clazz;
    }

    @Override protected T getRaw(Config config, List<String> path, Supplier<T> defaultSupplier)
    {
        return config.getEnumOrElse(path, clazz, converter, () -> defaultSupplier.get());
    }

}
