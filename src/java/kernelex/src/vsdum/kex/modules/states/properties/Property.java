package vsdum.kex.modules.states.properties;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

import vsdum.kex.common.INativeInterface;
import vsdum.kex.util.AlphabeticIDSource;

public abstract class Property<T extends Comparable<T>> implements INativeInterface {

    protected static native long getVanillaPointer(int id);
    protected static native long nativeCreateIntegerProperty(String name, int id, int possibleValuesCount);
    protected static native long nativeCreateBooleanProperty(String name, int id);
    private static native void nativeSetNumericID(long ptr, int id);

    public static final Map<Integer, Property<?>> statesById = new HashMap<>();
    public static final Map<String, Property<?>> statesByName = new HashMap<>();

    protected static final AlphabeticIDSource.Scope idScope = AlphabeticIDSource.instance()
        .createScope("blockstates", 256, scopeData -> {
            statesByName.values().forEach(property -> {
                int numericID = scopeData.getNumericID(property.name);
                property.setNumericID(numericID);
                statesById.put(numericID, property);
            });
        });
    
    private final long pointer;
    private final String name;
    private int id;
    private final Class<T> valueClass;
    private Integer hash = null;

    protected Property(long ptr, String name, int id, Class<T> valueClass)
    {
        this.pointer = ptr;
        this.name = name;
        this.id = id;
        this.valueClass = valueClass;
        if(!statesByName.containsKey(name))
        {
            statesByName.put(this.name, this);
        }
    }

    private final void setNumericID(int id)
    {
        this.id = id;
        nativeSetNumericID(this.pointer, this.id);
    }

    @Override public final long getPointer()
    {
        return this.pointer;
    }

    @Override public boolean equals(Object other)
    {
        if(other == this) return true;
        if(!(other instanceof Property)) return false;
        Property<?> otherProperty = (Property<?>) other;
        return this.valueClass.equals(otherProperty.valueClass) && this.name.equals(otherProperty.name) && this.id == otherProperty.id;
    }

    @Override public final int hashCode()
    {
        if(this.hash == null) this.hash = this.generateHashCode();
        return this.hash.intValue();
    }

    public int generateHashCode()
    {
        return 31 * this.valueClass.hashCode() + this.name.hashCode();
    }

    public final String getName()
    {
        return this.name;
    }

    public final int getNumericID()
    {
        return this.id;
    }

    public final Class<T> getValueClass()
    {
        return this.valueClass;
    }

    public abstract int getIndex(T value);

    public abstract Collection<T> getPossibleValues();

    public abstract Optional<T> getValue(int index);

}
