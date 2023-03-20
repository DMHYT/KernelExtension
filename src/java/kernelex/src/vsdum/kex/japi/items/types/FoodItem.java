package vsdum.kex.japi.items.types;

import org.json.JSONException;
import org.json.JSONObject;

import vsdum.kex.japi.items.Item;
import vsdum.kex.japi.items.ItemProperties;
import vsdum.kex.util.JsonUtils;

public class FoodItem extends Item {
    
    public FoodItem(String nameID)
    {
        super(nameID);
        this.initDefaultFood();
    }

    public FoodItem(String nameID, ItemProperties properties)
    {
        super(nameID, properties);
        this.initDefaultFood();
    }

    private void initDefaultFood()
    {
        if(this.properties.getUseAnimation() == 0) this.properties.setUseAnimation(1);
        if(this.properties.getMaxUseDuration() == 0) this.properties.setMaxUseDuration(32);
        try {
            JSONObject props = this.properties.getJSONProperties();
            if(!props.has("use_animation")) props.put("use_animation", "eat");
            if(!props.has("use_duration")) props.put("use_duration", 32);
            JSONObject food = JsonUtils.getOrCreateObject(props, "food");
            if(!food.has("nutrition")) food.put("nutrition", 1);
            if(!food.has("saturation_modifier")) food.put("saturation_modifier", "normal");
            JSONObject foodComponent = JsonUtils.getOrCreateObject(JsonUtils.getOrCreateObject(props, "components"), "minecraft:food");
            if(!foodComponent.has("nutrition")) foodComponent.put("nutrition", 1);
            if(!foodComponent.has("saturation_modifier")) foodComponent.put("saturation_modifier", "normal");
        } catch(JSONException ex) { ex.printStackTrace(); }
    }

}
