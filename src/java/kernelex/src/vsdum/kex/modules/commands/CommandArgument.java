package vsdum.kex.modules.commands;

import java.util.ArrayList;
import java.util.List;

import android.support.annotation.Nullable;

public class CommandArgument implements ICommandNode {
    
    public final String name;
    public final CommandArgumentType type;
    public boolean mandatory = true;
    public int fieldOffset = -1;
    @Nullable public CommandExecuteCallback callback = null;
    @Nullable public ICommandNode parent = null;
    public final List<CommandArgument> children = new ArrayList<>();

    public CommandArgument(String name, CommandArgumentType type)
    {
        this.name = name;
        this.type = type;
    }

    @Override public CommandArgument then(ICommandNode child)
    {
        if(!(child instanceof CommandArgument))
            throw new IllegalArgumentException("Anything except CommandArgument cannot be passed in CommandArgument.then!");
        this.children.add((CommandArgument) child);
        child.setParent(this);
        return this;
    }

    @Override public CommandArgument executes(CommandExecuteCallback callback)
    {
        this.callback = callback;
        return this;
    }

    @Override @Nullable public CommandExecuteCallback getCallback()
    {
        return this.callback;
    }

    @Override public void setParent(ICommandNode parent)
    {
        this.parent = parent;
        if(this.parent.getCallback() != null)
        {
            this.mandatory = false;
        }
    }

}
