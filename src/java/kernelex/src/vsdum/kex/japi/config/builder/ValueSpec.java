package vsdum.kex.japi.config.builder;

import java.util.List;
import java.util.Objects;
import java.util.function.Predicate;
import java.util.function.Supplier;

public class ValueSpec {

    private final String comment;
    private final String langKey;
    private final Range<?> range;
    private final boolean worldRestart;
    private final Class<?> clazz;
    private final Supplier<?> supplier;
    private final Predicate<Object> validator;

    ValueSpec(Supplier<?> supplier, Predicate<Object> validator, BuilderContext context, List<String> path)
    {
        Objects.requireNonNull(supplier, "Default supplier cannot be null");
        Objects.requireNonNull(validator, "Validator cannot be null");
        this.comment = context.hasComment() ? context.buildComment(path) : null;
        this.langKey = context.getTranslationKey();
        this.range = context.getRange();
        this.worldRestart = context.needsWorldRestart();
        this.clazz = context.getClazz();
        this.supplier = supplier;
        this.validator = validator;
    }

    public String getComment()
    {
        return this.comment;
    }
    
    public String getTranslationKey()
    {
        return this.langKey;
    }

    @SuppressWarnings("unchecked")
    public <V extends Comparable<? super V>> Range<V> getRange()
    {
        return (Range<V>) this.range;
    }

    public boolean needsWorldRestart()
    {
        return this.worldRestart;
    }

    public Class<?> getClazz()
    {
        return this.clazz;
    }

    public boolean test(Object value)
    {
        return this.validator.test(value);
    }

    public Object correct(Object value)
    {
        return this.range == null ? this.getDefault() : this.range.correct(value, this.getDefault());
    }

    public Object getDefault()
    {
        return this.supplier.get();
    }

}
