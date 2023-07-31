package vsdum.kex.japi.config.builder;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;

import com.electronwill.nightconfig.core.Config;
import com.electronwill.nightconfig.core.EnumGetMethod;
import com.electronwill.nightconfig.core.InMemoryFormat;
import com.electronwill.nightconfig.core.SimpleConfig;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

import android.util.Pair;
import vsdum.kex.japi.config.ConfigSpec;
import vsdum.kex.japi.config.value.*;

public class ConfigBuilder {

    private final Config storage = new SimpleConfig(LinkedHashMap::new, InMemoryFormat.withUniversalSupport());
    private BuilderContext context = new BuilderContext();
    private Map<List<String>, String> levelComments = new HashMap<>();
    private Map<List<String>, String> levelTranslationKeys = new HashMap<>();
    private List<String> currentPath = new ArrayList<>();
    public List<ConfigValue<?>> values = new ArrayList<>();

    public <T> ConfigValue<T> define(String path, T defaultValue)
    {
        return this.define(split(path), defaultValue);
    }

    public <T> ConfigValue<T> define(List<String> path, T defaultValue)
    {
        return this.define(path, defaultValue, o -> o != null && defaultValue.getClass().isAssignableFrom(o.getClass()));
    }

    public <T> ConfigValue<T> define(String path, T defaultValue, Predicate<Object> validator)
    {
        return this.define(split(path), defaultValue, validator);
    }

    public <T> ConfigValue<T> define(List<String> path, T defaultValue, Predicate<Object> validator)
    {
        Objects.requireNonNull(defaultValue, "Default value cannot be null");
        return this.define(path, () -> defaultValue, validator);
    }

    public <T> ConfigValue<T> define(String path, Supplier<T> defaultSupplier, Predicate<Object> validator)
    {
        return this.define(split(path), defaultSupplier, validator);
    }

    public <T> ConfigValue<T> define(List<String> path, Supplier<T> defaultSupplier, Predicate<Object> validator)
    {
        return this.define(path, defaultSupplier, validator, Object.class);
    }

    public <T> ConfigValue<T> define(List<String> path, Supplier<T> defaultSupplier, Predicate<Object> validator, Class<?> clazz)
    {
        this.context.setClazz(clazz);
        return this.define(path, new ValueSpec(defaultSupplier, validator, this.context, path), defaultSupplier);
    }

    public <T> ConfigValue<T> define(List<String> path, ValueSpec value, Supplier<T> defaultSupplier)
    {
        if(!this.currentPath.isEmpty())
        {
            List<String> tmp = new ArrayList<>(this.currentPath.size() + path.size());
            tmp.addAll(this.currentPath);
            tmp.addAll(path);
            path = tmp;
        }
        this.storage.set(path, value);
        this.context = new BuilderContext();
        return new ConfigValue<>(this, path, defaultSupplier);
    }

    public <V extends Comparable<? super V>> ConfigValue<V> defineInRange(String path, V defaultValue, V min, V max, Class<V> clazz)
    {
        return this.defineInRange(split(path), defaultValue, min, max, clazz);
    }

    public <V extends Comparable<? super V>> ConfigValue<V> defineInRange(List<String> path, V defaultValue, V min, V max, Class<V> clazz)
    {
        return this.defineInRange(path, (Supplier<V>)() -> defaultValue, min, max, clazz);
    }

    public <V extends Comparable<? super V>> ConfigValue<V> defineInRange(String path, Supplier<V> defaultSupplier, V min, V max, Class<V> clazz)
    {
        return this.defineInRange(split(path), defaultSupplier, min, max, clazz);
    }

    public <V extends Comparable<? super V>> ConfigValue<V> defineInRange(List<String> path, Supplier<V> defaultSupplier, V min, V max, Class<V> clazz)
    {
        Range<V> range = new Range<>(clazz, min, max);
        this.context.setRange(range);
        this.comment("Range: " + range.toString());
        if(min.compareTo(max) > 0) throw new IllegalArgumentException("Range min must be less than max.");
        return this.define(path, defaultSupplier, range);
    }

    public <T> ConfigValue<T> defineInList(String path, T defaultValue, Collection<? extends T> acceptableValues)
    {
        return this.defineInList(split(path), defaultValue, acceptableValues);
    }

    public <T> ConfigValue<T> defineInList(List<String> path, T defaultValue, Collection<? extends T> acceptableValues)
    {
        return this.defineInList(path, () -> defaultValue, acceptableValues);
    }

    public <T> ConfigValue<T> defineInList(String path, Supplier<T> defaultSupplier, Collection<? extends T> acceptableValues)
    {
        return this.defineInList(split(path), defaultSupplier, acceptableValues);
    }

    public <T> ConfigValue<T> defineInList(List<String> path, Supplier<T> defaultSupplier, Collection<? extends T> acceptableValues)
    {
        return this.define(path, defaultSupplier, acceptableValues::contains);
    }

    public <T> ConfigValue<List<? extends T>> defineList(String path, List<? extends T> defaultValue, Predicate<Object> elementValidator)
    {
        return this.defineList(split(path), defaultValue, elementValidator);
    }

    public <T> ConfigValue<List<? extends T>> defineList(List<String> path, List<? extends T> defaultValue, Predicate<Object> elementValidator)
    {
        return this.defineList(path, () -> defaultValue, elementValidator);
    }

    public <T> ConfigValue<List<? extends T>> defineList(String path, Supplier<List<? extends T>> defaultSupplier, Predicate<Object> elementValidator)
    {
        return this.defineList(split(path), defaultSupplier, elementValidator);
    }

    public <T> ConfigValue<List<? extends T>> defineList(List<String> path, Supplier<List<? extends T>> defaultSupplier, Predicate<Object> elementValidator)
    {
        this.context.setClazz(List.class);
        return this.define(path, new ValueSpec(defaultSupplier, getListValidator(elementValidator), this.context, path) {
            @Override public Object correct(Object value)
            {
                if(value == null || !(value instanceof List) || ((List<?>) value).isEmpty())
                {
                    Logger.debug("KEX-ConfigSpec", String.format("List on key %s is deemed to need correction. It is null, not a list, or an empty list. Modders, consider defineListAllowEmpty?", path.get(path.size() - 1)));
                    return this.getDefault();
                }
                List<?> list = new ArrayList<>((List<?>) value);
                list.removeIf(elementValidator.negate());
                if(list.isEmpty())
                {
                    Logger.debug("KEX-ConfigSpec", String.format("List on key %s is deemed to need correction. It failed validation.", path.get(path.size() - 1)));
                    return this.getDefault();
                }
                return list;
            }
        }, defaultSupplier);
    }

    public <T> ConfigValue<List<? extends T>> defineListAllowEmpty(String path, List<? extends T> defaultValue, Predicate<Object> elementValidator)
    {
        return this.defineListAllowEmpty(split(path), defaultValue, elementValidator);
    }

    public <T> ConfigValue<List<? extends T>> defineListAllowEmpty(List<String> path, List<? extends T> defaultValue, Predicate<Object> elementValidator)
    {
        return this.defineListAllowEmpty(path, () -> defaultValue, elementValidator);
    }

    public <T> ConfigValue<List<? extends T>> defineListAllowEmpty(String path, Supplier<List<? extends T>> defaultSupplier, Predicate<Object> elementValidator)
    {
        return this.defineListAllowEmpty(split(path), defaultSupplier, elementValidator);
    }

    public <T> ConfigValue<List<? extends T>> defineListAllowEmpty(List<String> path, Supplier<List<? extends T>> defaultSupplier, Predicate<Object> elementValidator)
    {
        this.context.setClazz(List.class);
        return this.define(path, new ValueSpec(defaultSupplier, getListValidator(elementValidator), this.context, path) {
            @Override public Object correct(Object value)
            {
                if(value == null || !(value instanceof List))
                {
                    Logger.debug("KEX-ConfigSpec", String.format("List on key %s is deemed to need correction, as it is null or not a list.", path.get(path.size() - 1)));
                    return this.getDefault();
                }
                List<?> list = new ArrayList<>((List<?>) value);
                list.removeIf(elementValidator.negate());
                if(list.isEmpty())
                {
                    Logger.debug("KEX-ConfigSpec", String.format("List on key %s is deemed to need correction. It failed validation.", path.get(path.size() - 1)));
                    return this.getDefault();
                }
                return list;
            }
        }, defaultSupplier);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, V defaultValue)
    {
        return this.defineEnum(split(path), defaultValue);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, V defaultValue)
    {
        return this.defineEnum(path, defaultValue, defaultValue.getDeclaringClass().getEnumConstants());
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, V defaultValue, EnumGetMethod converter)
    {
        return this.defineEnum(split(path), defaultValue, converter);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, V defaultValue, EnumGetMethod converter)
    {
        return this.defineEnum(path, defaultValue, converter, defaultValue.getDeclaringClass().getEnumConstants());
    }

    @SuppressWarnings("unchecked")
    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, V defaultValue, V... acceptableValues)
    {
        return this.defineEnum(split(path), defaultValue, acceptableValues);
    }

    @SuppressWarnings("unchecked")
    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, V defaultValue, V... acceptableValues)
    {
        return this.defineEnum(path, defaultValue, (Collection<V>) Arrays.asList(acceptableValues));
    }

    @SuppressWarnings("unchecked")
    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, V defaultValue, EnumGetMethod converter, V... acceptableValues)
    {
        return this.defineEnum(split(path), defaultValue, converter, acceptableValues);
    }

    @SuppressWarnings("unchecked")
    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, V defaultValue, EnumGetMethod converter, V... acceptableValues)
    {
        return this.defineEnum(path, defaultValue, converter, Arrays.asList(acceptableValues));
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, V defaultValue, Collection<V> acceptableValues)
    {
        return this.defineEnum(split(path), defaultValue, acceptableValues);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, V defaultValue, Collection<V> acceptableValues)
    {
        return this.defineEnum(path, defaultValue, EnumGetMethod.NAME_IGNORECASE, acceptableValues);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, V defaultValue, EnumGetMethod converter, Collection<V> acceptableValues)
    {
        return this.defineEnum(split(path), defaultValue, converter, acceptableValues);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, V defaultValue, EnumGetMethod converter, Collection<V> acceptableValues)
    {
        return this.defineEnum(path, defaultValue, converter, obj -> {
            if(obj instanceof Enum) return acceptableValues.contains(obj);
            if(obj == null) return false;
            try {
                return acceptableValues.contains(converter.get(obj, defaultValue.getDeclaringClass()));
            } catch(IllegalArgumentException | ClassCastException e) { return false; }
        });
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, V defaultValue, Predicate<Object> validator)
    {
        return this.defineEnum(split(path), defaultValue, validator);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, V defaultValue, Predicate<Object> validator)
    {
        return this.defineEnum(path, () -> defaultValue, validator, defaultValue.getDeclaringClass());
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, V defaultValue, EnumGetMethod converter, Predicate<Object> validator)
    {
        return this.defineEnum(split(path), defaultValue, converter, validator);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, V defaultValue, EnumGetMethod converter, Predicate<Object> validator)
    {
        return this.defineEnum(path, () -> defaultValue, converter, validator, defaultValue.getDeclaringClass());
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, Supplier<V> defaultSupplier, Predicate<Object> validator, Class<V> clazz)
    {
        return this.defineEnum(split(path), defaultSupplier, validator, clazz);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, Supplier<V> defaultSupplier, Predicate<Object> validator, Class<V> clazz)
    {
        return this.defineEnum(path, defaultSupplier, EnumGetMethod.NAME_IGNORECASE, validator, clazz);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(String path, Supplier<V> defaultSupplier, EnumGetMethod converter, Predicate<Object> validator, Class<V> clazz)
    {
        return this.defineEnum(split(path), defaultSupplier, converter, validator, clazz);
    }

    public <V extends Enum<V>> EnumValue<V> defineEnum(List<String> path, Supplier<V> defaultSupplier, EnumGetMethod converter, Predicate<Object> validator, Class<V> clazz)
    {
        this.context.setClazz(clazz);
        List<String> allowedValues = new ArrayList<>();
        for(V enumConstant : clazz.getEnumConstants())
            if(validator.test(enumConstant))
                allowedValues.add(enumConstant.name());
        this.comment("Allowed values: " + String.join(", ", allowedValues));
        return new EnumValue<V>(this, this.define(path, new ValueSpec(defaultSupplier, validator, this.context, path), defaultSupplier).getPath(), defaultSupplier, converter, clazz);
    }

    public BooleanValue define(String path, boolean defaultValue)
    {
        return this.define(split(path), defaultValue);
    }

    public BooleanValue define(List<String> path, boolean defaultValue)
    {
        return this.define(path, (Supplier<Boolean>)() -> defaultValue);
    }

    public BooleanValue define(String path, Supplier<Boolean> defaultSupplier)
    {
        return this.define(split(path), defaultSupplier);
    }

    public BooleanValue define(List<String> path, Supplier<Boolean> defaultSupplier)
    {
        return new BooleanValue(this, this.define(path, defaultSupplier, o -> {
            if(o instanceof String) return ((String) o).equalsIgnoreCase("true") || ((String) o).equalsIgnoreCase("false");
            return o instanceof Boolean;
        }, Boolean.class).getPath(), defaultSupplier);
    }

    public DoubleValue defineInRange(String path, double defaultValue, double min, double max)
    {
        return this.defineInRange(split(path), defaultValue, min, max);
    }

    public DoubleValue defineInRange(List<String> path, double defaultValue, double min, double max)
    {
        return this.defineInRange(path, (Supplier<Double>)() -> defaultValue, min, max);
    }

    public DoubleValue defineInRange(String path, Supplier<Double> defaultSupplier, double min, double max)
    {
        return this.defineInRange(split(path), defaultSupplier, min, max);
    }

    public DoubleValue defineInRange(List<String> path, Supplier<Double> defaultSupplier, double min, double max)
    {
        return new DoubleValue(this, this.defineInRange(path, defaultSupplier, min, max, Double.class).getPath(), defaultSupplier);
    }

    public IntValue defineInRange(String path, int defaultValue, int min, int max)
    {
        return this.defineInRange(split(path), defaultValue, min, max);
    }

    public IntValue defineInRange(List<String> path, int defaultValue, int min, int max)
    {
        return this.defineInRange(path, (Supplier<Integer>)() -> defaultValue, min, max);
    }

    public IntValue defineInRange(String path, Supplier<Integer> defaultSupplier, int min, int max)
    {
        return this.defineInRange(split(path), defaultSupplier, min, max);
    }

    public IntValue defineInRange(List<String> path, Supplier<Integer> defaultSupplier, int min, int max)
    {
        return new IntValue(this, this.defineInRange(path, defaultSupplier, min, max, Integer.class).getPath(), defaultSupplier);
    }

    public LongValue defineInRange(String path, long defaultValue, long min, long max)
    {
        return this.defineInRange(split(path), defaultValue, min, max);
    }

    public LongValue defineInRange(List<String> path, long defaultValue, long min, long max)
    {
        return this.defineInRange(path, (Supplier<Long>)() -> defaultValue, min, max);
    }

    public LongValue defineInRange(String path, Supplier<Long> defaultSupplier, long min, long max)
    {
        return this.defineInRange(split(path), defaultSupplier, min, max);
    }

    public LongValue defineInRange(List<String> path, Supplier<Long> defaultSupplier, long min, long max)
    {
        return new LongValue(this, this.defineInRange(path, defaultSupplier, min, max, Long.class).getPath(), defaultSupplier);
    }

    public ConfigBuilder comment(String comment)
    {
        this.context.addComment(comment);
        return this;
    }

    public ConfigBuilder comment(String... comment)
    {
        for(int i = 0; i < comment.length; i++) Objects.requireNonNull(comment[i], String.format("Comment string at %d is null.", i));
        for(String s : comment) this.context.addComment(s);
        return this;
    }

    public ConfigBuilder translation(String translationKey)
    {
        this.context.setTranslationKey(translationKey);
        return this;
    }

    public ConfigBuilder worldRestart()
    {
        this.context.worldRestart();
        return this;
    }

    public ConfigBuilder push(String path)
    {
        return this.push(split(path));
    }

    public ConfigBuilder push(List<String> path)
    {
        this.currentPath.addAll(path);
        if(this.context.hasComment())
        {
            this.levelComments.put(new ArrayList<>(this.currentPath), this.context.buildComment(path));
            this.context.clearComment();
        }
        if(this.context.getTranslationKey() != null)
        {
            levelTranslationKeys.put(new ArrayList<>(this.currentPath), this.context.getTranslationKey());
            this.context.setTranslationKey(null);
        }
        this.context.ensureEmpty();
        return this;
    }

    public ConfigBuilder pop()
    {
        return this.pop(1);
    }

    public ConfigBuilder pop(int count)
    {
        if(count > this.currentPath.size()) throw new IllegalArgumentException(String.format("Attempted to pop %d elements when we only had: %d", count, this.currentPath.toString()));
        for(int x = 0; x < count; x++) this.currentPath.remove(this.currentPath.size() - 1);
        return this;
    }

    public <T> Pair<T, ConfigSpec> configure(Function<ConfigBuilder, T> consumer)
    {
        T o = consumer.apply(this);
        return Pair.create(o, this.build());
    }

    public ConfigSpec build()
    {
        this.context.ensureEmpty();
        Config valueCfg = new SimpleConfig(() -> Collections.synchronizedMap(new LinkedHashMap<>()), InMemoryFormat.withSupport(ConfigValue.class::isAssignableFrom));
        this.values.forEach(v -> valueCfg.set(v.getPath(), v));
        ConfigSpec ret = new ConfigSpec(this.storage, valueCfg, this.levelComments, this.levelTranslationKeys);
        this.values.forEach(v -> v.spec = ret);
        return ret;
    }

    private static Predicate<Object> getListValidator(Predicate<Object> listElementValidator)
    {
        return x -> {
            boolean result = x instanceof List;
            if(result) for(Object element : (List<?>) x)
                if(!listElementValidator.test(element))
                {
                    result = false;
                    break;
                }
            return result;
        };
    }

    private static List<String> split(String path)
    {
        return Arrays.asList(path.split("\\."));
    }

}
