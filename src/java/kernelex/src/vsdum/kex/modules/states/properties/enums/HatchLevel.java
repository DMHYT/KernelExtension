package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum HatchLevel implements IStringSerializable {

    NO_CRACKS("no_cracks"),
    CRACKED("cracked"),
    MAX_CRACKED("max_cracked");

    private final String name;

    private HatchLevel(String name)
    {
        this.name = name;
    }

    @Override public final String toString()
    {
        return this.name;
    }

}
