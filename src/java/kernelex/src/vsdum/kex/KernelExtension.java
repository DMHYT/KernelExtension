package vsdum.kex;

import java.util.HashMap;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

public class KernelExtension {

    private static native void defineCallbackClasses();
    
    public static void boot(HashMap<?, ?> something)
    {
        Logger.debug("KEX", "Loading java...");
        defineCallbackClasses();
    }

    public static final int[] getVersion()
    {
        return new int[]{ 1, 2, 0 };
    }

}
