package vsdum.kex.modules.commands.arguments;

public class PositionArgument extends ArgumentBase {
    
    public final float x;
    public final float y;
    public final float z;

    public PositionArgument(String name)
    {
        this(name, 0.0f, 0.0f, 0.0f);
    }

    public PositionArgument(String name, float x, float y, float z)
    {
        this(name, x, y, z, false);
    }

    public PositionArgument(String name, float x, float y, float z, boolean isFloat)
    {
        super(name, isFloat ? CommandArgumentType.FLOAT_POSITION : CommandArgumentType.POSITION);
        this.x = x;
        this.y = y;
        this.z = z;
    }

}
