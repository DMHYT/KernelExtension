package vsdum.kex.util;

import java.util.Iterator;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.nbt.NativeCompoundTag;
import com.zhekasmirnov.innercore.api.nbt.NativeListTag;
import com.zhekasmirnov.innercore.api.nbt.NbtDataType;

public class NBTJSON {
    
    public static JSONObject NBT2JSON(NativeCompoundTag tag)
    {
        JSONObject result = new JSONObject();
        JSONObject values = new JSONObject();
        JSONObject valueTypes = new JSONObject();
        String[] keys = tag.getAllKeys();
        try {
            for(int i = 0; i < keys.length; i++)
            {
                String key = keys[i];
                int type = tag.getValueType(key);
                valueTypes.put(key, type);
                switch(type)
                {
                    case NbtDataType.TYPE_BYTE: values.put(key, tag.getByte(key) != 0); break;
                    case NbtDataType.TYPE_SHORT: values.put(key, tag.getShort(key)); break;
                    case NbtDataType.TYPE_INT: values.put(key, tag.getInt(key)); break;
                    case NbtDataType.TYPE_INT64: values.put(key, tag.getInt64(key)); break;
                    case NbtDataType.TYPE_FLOAT: values.put(key, tag.getFloat(key)); break;
                    case NbtDataType.TYPE_DOUBLE: values.put(key, tag.getDouble(key)); break;
                    case NbtDataType.TYPE_STRING: values.put(key, tag.getString(key)); break;
                    case NbtDataType.TYPE_LIST: values.put(key, ListTag2JSON(tag.getListTagNoClone(key))); break;
                    case NbtDataType.TYPE_COMPOUND: values.put(key, NBT2JSON(tag.getCompoundTagNoClone(key))); break;
                    default: break;
                }
            }
            return result
                .put("values", values)
                .put("value_types", valueTypes);
        } catch(JSONException ex) { ex.printStackTrace(); }
        return result;
    }
    
    public static NativeCompoundTag JSON2NBT(JSONObject json)
    {
        NativeCompoundTag result = new NativeCompoundTag();
        try {
            JSONObject values = json.getJSONObject("values");
            JSONObject valueTypes = json.getJSONObject("value_types");
            Iterator<String> keys = values.keys();
            while(keys.hasNext())
            {
                String key = keys.next();
                switch(valueTypes.getInt(key))
                {
                    case NbtDataType.TYPE_BYTE: result.putByte(key, values.getBoolean(key) ? 1 : 0); break;
                    case NbtDataType.TYPE_SHORT: result.putShort(key, values.getInt(key)); break;
                    case NbtDataType.TYPE_INT: result.putInt(key, values.getInt(key)); break;
                    case NbtDataType.TYPE_INT64: result.putInt64(key, values.getLong(key)); break;
                    case NbtDataType.TYPE_FLOAT: result.putFloat(key, (float) values.getDouble(key)); break;
                    case NbtDataType.TYPE_DOUBLE: result.putDouble(key, values.getDouble(key)); break;
                    case NbtDataType.TYPE_STRING: result.putString(key, values.getString(key)); break;
                    case NbtDataType.TYPE_LIST: result.putListTag(key, JSON2ListTag(values.getJSONArray(key))); break;
                    case NbtDataType.TYPE_COMPOUND: result.putCompoundTag(key, JSON2NBT(values.getJSONObject(key))); break;
                    default: break;
                }
            }
        } catch(JSONException ex) { ex.printStackTrace(); }
        return result;
    }

    public static JSONArray ListTag2JSON(NativeListTag tag)
    {
        JSONArray result = new JSONArray();
        try {
            for(int i = 0; i < tag.length(); i++)
            {
                int type = tag.getValueType(i);
                switch(type)
                {
                    case NbtDataType.TYPE_BYTE: result.put(new JSONObject().put("type", type).put("value", tag.getByte(i) != 0)); break;
                    case NbtDataType.TYPE_SHORT: result.put(new JSONObject().put("type", type).put("value", tag.getShort(i))); break;
                    case NbtDataType.TYPE_INT: result.put(new JSONObject().put("type", type).put("value", tag.getInt(i))); break;
                    case NbtDataType.TYPE_INT64: result.put(new JSONObject().put("type", type).put("value", tag.getInt64(i))); break;
                    case NbtDataType.TYPE_FLOAT: result.put(new JSONObject().put("type", type).put("value", tag.getFloat(i))); break;
                    case NbtDataType.TYPE_DOUBLE: result.put(new JSONObject().put("type", type).put("value", tag.getDouble(i))); break;
                    case NbtDataType.TYPE_STRING: result.put(new JSONObject().put("type", type).put("value", tag.getString(i))); break;
                    case NbtDataType.TYPE_LIST: result.put(new JSONObject().put("type", type).put("value", ListTag2JSON(tag.getListTagNoClone(i)))); break;
                    case NbtDataType.TYPE_COMPOUND: result.put(new JSONObject().put("type", type).put("value", NBT2JSON(tag.getCompoundTagNoClone(i)))); break;
                    default: break;
                }
            }
        } catch(JSONException ex) { ex.printStackTrace(); }
        return result;
    }

    public static NativeListTag JSON2ListTag(JSONArray json)
    {
        NativeListTag result = new NativeListTag();
        try {
            for(int i = 0; i < json.length(); i++)
            {
                switch(json.getJSONObject(i).getInt("type"))
                {
                    case NbtDataType.TYPE_BYTE: result.putByte(i, json.getJSONObject(i).getBoolean("value") ? 1 : 0); break;
                    case NbtDataType.TYPE_SHORT: result.putShort(i, json.getJSONObject(i).getInt("value")); break;
                    case NbtDataType.TYPE_INT: result.putInt(i, json.getJSONObject(i).getInt("value")); break;
                    case NbtDataType.TYPE_INT64: result.putInt64(i, json.getJSONObject(i).getLong("value")); break;
                    case NbtDataType.TYPE_FLOAT: result.putFloat(i, (float) json.getJSONObject(i).getDouble("value")); break;
                    case NbtDataType.TYPE_DOUBLE: result.putDouble(i, json.getJSONObject(i).getDouble("value")); break;
                    case NbtDataType.TYPE_STRING: result.putString(i, json.getJSONObject(i).getString("value")); break;
                    case NbtDataType.TYPE_LIST: result.putListTag(i, JSON2ListTag(json.getJSONObject(i).getJSONArray("value"))); break;
                    case NbtDataType.TYPE_COMPOUND: result.putCompoundTag(i, JSON2NBT(json.getJSONObject(i).getJSONObject("value"))); break;
                    default: break;
                }
            }
        } catch(JSONException ex) { ex.printStackTrace(); }
        return result;
    }

    private static final NativeCompoundTag testTag()
    {
        NativeCompoundTag result = new NativeCompoundTag();
        result.putByte("testByte", 123);
        result.putShort("testShort", 32761);
        result.putInt("testInt", 2141566842);
        result.putInt64("testLong", 6598324964354820L);
        result.putFloat("testFloat", 0.3125f);
        result.putDouble("testDouble", 0.21356643115f);
        result.putString("testString", "LMAO");
        NativeListTag testList = new NativeListTag();
        testList.putByte(0, 123);
        testList.putShort(1, 32761);
        testList.putInt(2, 2141566842);
        testList.putInt64(3, 6598324964354820L);
        testList.putFloat(4, 0.3125f);
        testList.putDouble(5, 0.21356643115f);
        testList.putString(6, "LMAO");
        testList.putCompoundTag(7, new NativeCompoundTag(result));
        result.putListTag("testList", testList);
        result.putCompoundTag("testCompound", new NativeCompoundTag(result));
        return result;
    }

    /**
     * <strong>Results</strong>:
     * <p>Test compound tag created in <code>~0.15-0.16 ms</code></p>
     * <p>Converted to JSON in <code>~0.57-0.61 ms</code></p>
     * <p>Converted back to compound tag in <code>~0.41-0.42 ms</code></p>
     * <p>Again converted to JSON in <code>~0.58-0.69 ms</code></p>
     */
    public static void test()
    {
        // try {
            Logger.debug("KEX", "====================");
            Logger.debug("KEX", "Starting NBT2JSON converter test...");
            long start = System.nanoTime();
            NativeCompoundTag tag = testTag();
            long end = System.nanoTime();
            Logger.debug("KEX", "Test compound tag created in " + (end - start) + " ns");
            start = System.nanoTime();
            JSONObject json = NBT2JSON(tag);
            end = System.nanoTime();
            Logger.debug("KEX", "Converted to JSON in " + (end - start) + " ns");
            // Logger.debug("KEX", "JSON: " + json.toString(4));
            start = System.nanoTime();
            tag = JSON2NBT(json);
            end = System.nanoTime();
            Logger.debug("KEX", "Converted back to compound tag in " + (end - start) + " ns");
            start = System.nanoTime();
            json = NBT2JSON(tag);
            end = System.nanoTime();
            Logger.debug("KEX", "Again converted to JSON in " + (end - start) + " ns");
            // Logger.debug("KEX", "JSON: " + json.toString(4));
            Logger.debug("KEX", "====================");
        // } catch(JSONException ex) { ex.printStackTrace(); }
    }

}