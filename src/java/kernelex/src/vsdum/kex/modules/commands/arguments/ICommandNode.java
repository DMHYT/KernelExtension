package vsdum.kex.modules.commands.arguments;

import android.support.annotation.Nullable;
import vsdum.kex.modules.commands.CommandExecuteCallback;

public interface ICommandNode {

    public ICommandNode executes(CommandExecuteCallback callback);

    @Nullable public CommandExecuteCallback getCallback();

}
