package vsdum.kex.modules.commands;

import java.util.List;

public class CommandOverload {

    public final List<CommandArgument> arguments;
    public final int index;

    public CommandOverload(List<CommandArgument> args, int index)
    {
        this.arguments = args;
        this.index = index;
    }

}
