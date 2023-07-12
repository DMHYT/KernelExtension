package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum WallConnectionType implements IStringSerializable {

    NONE("none"), SHORT("short"), TALL("tall");

    private final String name;

    private WallConnectionType(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
