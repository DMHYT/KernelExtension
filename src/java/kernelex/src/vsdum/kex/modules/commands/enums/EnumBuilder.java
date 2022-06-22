package vsdum.kex.modules.commands.enums;

import java.util.HashMap;
import java.util.Map;

import vsdum.kex.modules.CommandsModule;

public class EnumBuilder {

    private final String name;
    private final Map<String, Integer> values = new HashMap<>();

    public EnumBuilder(String name)
    {
        this.name = name;
    }

    public EnumBuilder add(String key, int value)
    {
        this.values.putIfAbsent(key, value);
        return this;
    }

    public void register()
    {
        CommandsModule.addEnum(this.name, this.values);
    }
    
}
