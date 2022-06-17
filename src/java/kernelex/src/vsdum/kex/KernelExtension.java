package vsdum.kex;

import java.lang.reflect.Field;
import java.util.HashMap;
// import java.util.Map;

import com.mojang.minecraftpe.MainActivity;
import com.mojang.minecraftpe.TextInputProxyEditTextbox;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.utils.UIUtils;

import android.support.annotation.Nullable;
// import vsdum.kex.modules.CommandsModule;
// import vsdum.kex.modules.commands.CommandArgumentType;

public class KernelExtension {

    private static native void defineCallbackClasses();
    
    public static void boot(HashMap<?, ?> something)
    {
        Logger.debug("KEX", "Loading java...");
        defineCallbackClasses();
        // Map<String, Integer> testEnum = new HashMap<>();
        // testEnum.put("zheka", 0);
        // testEnum.put("onton", 1);
        // testEnum.put("vasya",2);
        // testEnum.put("ilya", 3);
        // testEnum.put("belyash", 4);
        // testEnum.put("zholobak", 5);
        // CommandsModule.addEnum("Horizoners", testEnum);
        // CommandsModule.registerCommand(CommandsModule.newCommand("kexjavatest", 2)
        //     .then(CommandsModule.literal("l", "testliteral")
        //         .then(CommandsModule.argument("i", CommandArgumentType.INT.type)
        //             .then(CommandsModule.argument("f", CommandArgumentType.FLOAT.type)
        //                 .then(CommandsModule.argument("b", CommandArgumentType.BOOL.type))
        //             )
        //         )
        //     )
        //     .then(CommandsModule.argument("relf", CommandArgumentType.RELATIVE_FLOAT.type)
        //         .then(CommandsModule.argument("pos", CommandArgumentType.POSITION.type)
        //             .then(CommandsModule.argument("s", CommandArgumentType.STRING.type)
        //                 .then(CommandsModule.argument("msg", CommandArgumentType.MESSAGE.type))
        //             )
        //         )
        //     )
        //     .then(CommandsModule.argument("json", CommandArgumentType.JSON.type)
        //         .then(CommandsModule.argument("e", CommandArgumentType.ENTITY.type)
        //             .then(CommandsModule.argument("p", CommandArgumentType.PLAYER.type)
        //                 .then(CommandsModule.argument("item", CommandArgumentType.ITEM.type))
        //             )
        //         )
        //     )
        //     .then(CommandsModule.argument("block", CommandArgumentType.BLOCK.type)
        //         .then(CommandsModule.argument("effect", CommandArgumentType.EFFECT.type)
        //             .then(CommandsModule.enumArgument("enum", "Horizoners"))
        //         )
        //     )
        // );
    }

    public static final byte[] getVersion()
    {
        return new byte[]{ 3, 0, 0 };
    }

    public static final short getVersionCode()
    {
        return 300;
    }

    @Nullable private static Runnable onSignOpenFunc = null;

    public static void onSignOpen()
    {
        if(onSignOpenFunc != null)
        {
            UIUtils.getContext().runOnUiThread(onSignOpenFunc);
            onSignOpenFunc = null;
        }
    }

    public static void setMinecraftTextboxText(String text)
    {
        MainActivity minecraft = (MainActivity) UIUtils.getContext();
        onSignOpenFunc = new Runnable() {
            public void run()
            {
                try {
                    Field textEditField = MainActivity.class.getDeclaredField("textInputWidget");
                    textEditField.setAccessible(true);
                    TextInputProxyEditTextbox textbox = (TextInputProxyEditTextbox) textEditField.get(minecraft);
                    textbox.setText(text);
                    textbox.setSelection(textbox.length());
                } catch(Throwable ex) {
                    ex.printStackTrace();
                }
            }
        };
    }

}
