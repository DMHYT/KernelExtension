package vsdum.kex.modules.commands.arguments;

public class FloatArgument extends ArgumentBase {
    
    public final float defaultValue;

    public FloatArgument(String name)
    {
        this(name, 0.0f);
    }

    public FloatArgument(String name, float defaultValue)
    {
        this(name, defaultValue, false);
    }

    public FloatArgument(String name, float defaultValue, boolean isRelative)
    {
        super(name, isRelative ? CommandArgumentType.RELATIVE_FLOAT : CommandArgumentType.FLOAT);
        this.defaultValue = defaultValue;
    }

}
