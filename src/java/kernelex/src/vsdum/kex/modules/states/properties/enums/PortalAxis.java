package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum PortalAxis implements IStringSerializable {

    UNKNOWN("unknown"), X("x"), Z("z");

    private final String name;

    private PortalAxis(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
