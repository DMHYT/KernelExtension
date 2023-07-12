package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum StructureBlockType implements IStringSerializable {

    DATA("data"),
    SAVE("save"),
    LOAD("load"),
    CORNER("corner"),
    INVALID("invalid"),
    EXPORT("export");

    private final String name;

    private StructureBlockType(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
