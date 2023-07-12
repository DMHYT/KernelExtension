package vsdum.kex.modules.states.properties;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.function.Predicate;

import vsdum.kex.common.IStringSerializable;

public class EnumProperty<T extends Enum<T> & IStringSerializable> extends Property<T> {

    private final Set<T> possibleValues = new HashSet<>();
    private final Map<Integer, Integer> objectToIndex = new HashMap<>();
    private final Map<Integer, T> indexToObject = new HashMap<>();
    private final IntegerProperty integerCopy;
    
    protected EnumProperty(long ptr, String name, int id, Class<T> enumClass, Collection<T> collection)
    {
        super(ptr, name, id, enumClass);
        int index = 0;
        for(T enumValue : collection)
        {
            this.possibleValues.add(enumValue);
            this.objectToIndex.put(enumValue.ordinal(), index);
            this.indexToObject.put(index, enumValue);
            index++;
        }
        this.integerCopy = new IntegerProperty(ptr, name, id, 0, this.possibleValues.size() - 1);
    }

    @Override public boolean equals(Object other)
    {
        if(other == this) return true;
        if(!(other instanceof EnumProperty)) return false;
        if(!super.equals(other)) return false;
        return this.possibleValues.equals(((EnumProperty<?>) other).possibleValues);
    }

    @Override public int generateHashCode()
    {
        int hash = super.generateHashCode();
        hash = 31 * hash + this.possibleValues.hashCode();
        hash = 31 * hash + this.objectToIndex.hashCode();
        return hash;
    }

    @Override public Collection<T> getPossibleValues()
    {
        return this.possibleValues;
    }

    @Override public int getIndex(T value)
    {
        return this.objectToIndex.containsKey(value.ordinal()) ? this.objectToIndex.get(value.ordinal()) : -1;
    }

    @Override public Optional<T> getValue(int index)
    {
        return this.indexToObject.containsKey(index) ? Optional.of(this.indexToObject.get(index)) : Optional.empty();
    }

    public final IntegerProperty toIntegerProperty()
    {
        return this.integerCopy;
    }

    public static <T extends Enum<T> & IStringSerializable> EnumProperty<T> vanilla(String name, int id, Class<T> enumClass)
    {
        return vanilla(name, id, enumClass, Arrays.asList(enumClass.getEnumConstants()));
    }

    public static <T extends Enum<T> & IStringSerializable> EnumProperty<T> vanilla(String name, int id, Class<T> enumClass, Predicate<T> filter)
    {
        List<T> possibleValues = new ArrayList<>();
        for(T enumMember : enumClass.getEnumConstants())
            if(filter.test(enumMember))
                possibleValues.add(enumMember);
        return vanilla(name, id, enumClass, possibleValues);
    }

    @SafeVarargs
    public static <T extends Enum<T> & IStringSerializable> EnumProperty<T> vanilla(String name, int id, Class<T> enumClass, T... possibleValues)
    {
        return vanilla(name, id, enumClass, Arrays.asList(possibleValues));
    }

    public static <T extends Enum<T> & IStringSerializable> EnumProperty<T> vanilla(String name, int id, Class<T> enumClass, Collection<T> possibleValues)
    {
        return new EnumProperty<>(getVanillaPointer(id), name, id, enumClass, possibleValues);
    }

    public static <T extends Enum<T> & IStringSerializable> EnumProperty<T> create(String name, Class<T> enumClass)
    {
        return create(name, enumClass, Arrays.asList(enumClass.getEnumConstants()));
    }

    public static <T extends Enum<T> & IStringSerializable> EnumProperty<T> create(String name, Class<T> enumClass, Predicate<T> filter)
    {
        List<T> possibleValues = new ArrayList<>();
        for(T enumMember : enumClass.getEnumConstants())
            if(filter.test(enumMember))
                possibleValues.add(enumMember);
        return create(name, enumClass, possibleValues);
    }

    @SafeVarargs
    public static <T extends Enum<T> & IStringSerializable> EnumProperty<T> create(String name, Class<T> enumClass, T... possibleValues)
    {
        return create(name, enumClass, Arrays.asList(possibleValues));
    }

    public static <T extends Enum<T> & IStringSerializable> EnumProperty<T> create(String name, Class<T> enumClass, Collection<T> possibleValues)
    {
        if(statesByName.containsKey(name)) throw new IllegalArgumentException(String.format("Block state with name %s has already been registered by vanilla or by KEX API! Try using another name.", name));
        int id = idSource.getOrGenerateId(name, 1024, Integer.MAX_VALUE, true);
        long ptr = nativeCreateIntegerProperty(name, id, possibleValues.size());
        return new EnumProperty<>(ptr, name, id, enumClass, possibleValues);
    }

}
