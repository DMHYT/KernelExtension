package vsdum.kex.modules.commands.arguments;

import java.util.ArrayList;
import java.util.List;

import android.support.annotation.Nullable;
import vsdum.kex.modules.commands.CommandExecuteCallback;

public abstract class ArgumentBase implements ICommandNode {
    
    public final String name;
    public final CommandArgumentType type;
    public boolean mandatory = true;
    public int fieldOffset = -1;
    @Nullable public CommandExecuteCallback callback = null;
    @Nullable public ICommandNode parent = null;
    public final List<ArgumentBase> children = new ArrayList<>();

    public ArgumentBase(String name, CommandArgumentType type)
    {
        this.name = name;
        this.type = type;
    }

    public ArgumentBase then(ArgumentBase child)
    {
        if(!(child instanceof ArgumentBase))
            throw new IllegalArgumentException("Anything except CommandArgument cannot be passed in CommandArgument.then!");
        this.children.add((ArgumentBase) child);
        child.parent = this;
        return this;
    }

    @Override public ArgumentBase executes(CommandExecuteCallback callback)
    {
        this.callback = callback;
        return this;
    }

    @Override @Nullable public CommandExecuteCallback getCallback()
    {
        return this.callback == null ? this.parent == null ? null : this.parent.getCallback() : this.callback;
    }

}
