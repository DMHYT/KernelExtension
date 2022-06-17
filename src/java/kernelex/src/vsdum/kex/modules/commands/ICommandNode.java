package vsdum.kex.modules.commands;

import android.support.annotation.Nullable;

public interface ICommandNode {
    
    public ICommandNode then(ICommandNode child);

    public ICommandNode executes(CommandExecuteCallback callback);

    @Nullable public CommandExecuteCallback getCallback();

    public void setParent(ICommandNode parent);

}
