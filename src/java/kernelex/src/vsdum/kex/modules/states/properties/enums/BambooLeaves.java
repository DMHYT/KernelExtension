package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum BambooLeaves implements IStringSerializable {

    NONE("none"), SMALL("small"), LARGE("large");

    private final String name;

    private BambooLeaves(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }
    
}
