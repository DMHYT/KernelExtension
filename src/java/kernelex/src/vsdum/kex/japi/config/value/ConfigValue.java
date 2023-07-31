package vsdum.kex.japi.config.value;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.function.Supplier;

import com.electronwill.nightconfig.core.Config;

import vsdum.kex.japi.config.ConfigSpec;
import vsdum.kex.japi.config.builder.ConfigBuilder;

public class ConfigValue<T> implements Supplier<T> {

    private final ConfigBuilder parent;
    private final List<String> path;
    private final Supplier<T> defaultSupplier;
    private T cachedValue = null;
    public ConfigSpec spec;

    public ConfigValue(ConfigBuilder parent, List<String> path, Supplier<T> defaultSupplier)
    {
        this.parent = parent;
        this.path = path;
        this.defaultSupplier = defaultSupplier;
        this.parent.values.add(this);
    }

    public List<String> getPath()
    {
        return new ArrayList<>(this.path);
    }

    @Override public T get()
    {
        Objects.requireNonNull(this.spec, "cannot get config value before spec is built");
        if(this.spec.childConfig == null) return this.defaultSupplier.get();
        this.cachedValue = this.getRaw(this.spec.childConfig, path, defaultSupplier);
        return this.cachedValue;
    }

    protected T getRaw(Config config, List<String> path, Supplier<T> defaultSupplier)
    {
        return config.getOrElse(path, () -> defaultSupplier.get());
    }

    public T getDefault()
    {
        return this.defaultSupplier.get();
    }

    public ConfigBuilder next()
    {
        return this.parent;
    }

    public void save()
    {
        Objects.requireNonNull(this.spec, "Cannot save config value before spec is built");
        Objects.requireNonNull(this.spec.childConfig, "Cannot save config value without assigned Config object present");
        this.spec.save();
    }

    public void set(T value)
    {
        Objects.requireNonNull(this.spec, "Cannot save config value before spec is built");
        Objects.requireNonNull(this.spec.childConfig, "Cannot save config value without assigned Config object present");
        this.spec.childConfig.set(this.path, value);
        this.cachedValue = value;
    }

    public void clearCache()
    {
        this.cachedValue = null;
    }

}
