package vsdum.kex.util;

import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.Logger;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;

public class ItemFactoryHelper {

    protected static native long nativeKillItem(int id);
    protected static native void nativePutPropertiesToNewFactory(long ptr, int id);
    protected static native String nativeFactoryGetNameId(long ptr);
    protected static native String nativeFactoryGetNameToDisplay(long ptr);
    protected static native String nativeFactoryGetIconName(long ptr);
    protected static native int nativeFactoryGetIconIndex(long ptr);
    protected static native int nativeFactoryGetStack(long ptr);

    @Nullable public static ItemFactoryInterface killItem(int id)
    {
        Logger.debug("KEX", String.format("Killing item with id %d", new Object[]{Integer.valueOf(id)}));
        Logger.Flush();
        long ptr = nativeKillItem(id);
        Logger.debug("KEX", "Killed!");
        Logger.Flush();
        return ptr != 0L ? new ItemFactoryInterface(ptr) : null;
    }

    public static class ItemFactoryInterface implements INativeInterface {
        
        protected final long pointer;

        public final String nameId;
        public final String nameToDisplay;
        public final String iconName;
        public final int iconIndex;
        public final int stack;

        public final long getPointer()
        {
            return this.pointer;
        }

        public ItemFactoryInterface(long ptr)
        {
            this.pointer = ptr;
            this.nameId = nativeFactoryGetNameId(this.pointer);
            this.nameToDisplay = nativeFactoryGetNameToDisplay(this.pointer);
            this.iconName = nativeFactoryGetIconName(this.pointer);
            this.iconIndex = nativeFactoryGetIconIndex(this.pointer);
            this.stack = nativeFactoryGetStack(this.pointer);
        }

        public void applyOldFactoryProperties(int id)
        {
            Logger.Log("KEX", String.format("Applying old factory properties to the item with id %d", new Object[]{ Integer.valueOf(id) }));
            Logger.Flush();
            nativePutPropertiesToNewFactory(this.pointer, id);
            Logger.Log("KEX", "Applied!");
            Logger.Flush();
        }

    }

}
