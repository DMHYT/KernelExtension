package vsdum.kex.natives;

import android.support.annotation.Nullable;

public class GlobalContext {
    
    private static native long nativeGetLocalPlayer();
    private static native long nativeGetLevel();

    @Nullable public static final LocalPlayer getLocalPlayer()
    {
        long playerPtr = nativeGetLocalPlayer();
        if(playerPtr == 0L) return null;
        return new LocalPlayer(playerPtr, true);
    }

    @Nullable public static final Level getLevel()
    {
        long levelPtr = nativeGetLevel();
        if(levelPtr == 0L) return null;
        return new Level(levelPtr);
    }

}
