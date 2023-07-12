package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum RailShape implements IStringSerializable {

    NORTH_SOUTH("north_south"),
    EAST_WEST("east_west"),
    ASCENDING_EAST("ascending_east"),
    ASCENDING_WEST("ascending_west"),
    ASCENDING_NORTH("ascending_north"),
    ASCENDING_SOUTH("ascending_south"),
    SOUTH_EAST("south_east"),
    SOUTH_WEST("south_west"),
    NORTH_WEST("north_west"),
    NORTH_EAST("north_east");

    private final String name;

    private RailShape(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
