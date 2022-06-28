package vsdum.kex.util;

import java.util.HashSet;
import java.util.Set;

public class SetBuilder<T> {
    
    private final Set<T> result = new HashSet<>();

    public SetBuilder<T> add(T entry)
    {
        if(!this.result.contains(entry)) this.result.add(entry);
        return this;
    }

    public Set<T> build()
    {
        return this.result;
    }

}
