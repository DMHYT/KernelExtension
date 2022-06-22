package vsdum.kex.modules.commands.arguments;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import android.support.annotation.Nullable;
import vsdum.kex.modules.CommandsModule;

public final class CommandArgumentType {

    public static final CommandArgumentType INT = new CommandArgumentType(0, 4, null, "Integer");
    public static final CommandArgumentType FLOAT = new CommandArgumentType(1, 4, null, "Float");
    public static final CommandArgumentType BOOL = new CommandArgumentType(2, 4, "Boolean", "Boolean");
    public static final CommandArgumentType RELATIVE_FLOAT = new CommandArgumentType(3, 8, null, "RelativeFloat");
    public static final CommandArgumentType POSITION = new CommandArgumentType(4, 16, null, "Position");
    public static final CommandArgumentType FLOAT_POSITION = new CommandArgumentType(5, 16, null, "FloatPosition");
    public static final CommandArgumentType STRING = new CommandArgumentType(6, 12, null, "String");
    public static final CommandArgumentType MESSAGE = new CommandArgumentType(7, 12, null, "Message");
    public static final CommandArgumentType JSON = new CommandArgumentType(8, 16, null, "Json");
    public static final CommandArgumentType ENTITY = new CommandArgumentType(9, 120, null, "Entity");
    public static final CommandArgumentType PLAYER = new CommandArgumentType(10, 120, null, "Player");

    private static final Set<String> literals = new HashSet<>();
    
    public final int type;
    public final int sizeof;
    @Nullable public final String enumName;
    public final String typeName;

    private CommandArgumentType(int type, int sizeof, @Nullable String enumName, String typeName)
    {
        this.type = type;
        this.sizeof = sizeof;
        this.enumName = enumName;
        this.typeName = typeName;
    }

    public static CommandArgumentType enumArgument(String name)
    {
        return new CommandArgumentType(11, 4, name, "Enum");
    }

    public static CommandArgumentType stringEnumArgument(String name)
    {
        return new CommandArgumentType(12, 12, name, "StringEnum");
    }

    public static CommandArgumentType literalArgument(String literal)
    {
        String literalEnum = "KEXLITERAL-" + literal;
        if(!literals.contains(literal))
        {
            literals.add(literal);
            Map<String, Integer> enumValues = new HashMap<>();
            enumValues.put(literal, 0);
            CommandsModule.addEnum(literalEnum, enumValues);
        }
        return new CommandArgumentType(11, 4, literalEnum, "Literal");
    }

    @Override public String toString()
    {
        if(this.enumName == null) return this.typeName;
        return this.typeName + "(" + this.enumName + ")";
    }

}
