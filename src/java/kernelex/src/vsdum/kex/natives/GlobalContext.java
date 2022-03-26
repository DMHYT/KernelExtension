package vsdum.kex.natives;

import android.support.annotation.Nullable;

public class GlobalContext {
    
    private static native long nativeGetLocalPlayer();

    @Nullable public static final LocalPlayer getLocalPlayer()
    {
        long playerPtr = nativeGetLocalPlayer();
        if(playerPtr == 0L) return null;
        return new LocalPlayer(playerPtr, true);
    }

}
