package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum PillarAxis implements IStringSerializable {

    Y("y"), X("x"), Z("z");

    private final String name;

    private PillarAxis(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
