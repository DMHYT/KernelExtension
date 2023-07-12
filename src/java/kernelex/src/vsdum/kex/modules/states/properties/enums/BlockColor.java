package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum BlockColor implements IStringSerializable {

    WHITE("white"),
    ORANGE("orange"),
    MAGENTA("magenta"),
    LIGHT_BLUE("light_blue"),
    YELLOW("yellow"),
    LIME("lime"),
    PINK("pink"),
    GRAY("gray"),
    SILVER("silver"),
    CYAN("cyan"),
    PURPLE("purple"),
    BLUE("blue"),
    BROWN("brown"),
    GREEN("green"),
    RED("red"),
    BLACK("black");

    private final String name;

    private BlockColor(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
