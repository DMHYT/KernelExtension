package vsdum.kex.japi.internal;

import java.io.File;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.function.Consumer;

import org.json.JSONArray;
import org.json.JSONObject;

import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.utils.FileTools;

import android.support.annotation.Nullable;
import vsdum.kex.japi.internal.block.BlockVariantParser;
import vsdum.kex.japi.internal.item.ItemModelParser;
import vsdum.kex.natives.I18n;

public class ResourceManager {

    private static final Set<String> kexResourceDirectories = new HashSet<>();

    private static void findResourceDirectoriesInMods()
    {
        long start = System.currentTimeMillis();
        kexResourceDirectories.clear();
        File modsFolder = new File(FileTools.DIR_PACK + "innercore/mods");
        Arrays.asList(modsFolder.listFiles((current, name) -> new File(current, name).isDirectory()))
            .forEach(modFolder -> {
                String kexConfigPath = modFolder.getAbsolutePath() + "/kex-config.json";
                if(new File(kexConfigPath).exists())
                {
                    try {
                        JSONObject config = FileTools.readJSON(kexConfigPath);
                        if(config.has("resources"))
                        {
                            Object val = config.get("resources");
                            if(val instanceof String)
                            {
                                kexResourceDirectories.add(modFolder.getAbsolutePath() + "/" + (String) val);
                            } else if(val instanceof JSONArray) {
                                JSONArray resourcesArr = (JSONArray) val;
                                for(int i = 0; i < resourcesArr.length(); i++)
                                {
                                    Object entry = resourcesArr.get(i);
                                    if(entry instanceof String)
                                    {
                                        kexResourceDirectories.add(modFolder.getAbsolutePath() + "/" + (String) entry);
                                    }
                                }
                            }
                        }
                    } catch(Throwable ex) { ex.printStackTrace(); }
                }
            });
        Logger.debug("KEX-RESMGR", String.format("Verified %d KEX resource directories in %d ms", kexResourceDirectories.size(), System.currentTimeMillis() - start));
    }
    
    public static void onModsLoaded()
    {
        findResourceDirectoriesInMods();
        forEachSubDirectory("lang", I18n::addLangDir);
        BlockVariantParser.onModsLoaded();
        ItemModelParser.onModsLoaded();
    }

    public static void forEachDirectory(Consumer<String> action)
    {
        kexResourceDirectories.forEach(action);
    }

    public static void forEachSubDirectory(String subDirName, Consumer<String> action)
    {
        forEachDirectory(dir -> {
            String subDirectory = dir + subDirName + "/";
            if(new File(subDirectory).exists()) action.accept(subDirectory);
        });
    }

    public static void forEachFileIn(String subDirName, Consumer<File> action)
    {
        forEachSubDirectory(subDirName, subDirPath -> {
            File subDir = new File(subDirPath);
            for(File f : subDir.listFiles(file -> file.isFile()))
            {
                action.accept(f);
            }
        });
    }

    @Nullable public static String findFile(String filePath)
    {
        String result = null;
        for(String dir : kexResourceDirectories)
        {
            String absoluteFilePath = dir + filePath;
            if(new File(absoluteFilePath).exists())
            {
                result = absoluteFilePath;
                break;
            }
        }
        return result;
    }

}
