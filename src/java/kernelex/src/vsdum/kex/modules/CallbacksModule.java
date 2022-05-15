package vsdum.kex.modules;

import com.zhekasmirnov.apparatus.adapter.innercore.game.item.ItemStack;
import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;
import com.zhekasmirnov.innercore.api.runtime.Callback;

import org.mozilla.javascript.Context;

import vsdum.kex.natives.Level;

public class CallbacksModule {
    
    public static void onPlayerJump(long uid)
    {
        Callback.invokeAPICallback("PlayerJump", new Object[]{ Long.valueOf(uid) });
    }

    public static void onGameModeChanged(int mode)
    {
        Callback.invokeAPICallback("GameModeChanged", new Object[]{ Integer.valueOf(mode) });
    }

    public static void onChangeCarriedItem(long player, long oldStackPtr, long newStackPtr, byte hand)
    {
        ItemStack oldStack = ItemStack.fromPtr(oldStackPtr);
        ItemStack newStack = ItemStack.fromPtr(newStackPtr);
        if(oldStack != null && newStack != null)
        {
            Callback.invokeAPICallback("ChangeCarriedItem", new Object[]{ Long.valueOf(player), oldStack, newStack, Byte.valueOf(hand) });
        }
    }

    public static void onItemTooltip(ItemStack stack, Level level, StringBuilder textBuilder)
    {
        Callback.invokeAPICallback("ItemTooltip", new Object[]{ stack, Context.javaToJS(textBuilder, ScriptableObjectHelper.getDefaultScope()), level });
    }

}
