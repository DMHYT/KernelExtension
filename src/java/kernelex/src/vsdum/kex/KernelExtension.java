package vsdum.kex;

import java.util.HashMap;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

import vsdum.kex.modules.ToolsModule;

public class KernelExtension {
    
    public static void boot(HashMap<?, ?> something)
    {
        ToolsModule.defineCallbackClass();
        Logger.debug("KERNELEX", "Loading java...");
    }

}
