package vsdum.kex.modules.states.properties;

import java.util.Collection;
import java.util.Optional;
import java.util.Set;

import vsdum.kex.util.SetBuilder;

public class BooleanProperty extends Property<Boolean> {

    private static final Set<Boolean> possibleValues = new SetBuilder<Boolean>().add(true).add(false).build();

    protected BooleanProperty(long ptr, String name, int id)
    {
        super(ptr, name, id, Boolean.class);
    }

    @Override public boolean equals(Object other)
    {
        if(other == this) return true;
        if(!(other instanceof BooleanProperty)) return false;
        return super.equals(other);
    }

    @Override public int generateHashCode()
    {
        return 31 * super.generateHashCode() + possibleValues.hashCode();
    }

    @Override public Collection<Boolean> getPossibleValues()
    {
        return possibleValues;
    }

    @Override public int getIndex(Boolean value)
    {
        return value.booleanValue() ? 1 : 0;
    }

    @Override public Optional<Boolean> getValue(int index)
    {
        return index == 0 ? Optional.of(false) : index == 1 ? Optional.of(true) : Optional.empty();
    }

    public static BooleanProperty vanilla(String name, int id)
    {
        return new BooleanProperty(getVanillaPointer(id), name, id);
    }

    public static BooleanProperty create(String name)
    {
        if(statesByName.containsKey(name)) throw new IllegalArgumentException(String.format("Block state with name %s has already been registered by vanilla or by KEX API! Try using another name.", name));
        int id = idSource.getOrGenerateId(name, 1024, Integer.MAX_VALUE, true);
        long ptr = nativeCreateBooleanProperty(name, id);
        return new BooleanProperty(ptr, name, id);
    }

}
