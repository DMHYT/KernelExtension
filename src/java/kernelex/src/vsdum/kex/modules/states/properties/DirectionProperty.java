package vsdum.kex.modules.states.properties;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.util.function.Predicate;

import vsdum.kex.util.mcmath.Direction;

public class DirectionProperty extends EnumProperty<Direction> {
    
    protected DirectionProperty(long ptr, String name, int id, Collection<Direction> possibleValues)
    {
        super(ptr, name, id, Direction.class, possibleValues);
    }

    public static DirectionProperty vanilla(String name, int id)
    {
        return vanilla(name, id, Arrays.asList(Direction.values()));
    }

    public static DirectionProperty vanilla(String name, int id, Predicate<Direction> filter)
    {
        List<Direction> possibleValues = new ArrayList<>();
        for(Direction dir : Direction.values())
            if(filter.test(dir))
                possibleValues.add(dir);
        return vanilla(name, id, possibleValues);
    }

    @SafeVarargs
    public static DirectionProperty vanilla(String name, int id, Direction... possibleValues)
    {
        return vanilla(name, id, Arrays.asList(possibleValues));
    }

    public static DirectionProperty vanilla(String name, int id, Collection<Direction> possibleValues)
    {
        return new DirectionProperty(getVanillaPointer(id), name, id, possibleValues);
    }

    public static DirectionProperty create(String name)
    {
        return create(name, Arrays.asList(Direction.values()));
    }

    public static DirectionProperty create(String name, Predicate<Direction> filter)
    {
        List<Direction> possibleValues = new ArrayList<>();
        for(Direction dir : Direction.values())
            if(filter.test(dir))
                possibleValues.add(dir);
        return create(name, possibleValues);
    }

    @SafeVarargs
    public static DirectionProperty create(String name, Direction... possibleValues)
    {
        return create(name, Arrays.asList(possibleValues));
    }

    public static DirectionProperty create(String name, Collection<Direction> possibleValues)
    {
        if(statesByName.containsKey(name)) throw new IllegalArgumentException(String.format("Block state with name %s has already been registered by vanilla or by KEX API! Try using another name.", name));
        idScope.add(name);
        long ptr = nativeCreateIntegerProperty(name, 255, possibleValues.size());
        return new DirectionProperty(ptr, name, 255, possibleValues);
    }

}
