package vsdum.kex.util;

import java.lang.reflect.Field;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.constants.Enchantment;
import com.zhekasmirnov.innercore.api.mod.API;
import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;

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

    public static final ScriptableObject createTimeDataScriptable(float baseDestroyTime, float divider, float modifier)
    {
        ScriptableObject result = ScriptableObjectHelper.createEmpty();
        result.put("base", result, baseDestroyTime);
        result.put("devider", result, divider);
        result.put("modifier", result, modifier);
        return result;
    }

    @Nullable public static final ScriptableObject createEnchantDataScriptable(ItemStack stack)
    {
        if(stack.extra != null && stack.extra.isEnchanted())
        {
            ScriptableObject result = ScriptableObjectHelper.createEmpty();
            result.put("experience", result, 0);
            result.put("silk", result, stack.extra.getEnchantLevel(Enchantment.SILK_TOUCH) > 0);
            result.put("fortune", result, stack.extra.getEnchantLevel(Enchantment.FORTUNE));
            result.put("efficiency", result, stack.extra.getEnchantLevel(Enchantment.EFFICIENCY));
            result.put("unbreaking", result, stack.extra.getEnchantLevel(Enchantment.UNBREAKING));
            return result;
        }
        return null;
    }

    public static final short[] enchantDataScriptableToArray(ScriptableObject scr)
    {
        short[] result = new short[]{ 0, 0, 0, 0 };
        Object obj = scr.get("silk", scr);
        if(obj instanceof Boolean) result[0] = (short)( ((Boolean) obj).booleanValue() ? 1 : 0 );
        obj = scr.get("fortune", scr);
        if(obj instanceof Number) result[1] = ((Number) obj).shortValue();
        obj = scr.get("efficiency", scr);
        if(obj instanceof Number) result[2] = ((Number) obj).shortValue();
        obj = scr.get("unbreaking", scr);
        if(obj instanceof Number) result[3] = ((Number) obj).shortValue();
        return result;
    }

}
