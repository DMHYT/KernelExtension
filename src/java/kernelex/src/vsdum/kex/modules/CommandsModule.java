package vsdum.kex.modules;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;

import vsdum.kex.modules.commands.CommandArgument;
import vsdum.kex.modules.commands.CommandArgumentType;
import vsdum.kex.modules.commands.CommandOverload;
import vsdum.kex.modules.commands.CommandOverloadBase;
import vsdum.kex.modules.commands.CommandsNativeAPI;

public class CommandsModule {

    private static final Map<String, List<CommandOverload>> executableData = new HashMap<>();

    public static void registerCommand(CommandOverloadBase base)
    {
        long factoryPointer = CommandsNativeAPI.nativeNewCommand(base.commandName, base.permissionLevel, base.aliases.toArray());
        if(factoryPointer == 0L) throw new IllegalArgumentException(String.format("Command with name %s already exists!", new Object[]{ base.commandName }));
        List<List<CommandArgument>> overloads = base.listOverloads();
        for(int i = 0; i < overloads.size(); i++) {
            int offset = 64;
            List<CommandArgument> overload = overloads.get(i);
            executableData.putIfAbsent(base.commandName, new ArrayList<>());
            executableData.get(base.commandName).add(new CommandOverload(overload, i));
            long overloadPointer = CommandsNativeAPI.nativeAddOverload(factoryPointer, i);
            Iterator<CommandArgument> iter = overload.iterator();
            while(iter.hasNext())
            {
                CommandArgument arg = iter.next();
                arg.fieldOffset = offset;
                CommandsNativeAPI.nativeBuildArgument(overloadPointer, arg.name, arg.type.type, arg.type.enumName, arg.mandatory, offset);
                offset += arg.type.sizeof;
            }
        }
    }

    public static CommandOverloadBase newCommand(String name, int permissionLevel)
    {
        return new CommandOverloadBase(name, permissionLevel);
    }

    public static CommandArgument argument(String name, int argumentType)
    {
        if(argumentType < 0 || argumentType > 14) throw new IllegalArgumentException("Argument type in CommandsModule.argument must be between 0 and 14 inclusively!");
        return new CommandArgument(name, CommandArgumentType.lookup[argumentType]);
    }

    public static CommandArgument enumArgument(String name, String enumName)
    {
        return new CommandArgument(name, CommandArgumentType.enumArgument(enumName));
    }

    public static CommandArgument literal(String name, String l)
    {
        return new CommandArgument(name, CommandArgumentType.literalArgument(l));
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
        Object[] keys = values.getAllIds();
        for(int i = 0; i < keys.length; i++) {
            Object o = keys[i];
            if(o instanceof String)
            {
                String key = (String) o;
                int val = ScriptableObjectHelper.getIntProperty(values, key, Integer.MAX_VALUE);
                if(val != Integer.MAX_VALUE) map.put(key, val);
            }
        }
        addEnum(name, map);
    }
    
}
