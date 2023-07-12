package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum CoralColor implements IStringSerializable {

    BLUE("blue"),
    PINK("pink"),
    PURPLE("purple"),
    RED("red"),
    YELLOW("yellow");

    private final String name;

    private CoralColor(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
