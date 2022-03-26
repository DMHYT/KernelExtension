package vsdum.kex.modules;

import com.zhekasmirnov.innercore.api.runtime.Callback;

public class CallbacksModule {
    
    public static void onPlayerJump(long uid)
    {
        Callback.invokeAPICallback("PlayerJump", new Object[]{ Long.valueOf(uid) });
    }

    public static void onGameModeChanged(int mode)
    {
        Callback.invokeAPICallback("GameModeChanged", new Object[]{ Integer.valueOf(mode) });
    }

}
