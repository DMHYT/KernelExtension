package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum BellAttachment implements IStringSerializable {

    FLOOR("floor"),
    CEILING("ceiling"),
    SINGLE_WALL("single_wall"),
    DOUBLE_WALL("double_wall");

    private final String name;

    private BellAttachment(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
