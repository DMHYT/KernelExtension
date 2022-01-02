package vsdum.kex.common;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public final class JsonUtils {
    
    public static JSONArray getOrCreateArray(JSONObject obj, String key)
    throws JSONException
    {
        JSONArray array = obj.optJSONArray(key);
        if(array == null)
        {
            array = new JSONArray();
            obj.put(key, array);
        }
        return array;
    }

    public static JSONObject getOrCreateObject(JSONObject obj, String key)
    throws JSONException
    {
        JSONObject object = obj.optJSONObject(key);
        if(object == null)
        {
            object = new JSONObject();
            obj.put(key, object);
        }
        return object;
    }

}
