package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum StalkThickness implements IStringSerializable {

    THIN, THICK;

    @Override public final String toString()
    {
        return this == THIN ? "thin" : "thick";
    }

}
