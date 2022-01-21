package vsdum.kex;

import java.util.HashMap;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

public class KernelExtension {
    
    public static void boot(HashMap<?, ?> something)
    {
        Logger.debug("KEX", "Loading java...");
    }

}
