package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum AnvilDamage implements IStringSerializable {

    UNDAMAGED("undamaged"),
    SLIGHTLY_DAMAGED("slightly_damaged"),
    VERY_DAMAGED("very_damaged"),
    BROKEN("broken");

    private final String name;

    private AnvilDamage(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
