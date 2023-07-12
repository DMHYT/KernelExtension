package vsdum.kex.modules.states.properties.enums;

import vsdum.kex.common.IStringSerializable;

public enum StructureVoidType implements IStringSerializable {

    VOID, AIR;

    @Override public final String toString()
    {
        return this == VOID ? "void" : "air";
    }

}
