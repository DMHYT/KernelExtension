package vsdum.kex.util;

import java.util.HashMap;
import java.util.Map;

public class MapBuilder<K, V> {
    
    private final Map<K, V> result = new HashMap<>();

    public MapBuilder<K, V> add(K k, V v)
    {
        this.result.putIfAbsent(k, v);
        return this;
    }

    public Map<K, V> build()
    {
        return this.result;
    }

}
