package vsdum.kex.modules.commands.arguments;

public class StringArgument extends ArgumentBase {
    
    public final String defaultValue;

    public StringArgument(String name)
    {
        this(name, null);
    }

    public StringArgument(String name, String defaultValue)
    {
        this(name, defaultValue, null);
    }

    public StringArgument(String name, String defaultValue, String enumName)
    {
        super(name, enumName == null ? CommandArgumentType.STRING : CommandArgumentType.stringEnumArgument(enumName));
        this.defaultValue = defaultValue;
    }

}
