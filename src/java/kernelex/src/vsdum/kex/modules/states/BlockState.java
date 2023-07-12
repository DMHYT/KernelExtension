package vsdum.kex.modules.states;

import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Optional;
import java.util.Set;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import vsdum.kex.japi.blocks.Block;
import vsdum.kex.japi.blocks.BlockRegistry;
import vsdum.kex.japi.blocks.components.IHasBlockActor;
import vsdum.kex.japi.blocks.components.IMirrorable;
import vsdum.kex.japi.blocks.components.IRotatable;
import vsdum.kex.modules.states.properties.Property;
import vsdum.kex.util.mcmath.Mirror;
import vsdum.kex.util.mcmath.Rotation;

public class BlockState {

    protected static native long blockLongFromRuntimeID(int runtimeID);
    protected static native boolean nativeHasState(int id, long statePtr);
    protected static native int nativeGet(int runtimeID, long statePtr);
    protected static native int nativeSet(int runtimeID, long statePtr, int value);

    private static final Map<Integer, Set<Property<?>>> propertiesById = new HashMap<>();

    private final int runtimeID;
    public final int id;
    public final int data;

    public BlockState(long idDataAndState) {
        long idData = idDataAndState & 0xFFFFFFFFL;
        this.id = (int) (idData >> 16L) & 0xFFFF;
        this.data = (int) (idData & 0xFFFFL);
        this.runtimeID = (int) (idDataAndState >> 32L);
    }

    public final int getRuntimeID()
    {
        return this.runtimeID;
    }

    @Nullable public final Block getBlock()
    {
        return BlockRegistry.getBlockById(this.id);
    }

    public final boolean is(@NonNull Block block)
    {
        return this.id == block.id;
    }

    public final boolean hasBlockEntity()
    {
        return this.getBlock() instanceof IHasBlockActor;
    }

    public Collection<Property<?>> getProperties()
    {
        return getOrCreatePropertiesById(this.id);
    }

    public <T extends Comparable<T>> boolean hasProperty(Property<T> property)
    {
        return getProperties().contains(property);
    }

    public <T extends Comparable<T>> T getValue(Property<T> property)
    {
        return property.getValue(nativeGet(this.runtimeID, property.getPointer())).get();
    }

    public <T extends Comparable<T>> Optional<T> getOptionalValue(Property<T> property)
    {
        return this.hasProperty(property) ? Optional.of(this.getValue(property)) : Optional.empty();
    }

    public <T extends Comparable<T>, V extends T> BlockState setValue(Property<T> property, V value)
    {
        int newRuntimeID = nativeSet(this.runtimeID, property.getPointer(), property.getIndex(value));
        return newRuntimeID == this.runtimeID ? this : new BlockState(blockLongFromRuntimeID(newRuntimeID));
    }

    public <T extends Comparable<T>> BlockState cycle(Property<T> property)
    {
        return this.setValue(property, findNextInCollection(property.getPossibleValues(), this.getValue(property)));
    }

    public BlockState rotate(Rotation rotation)
    {
        Block block = this.getBlock();
        if(block == null || !(block instanceof IRotatable)) return this;
        return ((IRotatable) block).rotate(this, rotation);
    }

    public BlockState mirror(Mirror m)
    {
        Block block = this.getBlock();
        if(block == null || !(block instanceof IMirrorable)) return this;
        return ((IMirrorable) block).mirror(this, m);
    }

    protected static <T> T findNextInCollection(Collection<T> possibleValues, T currentValue)
    {
        Iterator<T> iter = possibleValues.iterator();
        while(iter.hasNext())
            if(iter.next().equals(currentValue))
                return iter.hasNext() ? iter.next() : possibleValues.iterator().next();
        return iter.next();
    }

    private static Set<Property<?>> getOrCreatePropertiesById(int id)
    {
        if(!propertiesById.containsKey(id))
        {
            Set<Property<?>> propertiesSet = new HashSet<>();
            for(Property<?> property : Property.statesById.values())
                if(nativeHasState(id, property.getPointer()))
                    propertiesSet.add(property);
            propertiesById.put(id, propertiesSet);
        }
        return propertiesById.get(id);
    }

}
