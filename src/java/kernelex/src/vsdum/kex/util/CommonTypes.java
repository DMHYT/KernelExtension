package vsdum.kex.util;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.commontypes.FullBlock;
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
import vsdum.kex.modules.states.BlockState;

public final class CommonTypes {
    
    public static final Pair<Integer, Integer> deserializeMinMaxScriptable(ScriptableObject scr)
    {
        if(!ScriptableObject.hasProperty(scr, "min") || !ScriptableObject.hasProperty(scr, "max"))
            throw new IllegalArgumentException();
        int min = ScriptableObjectHelper.getIntProperty(scr, "min", -1);
        int max = ScriptableObjectHelper.getIntProperty(scr, "max", -1);
        if(min == -1 || max == -1) throw new IllegalArgumentException();
        return new Pair<>(min, max);
    }

    public static final int[] deserializeIntVec3(ScriptableObject scr)
    {
        int[] result = new int[]{ 0, 0, 0 };
        if(ScriptableObject.hasProperty(scr, "x")) result[0] = ScriptableObjectHelper.getIntProperty(scr, "x", 0);
        if(ScriptableObject.hasProperty(scr, "y")) result[1] = ScriptableObjectHelper.getIntProperty(scr, "y", 0);
        if(ScriptableObject.hasProperty(scr, "z")) result[2] = ScriptableObjectHelper.getIntProperty(scr, "z", 0);
        return result;
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
        return new short[] {
            ScriptableObjectHelper.getBooleanProperty(scr, "silk", false) ? (short) 1 : (short) 0,
            (short) ScriptableObjectHelper.getIntProperty(scr, "fortune", 0),
            (short) ScriptableObjectHelper.getIntProperty(scr, "efficiency", 0),
            (short) ScriptableObjectHelper.getIntProperty(scr, "unbreaking", 0)
        };
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

    @Nullable public static final Pair<Integer, Integer> deserializeFullBlockOrBlockState(Object block)
    {
        if(block instanceof FullBlock)
        {
            FullBlock full = (FullBlock) block;
            return new Pair<>(full.id, full.data);
        }
        if(block instanceof com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState)
        {
            com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState state = (com.zhekasmirnov.apparatus.adapter.innercore.game.block.BlockState) block;
            return new Pair<>(state.id, state.data);
        }
        if(block instanceof BlockState)
        {
            BlockState state = (BlockState) block;
            return new Pair<>(state.id, state.data);
        }
        if(block instanceof ScriptableObject)
        {
            ScriptableObject scr = (ScriptableObject) block;
            if(ScriptableObject.hasProperty(scr, "id"))
            {
                int id = ScriptableObjectHelper.getIntProperty(scr, "id", -1000);
                int data = ScriptableObjectHelper.getIntProperty(scr, "data", 0);
                if(id == -1000) throw new IllegalArgumentException();
                return new Pair<>(id, data);
            }
        }
        return null;
    }

    public static String getShortLanguageName(String languageName)
    {
        int underscore = languageName.indexOf('_');
        return underscore == -1 ? languageName : languageName.substring(0, underscore);
    }

    public static String formatLikeInVanilla(String str, String[] formatData)
    {
        for(int i = 0; i < formatData.length; ++i)
        {
            str = str.replace(String.format("%%%d$s", i + 1), formatData[i]);
        }
        return str;
    }

}
