package vsdum.kex.japi.config;

import java.io.File;
import java.util.Collections;
import java.util.EnumMap;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

import com.electronwill.nightconfig.core.CommentedConfig;
import com.electronwill.nightconfig.core.InMemoryCommentedFormat;
import com.electronwill.nightconfig.core.file.CommentedFileConfig;
import com.zhekasmirnov.apparatus.util.Java8BackComp;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.utils.FileTools;

public class ConfigTracker {

    private static final String getConfigDir()
    {
        String preferencesPath = FileTools.DIR_PACK + "innercore/preferences.json";
        if(new File(preferencesPath).exists())
        {
            try {
                String innerCoreDir = Optional.ofNullable(
                    FileTools.readJSON(preferencesPath)
                        .optString("pack_selected")
                ).orElse(FileTools.DIR_PACK + "innercore");
                return innerCoreDir + "/cfg/";
            } catch(Throwable ex) {}
        }
        return FileTools.DIR_PACK + "innercore/cfg/";
    }

    public static final String CONFIG_DIR = getConfigDir();

    public static final ConfigTracker INSTANCE = new ConfigTracker();

    private final ConcurrentHashMap<String, ModConfig> fileMap;
    private final EnumMap<ModConfig.Type, Set<ModConfig>> configSets;
    private final ConcurrentHashMap<String, Map<ModConfig.Type, ModConfig>> configsByMod;

    private ConfigTracker()
    {
        this.fileMap = new ConcurrentHashMap<>();
        this.configSets = new EnumMap<>(ModConfig.Type.class);
        this.configsByMod = new ConcurrentHashMap<>();
        this.configSets.put(ModConfig.Type.CLIENT, Collections.synchronizedSet(new LinkedHashSet<>()));
        this.configSets.put(ModConfig.Type.COMMON, Collections.synchronizedSet(new LinkedHashSet<>()));
        this.configSets.put(ModConfig.Type.SERVER, Collections.synchronizedSet(new LinkedHashSet<>()));
    }

    public void trackConfig(final ModConfig config)
    {
        if(this.fileMap.containsKey(config.getFileName()))
        {
            Logger.error("KEX-ConfigSpec", String.format("Detected config file conflict %s between %s and %s", config.getFileName(), this.fileMap.get(config.getFileName()).getModId(), config.getModId()));
            throw new RuntimeException("Config conflict detected");
        }
        this.fileMap.put(config.getFileName(), config);
        this.configSets.get(config.getType()).add(config);
        Java8BackComp.computeIfAbsent(this.configsByMod, config.getModId(), k -> new EnumMap<>(ModConfig.Type.class)).put(config.getType(), config);
        Logger.debug("KEX-ConfigSpec", String.format("Config file %s for %s tracking", config.getFileName(), config.getModId()));
    }

    public void loadConfigs(ModConfig.Type type, File configBasePath)
    {
        Logger.debug("KEX-ConfigSpec", "Loading configs type " + type.extension());
        this.configSets.get(type).forEach(config -> openConfig(config, configBasePath));
    }

    public void unloadConfigs(ModConfig.Type type, File configBasePath)
    {
        Logger.debug("KEX-ConfigSpec", "Unloading configs type " + type.extension());
        this.configSets.get(type).forEach(config -> closeConfig(config, configBasePath));
    }

    private static void openConfig(final ModConfig config, final File configBasePath)
    {
        Logger.debug("KEX-ConfigSpec", String.format("Loading config file type %s at %s for %s", config.getType().extension(), config.getFileName(), config.getModId()));
        final CommentedFileConfig configData = ConfigFileTypeHandler.reader(configBasePath).apply(config);
        config.setConfigData(configData);
        config.fireEventLoad();
        config.save();
    }

    private static void closeConfig(final ModConfig config, final File configBasePath)
    {
        if(config.getConfigData() != null)
        {
            Logger.message("KEX-ConfigSpec", String.format("Closing config file type %s at %s for %s", config.getType().extension(), config.getFileName(), config.getModId()));
            ConfigFileTypeHandler.unload(configBasePath, config);
            config.fireEventUnload();
            config.save();
            config.setConfigData(null);
        }
    }

    public void loadDefaultServerConfigs()
    {
        this.configSets.get(ModConfig.Type.SERVER).forEach(modConfig -> {
            final CommentedConfig commentedConfig = (CommentedConfig) InMemoryCommentedFormat.defaultInstance().createConfig();
            modConfig.getSpec().correct(commentedConfig);
            modConfig.setConfigData(commentedConfig);
            modConfig.fireEventLoad();
        });
    }

    public String getConfigFileName(String modId, ModConfig.Type type)
    {
        return Optional.ofNullable(this.configsByMod.getOrDefault(modId, Collections.emptyMap()).getOrDefault(type, null))
            .map(ModConfig::getFile)
            .map(Object::toString)
            .orElse(null);
    }

    public Map<ModConfig.Type, Set<ModConfig>> configSets()
    {
        return this.configSets;
    }

    public ConcurrentHashMap<String, ModConfig> fileMap()
    {
        return this.fileMap;
    }

}
