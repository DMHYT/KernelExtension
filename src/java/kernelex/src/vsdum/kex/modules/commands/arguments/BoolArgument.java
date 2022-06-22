package vsdum.kex.modules.commands.arguments;

public class BoolArgument extends ArgumentBase {
    
    public final boolean defaultValue;

    public BoolArgument(String name)
    {
        this(name, true);
    }

    public BoolArgument(String name, boolean defaultValue)
    {
        super(name, CommandArgumentType.BOOL);
        this.defaultValue = defaultValue;
    }

}
