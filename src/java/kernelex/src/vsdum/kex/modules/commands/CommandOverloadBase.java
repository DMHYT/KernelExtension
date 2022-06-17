package vsdum.kex.modules.commands;

import java.util.ArrayList;
import java.util.List;

import android.support.annotation.Nullable;

public class CommandOverloadBase implements ICommandNode {
    
    public final String commandName;
    public final int permissionLevel;
    public final List<String> aliases = new ArrayList<>();
    @Nullable public CommandExecuteCallback callback = null;
    public final List<CommandArgument> children = new ArrayList<>();

    public CommandOverloadBase(String commandName, int permissionLevel)
    {
        this.commandName = commandName;
        this.permissionLevel = permissionLevel;
    }

    @Override public CommandOverloadBase then(ICommandNode child)
    {
        if(!(child instanceof CommandArgument))
            throw new IllegalArgumentException("Anything except CommandArgument cannot be passed in CommandOverloadBase.then!");
        this.children.add((CommandArgument) child);
        child.setParent(this);
        return this;
    }

    @Override public CommandOverloadBase executes(CommandExecuteCallback callback)
    {
        this.callback = callback;
        return this;
    }

    @Override @Nullable public CommandExecuteCallback getCallback()
    {
        return this.callback;
    }

    @Override public void setParent(ICommandNode parent) {}

    public CommandOverloadBase addAlias(String alias)
    {
        this.aliases.add(alias);
        return this;
    }

    public CommandOverloadBase addAliases(String[] aliasesArr)
    {
        for(int i = 0; i < aliasesArr.length; ++i) this.aliases.add(aliasesArr[i]);
        return this;
    }

    private static void listLeaves(List<CommandArgument> result, List<CommandArgument> children)
    {
        for(int i = 0; i < children.size(); i++)
        {
            CommandArgument node = (CommandArgument) children.get(i);
            if(node.children.isEmpty()) result.add(node);
            else listLeaves(result, node.children);
        }
    }

    private static List<CommandArgument> leafToRoot(CommandArgument node)
    {
        List<CommandArgument> result = new ArrayList<>();
        result.add(node);
        ICommandNode parent = node.parent;
        while(parent instanceof CommandArgument)
        {
            CommandArgument arg = (CommandArgument) parent;
            result.add(arg);
            parent = arg.parent;
        }
        return result;
    }

    public List<List<CommandArgument>> listOverloads()
    {
        List<List<CommandArgument>> result = new ArrayList<>();
        if(this.children.isEmpty())
        {
            result.add(new ArrayList<>());
            return result;
        }
        List<CommandArgument> leaves = new ArrayList<>();
        listLeaves(leaves, this.children);
        for(int i = 0; i < leaves.size(); i++)
        {
            List<CommandArgument> path = leafToRoot(leaves.get(i));
            List<CommandArgument> overload = new ArrayList<>();
            for(int j = path.size() - 1; j >= 0; j--)
            {
                overload.add(path.get(j));
            }
            result.add(overload);
        }
        return result;
    }

}
