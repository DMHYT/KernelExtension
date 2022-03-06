package vsdum.kex.util;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.NativeItemInstanceExtra;
import com.zhekasmirnov.innercore.api.commontypes.ItemInstance;
import com.zhekasmirnov.innercore.api.constants.Enchantment;
import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;
import com.zhekasmirnov.innercore.api.runtime.saver.serializer.ScriptableSerializer;

import org.json.JSONObject;
import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.NativeJSON;
import org.mozilla.javascript.ScriptableObject;

import android.support.annotation.Nullable;
import android.util.Pair;

public final class CommonTypes {
    
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
            return new JSONObject((String) NativeJSON.stringify(Context.enter(), scr.getParentScope(), scr, null, null));
        } catch(Exception ex) {}
        return null;
    }

    @Nullable public static final ScriptableObject jsonToScriptable(JSONObject obj)
    {
        return (ScriptableObject) ScriptableSerializer.scriptableFromJson(obj);
    }

    public static final ScriptableObject createTimeDataScriptable(float baseDestroyTime, float divider, float modifier)
    {
        ScriptableObject result = ScriptableObjectHelper.createEmpty();
        result.put("base", result, baseDestroyTime);
        result.put("devider", result, divider);
        result.put("modifier", result, modifier);
        return result;
    }

    private static final ScriptableObject createEmptyEnchantDataScriptable()
    {
        ScriptableObject result = ScriptableObjectHelper.createEmpty();
        result.put("experience", result, 0);
        result.put("silk", result, false);
        result.put("fortune", result, 0);
        result.put("efficiency", result, 0);
        result.put("unbreaking", result, 0);
        return result;
    }

    @Nullable public static final ScriptableObject createEnchantDataScriptable(ItemStack stack)
    {
        ScriptableObject result = createEmptyEnchantDataScriptable();
        if(stack.extra != null && stack.extra.isEnchanted())
        {
            result.put("experience", result, 0);
            result.put("silk", result, stack.extra.getEnchantLevel(Enchantment.SILK_TOUCH) > 0);
            result.put("fortune", result, stack.extra.getEnchantLevel(Enchantment.FORTUNE));
            result.put("efficiency", result, stack.extra.getEnchantLevel(Enchantment.EFFICIENCY));
            result.put("unbreaking", result, stack.extra.getEnchantLevel(Enchantment.UNBREAKING));
        }
        return result;
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

    @Nullable private static Function getFunctionFromScriptable(ScriptableObject scr, String functionName)
    {
        Function result = null;
        if(ScriptableObject.hasProperty(scr, functionName))
        {
            Object val = ScriptableObject.getProperty(scr, functionName);
            if(val instanceof Function)
            {
                result = (Function) val;
            }
        }
        return result;
    }

    public static void callVoidJSFunction(ScriptableObject scr, String functionName, Object[] args)
    {
        Function func = getFunctionFromScriptable(scr, functionName);
        if(func != null)
        {
            func.call(Context.enter(), scr.getParentScope(), scr, args);
        }
    }

    public static float callFloatJSFunction(ScriptableObject scr, String functionName, Object[] args, float defaultValue)
    {
        Function func = getFunctionFromScriptable(scr, functionName);
        if(func != null)
        {
            Object result = func.call(Context.enter(), scr.getParentScope(), scr, args);
            if(result instanceof Number)
            {
                return ((Number) result).floatValue();
            }
        }
        return defaultValue;
    }

    public static boolean callBooleanJSFunction(ScriptableObject scr, String functionName, Object[] args, boolean defaultValue)
    {
        Function func = getFunctionFromScriptable(scr, functionName);
        if(func != null)
        {
            Object result = func.call(Context.enter(), scr.getParentScope(), scr, args);
            if(result instanceof Boolean)
            {
                return ((Boolean) result).booleanValue();
            }
        }
        return defaultValue;
    }

    public static int callIntJSFunction(ScriptableObject scr, String functionName, Object[] args, int defaultValue)
    {
        Function func = getFunctionFromScriptable(scr, functionName);
        if(func != null)
        {
            Object result = func.call(Context.enter(), scr.getParentScope(), scr, args);
            if(result instanceof Number)
            {
                return ((Number) result).intValue();
            }
        }
        return defaultValue;
    }

    @Nullable public static NativeItemInstanceExtra getExtraFromInstance(ItemInstance item)
    {
        return NativeItemInstanceExtra.unwrapObject(ScriptableObjectHelper.getProperty(item, "extra", null));
    }

}
