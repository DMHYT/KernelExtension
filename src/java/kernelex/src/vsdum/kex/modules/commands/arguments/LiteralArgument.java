package vsdum.kex.modules.commands.arguments;

public class LiteralArgument extends ArgumentBase {
    
    public LiteralArgument(String literal)
    {
        super(literal, CommandArgumentType.literalArgument(literal));
    }

}
