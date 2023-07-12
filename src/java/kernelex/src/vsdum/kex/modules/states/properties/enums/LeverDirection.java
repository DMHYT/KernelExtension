package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum LeverDirection implements IStringSerializable {

    DOWN_EAST_WEST("down_east_west"),
    EAST("east"),
    WEST("west"),
    SOUTH("south"),
    NORTH("north"),
    UP_NORTH_SOUTH("up_north_south"),
    UP_EAST_WEST("up_east_west"),
    DOWN_NORTH_SOUTH("down_north_south");

    private final String name;

    private LeverDirection(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
