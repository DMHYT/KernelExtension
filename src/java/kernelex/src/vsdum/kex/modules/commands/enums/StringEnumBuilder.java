package vsdum.kex.modules.commands.enums;

import java.util.HashSet;
import java.util.Set;

import vsdum.kex.modules.CommandsModule;

public class StringEnumBuilder {
    
    private final String name;
    private final Set<String> values = new HashSet<>();

    public StringEnumBuilder(String name)
    {
        this.name = name;
    }

    public StringEnumBuilder add(String value)
    {
        this.values.add(value);
        return this;
    }

    public void register()
    {
        CommandsModule.addStringEnum(this.name, this.values);
    }

}
