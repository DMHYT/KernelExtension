package vsdum.kex.natives;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.utils.FileTools;

public class I18n {

    private static native void append(long localizationPtr, String content);
    private static native long getCurrent();
    
    public static native String translate(String key);

    private static final Set<String> langDirs = new HashSet<>();

    public static void addLangDir(String dir)
    {
        langDirs.add(dir);
    }

    private static void onChooseLanguage(long localizationPtr, String languageCode)
    {
        Iterator<String> iter = langDirs.iterator();
        while(iter.hasNext())
        {
            String dir = iter.next();
            String langFilePath = dir + languageCode + ".lang";
            if(!FileTools.exists(langFilePath)) langFilePath = dir + "en_US.lang";
            if(FileTools.exists(langFilePath)) try {
                append(localizationPtr, FileTools.readFileText(langFilePath));
            } catch(Throwable ex) { ex.printStackTrace(); }
        }
    }

    public static void onModsLoaded()
    {
        onChooseLanguage(getCurrent(), NativeAPI.getGameLanguage());
    }

}
