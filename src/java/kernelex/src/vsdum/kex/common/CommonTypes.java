package vsdum.kex.common;

import java.lang.reflect.Field;

import com.zhekasmirnov.innercore.api.mod.API;

import org.json.JSONObject;
import org.mozilla.javascript.Context;
import org.mozilla.javascript.NativeJSON;
import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import android.util.Pair;

public final class CommonTypes {

    @Nullable private static final ScriptableObject currentScope = getCurrentScope();

    @Nullable private static final ScriptableObject getCurrentScope()
    {
        ScriptableObject result = null;
        try {
            Field scopeField = API.class.getDeclaredField("currentScopeToInject");
            scopeField.setAccessible(true);
            result = (ScriptableObject) scopeField.get(null);
        } catch(Exception ex) {}
        return result;
    }
    
    public static final Pair<Integer, Integer> deserializeMinMaxScriptable(ScriptableObject scr)
    {
        if(!scr.has("min", scr) || !scr.has("max", scr))
            throw new IllegalArgumentException();
        Object minO = scr.get("min");
        Object maxO = scr.get("max");
        if(!(minO instanceof Number) || !(maxO instanceof Number))
            throw new IllegalArgumentException();
        int min = ((Number) minO).intValue();
        int max = ((Number) maxO).intValue();
        return new Pair<>(min, max);
    }

    @Nullable public static final JSONObject scriptableToJson(ScriptableObject scr)
    {
        try {
            return new JSONObject((String) NativeJSON.stringify(Context.enter(), currentScope, scr, null, null));
        } catch(Exception ex) {}
        return null;
    }

}
