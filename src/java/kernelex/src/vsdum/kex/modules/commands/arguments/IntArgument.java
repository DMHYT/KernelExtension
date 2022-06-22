package vsdum.kex.modules.commands.arguments;

public class IntArgument extends ArgumentBase {

    public final int defaultValue;

    public IntArgument(String name)
    {
        this(name, 0);
    }
    
    public IntArgument(String name, int defaultValue)
    {
        this(name, defaultValue, null);
    }

    public IntArgument(String name, int defaultValue, String enumName)
    {
        super(name, enumName == null ? CommandArgumentType.INT : CommandArgumentType.enumArgument(enumName));
        this.defaultValue = defaultValue;
    }

}
