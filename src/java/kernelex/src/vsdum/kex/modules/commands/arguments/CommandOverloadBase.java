package vsdum.kex.modules.commands.arguments;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import vsdum.kex.modules.commands.CommandExecuteCallback;

public class CommandOverloadBase implements ICommandNode {
    
    public final String commandName;
    public final int permissionLevel;
    public final List<String> aliases = new ArrayList<>();
    @Nullable public CommandExecuteCallback callback = null;
    public final List<ArgumentBase> children = new ArrayList<>();
    public final Map<String, String> descriptionTranslations = new HashMap<>();

    public CommandOverloadBase(String commandName, int permissionLevel)
    {
        this.commandName = commandName;
        this.permissionLevel = permissionLevel;
    }

    public CommandOverloadBase then(ArgumentBase child)
    {
        this.children.add((ArgumentBase) child);
        child.parent = this;
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

    public CommandOverloadBase setDescription(String description)
    {
        this.descriptionTranslations.putIfAbsent("en", description);
        return this;
    }

    public CommandOverloadBase setDescription(ScriptableObject translations)
    {
        Object[] keys = translations.getAllIds();
        for(int i = 0; i < keys.length; i++)
        {
            Object obj = keys[i];
            if(obj instanceof String)
            {
                String str = (String) obj;
                this.descriptionTranslations.putIfAbsent(str, new StringBuilder().append("").append(translations.get(str, translations)).toString());
            }
        }
        return this;
    }

    public CommandOverloadBase setDescriptionMap(Map<String, String> translations)
    {
        translations.entrySet().forEach(entry -> this.descriptionTranslations.putIfAbsent(entry.getKey(), entry.getValue()));
        return this;
    }

    private static void listLeaves(List<ArgumentBase> result, List<ArgumentBase> children)
    {
        for(int i = 0; i < children.size(); i++)
        {
            ArgumentBase node = (ArgumentBase) children.get(i);
            if(node.children.isEmpty()) result.add(node);
            else listLeaves(result, node.children);
        }
    }

    private static List<ArgumentBase> leafToRoot(ArgumentBase node)
    {
        List<ArgumentBase> result = new ArrayList<>();
        result.add(node);
        ICommandNode parent = node.parent;
        while(parent instanceof ArgumentBase)
        {
            ArgumentBase arg = (ArgumentBase) parent;
            result.add(arg);
            parent = arg.parent;
        }
        return result;
    }

    public List<List<ArgumentBase>> listOverloads()
    {
        List<List<ArgumentBase>> result = new ArrayList<>();
        if(this.children.isEmpty())
        {
            result.add(new ArrayList<>());
            return result;
        }
        List<ArgumentBase> leaves = new ArrayList<>();
        listLeaves(leaves, this.children);
        for(int i = 0; i < leaves.size(); i++)
        {
            List<ArgumentBase> path = leafToRoot(leaves.get(i));
            List<ArgumentBase> overload = new ArrayList<>();
            for(int j = path.size() - 1; j >= 0; j--)
            {
                overload.add(path.get(j));
            }
            result.add(overload);
        }
        return result;
    }

}
