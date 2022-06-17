package vsdum.kex.modules.commands;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import android.support.annotation.Nullable;
import vsdum.kex.modules.CommandsModule;

public final class CommandArgumentType {

    public static final CommandArgumentType INT = new CommandArgumentType(0, 4, null);
    public static final CommandArgumentType FLOAT = new CommandArgumentType(1, 4, null);
    public static final CommandArgumentType BOOL = new CommandArgumentType(2, 4, "Boolean");
    public static final CommandArgumentType RELATIVE_FLOAT = new CommandArgumentType(3, 8, null);
    public static final CommandArgumentType POSITION = new CommandArgumentType(4, 16, null);
    public static final CommandArgumentType FLOAT_POSITION = new CommandArgumentType(5, 16, null);
    public static final CommandArgumentType STRING = new CommandArgumentType(6, 12, null);
    public static final CommandArgumentType MESSAGE = new CommandArgumentType(7, 12, null);
    public static final CommandArgumentType WILDCARD_INT = new CommandArgumentType(8, 8, null);
    public static final CommandArgumentType JSON = new CommandArgumentType(9, 16, null);
    public static final CommandArgumentType ENTITY = new CommandArgumentType(10, 140, null);
    public static final CommandArgumentType PLAYER = new CommandArgumentType(11, 140, null);
    public static final CommandArgumentType ITEM = new CommandArgumentType(12, 8, "Item");
    public static final CommandArgumentType BLOCK = new CommandArgumentType(13, 4, "Block");
    public static final CommandArgumentType EFFECT = new CommandArgumentType(14, 4, "Effect");

    public static final CommandArgumentType[] lookup = new CommandArgumentType[]{ INT, FLOAT, BOOL, RELATIVE_FLOAT, POSITION, FLOAT_POSITION, STRING, MESSAGE, WILDCARD_INT, JSON, ENTITY, PLAYER, ITEM, BLOCK, EFFECT };

    private static final Set<String> literals = new HashSet<>();
    
    public final int type;
    public final int sizeof;
    @Nullable public final String enumName;

    private CommandArgumentType(int type, int sizeof, @Nullable String enumName)
    {
        this.type = type;
        this.sizeof = sizeof;
        this.enumName = enumName;
    }

    public static CommandArgumentType enumArgument(String name)
    {
        return new CommandArgumentType(15, 4, name);
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
        return enumArgument(literalEnum);
    }

}
