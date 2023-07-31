package vsdum.kex.japi.config.builder;

import java.util.function.Predicate;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

public class Range<V extends Comparable<? super V>> implements Predicate<Object> {

    private final Class<? extends V> clazz;
    private final V min;
    private final V max;

    public Range(Class<V> clazz, V min, V max)
    {
        this.clazz = clazz;
        this.min = min;
        this.max = max;
    }

    public Class<? extends V> getClazz()
    {
        return this.clazz;
    }

    public V getMin()
    {
        return this.min;
    }

    public V getMax()
    {
        return this.max;
    }

    private boolean isNumber(Object other)
    {
        return Number.class.isAssignableFrom(this.clazz) && other instanceof Number;
    }

    @Override public boolean test(Object t)
    {
        if(this.isNumber(t))
        {
            Number n = (Number) t;
            boolean result = ((Number) this.min).doubleValue() <= n.doubleValue() && n.doubleValue() <= ((Number) this.max).doubleValue();
            if(!result) Logger.debug("KEX-ConfigSpec", String.format("Range value %f is not within its bounds %f-%f", n.doubleValue(), ((Number) this.min).doubleValue(), ((Number) this.max).doubleValue()));
            return result;
        }
        if(!this.clazz.isInstance(t)) return false;
        V c = this.clazz.cast(t);
        boolean result = c.compareTo(this.min) >= 0 && c.compareTo(this.max) <= 0;
        if(!result) Logger.debug("KEX-ConfigSpec", String.format("Range value %s is not within its bounds %s-%s", c.toString(), this.min.toString(), this.max.toString()));
        return result;
    }

    public Object correct(Object value, Object def)
    {
        if(this.isNumber(value))
        {
            Number n = (Number) value;
            return n.doubleValue() < ((Number) this.min).doubleValue() ? this.min : n.doubleValue() > ((Number) this.max).doubleValue() ? this.max : value;
        }
        if(!this.clazz.isInstance(value)) return def;
        V c = this.clazz.cast(value);
        return c.compareTo(this.min) < 0 ? this.min : c.compareTo(this.max) > 0 ? this.max : value;
    }

    @Override public String toString()
    {
        if(this.clazz == Integer.class)
        {
            if(this.max.equals(Integer.MAX_VALUE)) return "> " + this.min.toString();
            else if(this.min.equals(Integer.MIN_VALUE)) return "< " + this.max.toString();
        }
        return this.min.toString() + " ~ " + this.max.toString();
    }

}
