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

    public static final byte[] getVersion()
    {
        return new byte[]{ 1, 3, 0 };
    }

    public static final short getVersionCode()
    {
        return 130;
    }

}
