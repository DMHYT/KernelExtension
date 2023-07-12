package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum TorchFacing implements IStringSerializable {

    UNKNOWN("unknown"),
    WEST("west"),
    EAST("east"),
    NORTH("north"),
    SOUTH("south"),
    TOP("top");

    private final String name;

    private TorchFacing(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
