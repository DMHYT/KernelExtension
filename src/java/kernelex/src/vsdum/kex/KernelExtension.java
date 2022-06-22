package vsdum.kex;

import java.lang.reflect.Field;
import java.util.HashMap;

import com.mojang.minecraftpe.MainActivity;
import com.mojang.minecraftpe.TextInputProxyEditTextbox;
import com.zhekasmirnov.apparatus.adapter.innercore.game.common.Vector3;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Entity;
import com.zhekasmirnov.innercore.utils.UIUtils;

import android.support.annotation.Nullable;
import vsdum.kex.modules.CommandsModule;
import vsdum.kex.modules.commands.CommandContext;
import vsdum.kex.modules.commands.CommandExecuteCallback;

public class KernelExtension {

    private static native void defineCallbackClasses();
    
    public static void boot(HashMap<?, ?> something)
    {
        Logger.debug("KEX", "Loading java...");
        defineCallbackClasses();
        CommandsModule.newEnum("Horizoners")
            .add("zheka", 0)
            .add("onton", 1)
            .add("vasya", 2)
            .add("ilya", 3)
            .add("belyash", 4)
            .add("zholobak", 5)
            .register();
        CommandsModule.registerCommand(CommandsModule.newCommand("kexjavatest", 2)
            .then(CommandsModule.relativeFloatArg("relf")
                .then(CommandsModule.positionArg("pos")
                    .then(CommandsModule.floatPositionArg("fpos")
                        .executes(new CommandExecuteCallback() {
                            public void execute(CommandContext ctx)
                            {
                                float relf = ctx.getRelativeFloat("relf", Entity.getPosition(ctx.getSourcePlayer().getUniqueID())[0]);
                                Vector3 pos = ctx.getPosition("pos");
                                Vector3 fpos = ctx.getFloatPosition("fpos");
                                ctx.success(String.format(
                                    "relf=%f, pos=[%f, %f, %f], fpos=[%f, %f, %f]", new Object[]{
                                        Float.valueOf(relf),
                                        Float.valueOf(pos.x), Float.valueOf(pos.y), Float.valueOf(pos.z),
                                        Float.valueOf(fpos.x), Float.valueOf(fpos.y), Float.valueOf(fpos.z)
                                    }
                                ));
                            }
                        })
                    )
                )
            )
            .then(CommandsModule.stringArg("str")
                .then(CommandsModule.messageArg("msg")
                    .then(CommandsModule.jsonArg("json")
                        .executes(new CommandExecuteCallback() {
                            public void execute(CommandContext ctx)
                            {
                                ctx.success(String.format(
                                    "str=%s, msg=[%s], json=%s", new Object[]{
                                        ctx.getString("str"),
                                        ctx.getMessage("msg"),
                                        ctx.getJson("json").toString()
                                    }
                                ));
                            }
                        })
                    )
                )
            )
            .then(CommandsModule.entityArg("ent")
                .then(CommandsModule.playerArg("pl")
                    .executes(new CommandExecuteCallback() {
                        public void execute(CommandContext ctx)
                        {
                            ctx.success(String.format(
                                "entitiesCount=%d, playersCount=%d", new Object[]{
                                    ctx.getEntities("ent").size(),
                                    ctx.getPlayers("pl").size()
                                }
                            ));
                        }
                    })
                )
            )
        );
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
