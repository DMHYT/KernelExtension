package vsdum.kex.modules.tools;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.NativeItemInstanceExtra;
import com.zhekasmirnov.innercore.api.commontypes.Coords;
import com.zhekasmirnov.innercore.api.commontypes.FullBlock;
import com.zhekasmirnov.innercore.api.commontypes.ItemInstance;
import com.zhekasmirnov.innercore.api.constants.Enchantment;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Entity;

import org.mozilla.javascript.ScriptableObject;

import android.util.Pair;
import vsdum.kex.util.CommonTypes;

public class CustomToolEvents {
    
    public static float calcDestroyTime(int id, int data, int x, int y, int z, byte side, float baseDestroyTime, float divider, float modifier, float defaultTime)
    {
        ItemInstance stack = Entity.getCarriedItem(NativeAPI.getLocalPlayer());
        if(DataSets.toolData.containsKey(id))
        {
            ScriptableObject obj = DataSets.toolData.get(id);
            if(ScriptableObject.hasProperty(obj, "calcDestroyTime"))
            {
                return CommonTypes.callFloatJSFunction(obj, "calcDestroyTime", new Object[]{
                    new Coords(x, y, z, side),
                    new FullBlock(id, data),
                    CommonTypes.createTimeDataScriptable(baseDestroyTime, divider, modifier),
                    Float.valueOf(defaultTime),
                    CommonTypes.createEnchantDataScriptable(new ItemStack(stack))
                }, defaultTime);
            }
        }
        return defaultTime;
    }

    public static boolean onDestroy(Coords coords, ItemInstance item, Object tile, long player)
    {
        Pair<Integer, Integer> block = CommonTypes.deserializeFullBlockOrBlockState(tile);
        if(block == null) return false;
        if(DataSets.toolData.containsKey(item.getId()))
        {
            ScriptableObject obj = DataSets.toolData.get(item.getId());
            if(ScriptableObject.hasProperty(obj, "onDestroy"))
            {
                boolean result = CommonTypes.callBooleanJSFunction(obj, "onDestroy", new Object[]{
                    item, coords, new FullBlock(block.first.intValue(), block.second.intValue()), Long.valueOf(player)
                }, false);
                Entity.setCarriedItem(player, item.getId(), item.getCount(), item.getData(), CommonTypes.getExtraFromInstance(item));
                return result;
            }
        }
        return false;
    }

    public static boolean onAttack(long victim, long attacker, ItemInstance item)
    {
        if(DataSets.toolData.containsKey(item.getId()))
        {
            ScriptableObject obj = DataSets.toolData.get(item.getId());
            if(ScriptableObject.hasProperty(obj, "onAttack"))
            {
                boolean result = CommonTypes.callBooleanJSFunction(obj, "onAttack", new Object[]{
                    item, Long.valueOf(victim), Long.valueOf(attacker)
                }, false);
                Entity.setCarriedItem(attacker, item.getId(), item.getCount(), item.getData(), CommonTypes.getExtraFromInstance(item));
                return result;
            }
        }
        return false;
    }

    public static boolean onBroke()
    {
        ItemInstance stack = Entity.getCarriedItem(NativeAPI.getLocalPlayer());
        if(DataSets.toolData.containsKey(stack.getId()))
        {
            ScriptableObject obj = DataSets.toolData.get(stack.getId());
            if(ScriptableObject.hasProperty(obj, "onBroke"))
            {
                return CommonTypes.callBooleanJSFunction(obj, "onBroke", new Object[]{ stack }, false);
            }
        }
        return false;
    }

    public static void modifyEnchant(Coords coords, ItemInstance item, Object tile, long player)
    {
        Pair<Integer, Integer> block = CommonTypes.deserializeFullBlockOrBlockState(tile);
        if(block != null)
        {
            if(DataSets.toolData.containsKey(item.getId()))
            {
                ScriptableObject obj = DataSets.toolData.get(item.getId());
                if(ScriptableObject.hasProperty(obj, "modifyEnchant"))
                {
                    NativeItemInstanceExtra extra = CommonTypes.getExtraFromInstance(item);
                    if(extra == null) extra = new NativeItemInstanceExtra();
                    extra.removeAllEnchants();
                    ScriptableObject enchantData = CommonTypes.createEnchantDataScriptable(new ItemStack(item));
                    CommonTypes.callVoidJSFunction(obj, "modifyEnchant", new Object[]{ enchantData, item, coords, new FullBlock(block.first.intValue(), block.second.intValue()) });
                    short[] modified = CommonTypes.enchantDataScriptableToArray(enchantData);
                    if(modified[0] > 0) extra.addEnchant(Enchantment.SILK_TOUCH, modified[0]); else extra.removeEnchant(Enchantment.SILK_TOUCH);
                    if(modified[1] > 0) extra.addEnchant(Enchantment.FORTUNE, modified[1]); else extra.removeEnchant(Enchantment.FORTUNE);
                    if(modified[2] > 0) extra.addEnchant(Enchantment.EFFICIENCY, modified[2]); else extra.removeEnchant(Enchantment.EFFICIENCY);
                    if(modified[3] > 0) extra.addEnchant(Enchantment.UNBREAKING, modified[3]); else extra.removeEnchant(Enchantment.UNBREAKING);
                    Entity.setCarriedItem(player, item.getId(), item.getCount(), item.getData(), extra);
                }
            }
        }
    }

    public static void onMineBlock(int x, int y, int z, byte side, int id, int data, long player)
    {
        ItemInstance stack = Entity.getCarriedItem(player);
        if(DataSets.toolData.containsKey(stack.getId()))
        {
            ScriptableObject obj = DataSets.toolData.get(stack.getId());
            if(ScriptableObject.hasProperty(obj, "onMineBlock"))
            {
                CommonTypes.callVoidJSFunction(obj, "onMineBlock", new Object[]{
                    new Coords(x, y, z, side),
                    stack,
                    new FullBlock(id, data)
                });
                Entity.setCarriedItem(player, stack.getId(), stack.getCount(), stack.getData(), CommonTypes.getExtraFromInstance(stack));
            }
        }
    }

    public static int getAttackDamageBonus(int id, int count, int data, long extraPtr, int defaultValue)
    {
        if(DataSets.toolData.containsKey(id))
        {
            ItemInstance stack = new ItemInstance(id, count, data, new NativeItemInstanceExtra(extraPtr));
            ScriptableObject obj = DataSets.toolData.get(id);
            if(ScriptableObject.hasProperty(obj, "getAttackDamageBonus"))
            {
                return CommonTypes.callIntJSFunction(obj, "getAttackDamageBonus", new Object[]{ stack }, defaultValue);
            }
        }
        return defaultValue;
    }

}
