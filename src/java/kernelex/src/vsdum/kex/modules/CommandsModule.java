package vsdum.kex.modules;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;

import vsdum.kex.modules.commands.*;
import vsdum.kex.modules.commands.arguments.*;
import vsdum.kex.modules.commands.enums.*;
import vsdum.kex.util.LangInjector;

public class CommandsModule {

    private static final Map<String, List<CommandOverload>> executableData = new HashMap<>();
    private static final Map<String, Map<String, String>> descriptionTranslations = LangInjector.addSection("CUSTOM COMMAND DESCRIPTIONS");

    public static void registerCommand(CommandOverloadBase base)
    {
        long factoryPointer = CommandsNativeAPI.nativeNewCommand(base.commandName, base.permissionLevel, base.aliases.toArray());
        if(factoryPointer == 0L) throw new IllegalArgumentException(String.format("Command with name %s already exists!", base.commandName));
        List<List<ArgumentBase>> overloads = base.listOverloads();
        for(int i = 0; i < overloads.size(); i++) {
            int offset = 36;
            List<ArgumentBase> overload = overloads.get(i);
            executableData.putIfAbsent(base.commandName, new ArrayList<>());
            executableData.get(base.commandName).add(new CommandOverload(overload, i));
            long overloadPointer = CommandsNativeAPI.nativeAddOverload(factoryPointer, i);
            for(ArgumentBase arg : overload)
            {
                arg.mandatory = arg.parent.getCallback() == null;
                arg.fieldOffset = offset;
                buildArgument(overloadPointer, arg);
                offset += arg.type.sizeof;
            }
            Logger.debug("KEX-CommandRegistry", String.format("Overload %d for command %s built, used %d bytes out of %d possible.", i, base.commandName, offset - 36, (2012 - overload.size()) / 4 * 4));
        }
        base.descriptionTranslations.forEach((language, translation) -> {
            String code = LangInjector.validateLanguageCode(language);
            if(code != null)
            {
                descriptionTranslations.putIfAbsent(code, new HashMap<>());
                descriptionTranslations.get(code).put("commands." + base.commandName + ".description", translation);
            }
        });
    }

    public static void registerCustomParserCommand(String name, CustomParserCommandExecuteCallback callback)
    {
        registerCustomParserCommand(name, callback, 0);
    }

    public static void registerCustomParserCommand(String name, CustomParserCommandExecuteCallback callback, int permissionLevel)
    {
        registerCommand(newCommand(name, permissionLevel)
            .then(messageArg("{...}")
                .executes(ctx -> callback.execute(ctx.getMessage("{...}"), ctx))
            )
        );
    }

    public static CommandOverloadBase newCommand(String name)
    {
        return newCommand(name, 0);
    }

    public static CommandOverloadBase newCommand(String name, int permissionLevel)
    {
        return new CommandOverloadBase(name, permissionLevel);
    }

    public static native void registerAlias(String name, String alias);

    public static void addEnum(String name, Map<String, Integer> values)
    {
        Object[] vals = values.values().toArray();
        int[] valsToPut = new int[vals.length];
        for(int i = 0; i < vals.length; i++) valsToPut[i] = ((Integer) vals[i]).intValue();
        CommandsNativeAPI.nativeAddEnum(name, values.keySet().toArray(), valsToPut);
    }

    public static void addEnum(String name, ScriptableObject values)
    {
        Map<String, Integer> map = new HashMap<>();
        for(Object o : values.getAllIds())
        {
            if(o instanceof String)
            {
                String key = (String) o;
                int val = ScriptableObjectHelper.getIntProperty(values, key, Integer.MAX_VALUE);
                if(val != Integer.MAX_VALUE) map.put(key, val);
            }
        }
        addEnum(name, map);
    }

    public static void addStringEnum(String name, Set<String> values)
    {
        addStringEnum(name, values.toArray());
    }

    public static void addStringEnum(String name, Object[] values)
    {
        CommandsNativeAPI.nativeAddStringEnum(name, values);
    }

    public static EnumBuilder newEnum(String name)
    {
        return new EnumBuilder(name);
    }

    public static StringEnumBuilder newStringEnum(String name)
    {
        return new StringEnumBuilder(name);
    }

    public static IntArgument intArg(String name)
    {
        return new IntArgument(name);
    }

    public static IntArgument intArg(String name, int defaultValue)
    {
        return new IntArgument(name, defaultValue);
    }

    public static FloatArgument floatArg(String name)
    {
        return new FloatArgument(name);
    }

    public static FloatArgument floatArg(String name, float defaultValue)
    {
        return new FloatArgument(name, defaultValue);
    }

    public static BoolArgument boolArg(String name)
    {
        return new BoolArgument(name);
    }

    public static BoolArgument boolArg(String name, boolean defaultValue)
    {
        return new BoolArgument(name, defaultValue);
    }

    public static FloatArgument relativeFloatArg(String name)
    {
        return new FloatArgument(name, 0.0f, true);
    }

    public static FloatArgument relativeFloatArg(String name, float defaultValue)
    {
        return new FloatArgument(name, defaultValue, true);
    }

    public static PositionArgument positionArg(String name)
    {
        return new PositionArgument(name);
    }

    public static PositionArgument positionArg(String name, float defaultX, float defaultY, float defaultZ)
    {
        return new PositionArgument(name, defaultX, defaultY, defaultZ);
    }

    public static PositionArgument floatPositionArg(String name)
    {
        return new PositionArgument(name, 0.0f, 0.0f, 0.0f, true);
    }

    public static PositionArgument floatPositionArg(String name, float defaultX, float defaultY, float defaultZ)
    {
        return new PositionArgument(name, defaultX, defaultY, defaultZ, true);
    }

    public static StringArgument stringArg(String name)
    {
        return new StringArgument(name);
    }

    public static StringArgument stringArg(String name, String defaultValue)
    {
        return new StringArgument(name, defaultValue);
    }

    public static MessageArgument messageArg(String name)
    {
        return new MessageArgument(name);
    }

    public static JsonArgument jsonArg(String name)
    {
        return new JsonArgument(name);
    }

    public static EntityArgument entityArg(String name)
    {
        return new EntityArgument(name);
    }

    public static PlayerArgument playerArg(String name)
    {
        return new PlayerArgument(name);
    }

    public static IntArgument enumArg(String name, String enumName)
    {
        return new IntArgument(name, 0, enumName);
    }

    public static IntArgument enumArg(String name, String enumName, int defaultValue)
    {
        return new IntArgument(name, defaultValue, enumName);
    }

    public static StringArgument stringEnumArg(String name, String enumName, String defaultValue)
    {
        return new StringArgument(name, defaultValue, enumName);
    }

    public static LiteralArgument literal(String name)
    {
        return new LiteralArgument(name);
    }

    public static void callAPICommand(String commandName, long commandPtr, int overloadIndex, long originPtr, long outputPtr, boolean[] paramsPresence)
    {
        CommandOverload overload = executableData.get(commandName).get(overloadIndex);
        CommandExecuteCallback lastCallbackFound = null;
        if(overload.arguments.size() != paramsPresence.length) throw new IllegalStateException("Something went wrong, arguments count does not match their presence flags count!");
        for(int i = 0; i < overload.arguments.size(); i++)
        {
            ArgumentBase arg = overload.arguments.get(i);
            if(paramsPresence[i])
            {
                lastCallbackFound = arg.getCallback();
            }
        }
        if(lastCallbackFound != null)
        {
            try {
                lastCallbackFound.execute(new CommandContext(commandPtr, originPtr, outputPtr, overload.argumentsByName));
            } catch(Throwable ex) { ex.printStackTrace(); }
        }
    }

    private static void buildArgument(long vectorPtr, ArgumentBase arg)
    {
        switch(arg.type.type)
        {
            case 0: CommandsNativeAPI.nativeBuildIntArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset, ((IntArgument) arg).defaultValue); break;
            case 1: CommandsNativeAPI.nativeBuildFloatArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset, ((FloatArgument) arg).defaultValue); break;
            case 2: CommandsNativeAPI.nativeBuildBoolArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset, ((BoolArgument) arg).defaultValue); break;
            case 3: CommandsNativeAPI.nativeBuildRelativeFloatArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset, ((FloatArgument) arg).defaultValue); break;
            case 4: CommandsNativeAPI.nativeBuildPositionArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset, ((PositionArgument) arg).x, ((PositionArgument) arg).y, ((PositionArgument) arg).z); break;
            case 5: CommandsNativeAPI.nativeBuildFloatPositionArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset, ((PositionArgument) arg).x, ((PositionArgument) arg).y, ((PositionArgument) arg).z); break;
            case 6: CommandsNativeAPI.nativeBuildStringArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset, ((StringArgument) arg).defaultValue); break;
            case 7: CommandsNativeAPI.nativeBuildMessageArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset); break;
            case 8: CommandsNativeAPI.nativeBuildJsonArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset); break;
            case 9: CommandsNativeAPI.nativeBuildEntityArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset); break;
            case 10: CommandsNativeAPI.nativeBuildPlayerArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset); break;
            case 11: CommandsNativeAPI.nativeBuildEnumArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset, arg.type.enumName, arg.type.enumName.startsWith("KEXLITERAL-") ? 0 : ((IntArgument) arg).defaultValue); break;
            case 12: CommandsNativeAPI.nativeBuildStringEnumArgument(vectorPtr, arg.name, arg.mandatory, arg.fieldOffset, arg.type.enumName, ((StringArgument) arg).defaultValue); break;
            default: throw new IllegalArgumentException(String.format("Invalid command argument type %d", arg.type.type));
        }
    }
    
}
