package vsdum.kex.modules.commands;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import vsdum.kex.modules.commands.arguments.ArgumentBase;

public class CommandOverload {

    public final List<ArgumentBase> arguments;
    public final int index;
    public final Map<String, ArgumentBase> argumentsByName = new HashMap<>();

    public CommandOverload(List<ArgumentBase> args, int index)
    {
        this.arguments = args;
        this.index = index;
        Iterator<ArgumentBase> iter = this.arguments.iterator();
        while(iter.hasNext())
        {
            ArgumentBase arg = iter.next();
            this.argumentsByName.put(arg.name, arg);
        }
    }

}
