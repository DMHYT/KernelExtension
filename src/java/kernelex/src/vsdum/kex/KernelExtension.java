package vsdum.kex;

import java.lang.reflect.Field;
import java.util.HashMap;

import com.mojang.minecraftpe.MainActivity;
import com.mojang.minecraftpe.TextInputProxyEditTextbox;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.utils.UIUtils;

import android.support.annotation.Nullable;

public class KernelExtension {

    private static native void defineCallbackClasses();
    
    public static void boot(HashMap<?, ?> something)
    {
        Logger.debug("KEX", "Loading java...");
        defineCallbackClasses();
    }

    public static final byte[] getVersion()
    {
        return new byte[]{ 2, 2, 3 };
    }

    public static final short getVersionCode()
    {
        return 223;
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
