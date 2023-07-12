package vsdum.kex.modules.states.properties;

import java.util.Collection;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class IntegerProperty extends Property<Integer> {

    private final Set<Integer> possibleValues;
    private final int indexOffset;

    protected IntegerProperty(long ptr, String name, int id, int min, int max)
    {
        super(ptr, name, id, Integer.class);
        this.possibleValues = new HashSet<>();
        for(int i = min; i <= max; i++) this.possibleValues.add(i);
        this.indexOffset = -min;
    }

    @Override public boolean equals(Object other)
    {
        if(other == this) return true;
        if(!(other instanceof IntegerProperty)) return false;
        if(!super.equals(other)) return false;
        return this.possibleValues.equals(((IntegerProperty) other).possibleValues);
    }

    @Override public int generateHashCode()
    {
        return 31 * super.generateHashCode() + this.possibleValues.hashCode();
    }

    @Override public Collection<Integer> getPossibleValues()
    {
        return this.possibleValues;
    }

    @Override public int getIndex(Integer value)
    {
        return value.intValue() + this.indexOffset;
    }

    @Override public Optional<Integer> getValue(int index)
    {
        return this.possibleValues.contains(index - this.indexOffset) ? Optional.of(index - this.indexOffset) : Optional.empty();
    }

    public static IntegerProperty vanilla(String name, int id, int min, int max)
    {
        return new IntegerProperty(getVanillaPointer(id), name, id, min, max);
    }

    public static IntegerProperty create(String name, int min, int max)
    {
        if(statesByName.containsKey(name)) throw new IllegalArgumentException(String.format("Block state with name %s has already been registered by vanilla or by KEX API! Try using another name.", name));
        if(min < 0) throw new IllegalArgumentException(String.format("Minimum value of IntegerProperty %s must be 0 or greater!", name));
        if(max <= min) throw new IllegalArgumentException(String.format("Maximum value of IntegerProperty %s must be greater than specified minimum value (%d)", name, min));
        int id = idSource.getOrGenerateId(name, 1024, Integer.MAX_VALUE, true);
        long ptr = nativeCreateIntegerProperty(name, id, max - min + 1);
        return new IntegerProperty(ptr, name, id, min, max);
    }

}
