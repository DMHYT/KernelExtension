package vsdum.kex.japi.config;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.function.Function;
import java.util.stream.Collectors;

import com.electronwill.nightconfig.core.CommentedConfig;
import com.electronwill.nightconfig.core.ConfigFormat;
import com.electronwill.nightconfig.core.file.CommentedFileConfig;
import com.electronwill.nightconfig.core.file.CommentedFileConfigBuilder;
import com.electronwill.nightconfig.core.file.FileWatcher;
import com.electronwill.nightconfig.core.file.FormatDetector;
import com.electronwill.nightconfig.core.file.NoFormatFoundException;
import com.electronwill.nightconfig.core.io.ParsingException;
import com.electronwill.nightconfig.core.io.WritingMode;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.horizon.util.FileUtils;
import com.zhekasmirnov.innercore.api.log.ICLog;
import com.zhekasmirnov.innercore.utils.FileTools;

public class ConfigFileTypeHandler {

    public static Function<ModConfig, CommentedFileConfig> reader(File configBasePath)
    {
        return c -> {
            final File configPath = new File(configBasePath, c.getFileName());
            final CommentedFileConfig configData = commentedFileConfigBuilder(configPath)
                .sync()
                .preserveInsertionOrder()
                .autosave()
                .onFileNotFound((newFile, configFormat) -> setupConfigFile(c, newFile, configFormat))
                .writingMode(WritingMode.REPLACE)
                .build();
            Logger.debug("KEX-ConfigSpec", "Built config for " + configPath.toString());
            try {
                configData.load();
            } catch(ParsingException ex) { throw new ConfigLoadingException(c, ex); }
            Logger.debug("KEX-ConfigSpec", "Loaded config file " + configPath.toString());
            try {
                FileWatcher.defaultInstance().addWatch(configPath, new ConfigWatcher(c, configData, Thread.currentThread().getContextClassLoader()));
                Logger.debug("KEX-ConfigSpec", "Watching config file " + configPath.toString() + " for changes");
            } catch(IOException e) { throw new RuntimeException("Couldn't watch config file", e); }
            return configData;
        };
    }

    public static void unload(File configBasePath, ModConfig config)
    {
        File configPath = new File(configBasePath, config.getFileName());
        try {
            FileWatcher.defaultInstance().removeWatch(configPath);
        } catch(RuntimeException e) { ICLog.e("KEX-ConfigSpec", "Failed to remove config " + configPath.toString() + " from tracker!", e); }
    }

    private static boolean setupConfigFile(final ModConfig modConfig, final File file, final ConfigFormat<?> conf)
    throws IOException
    {
        FileTools.assureDir(file.getParent());
        File f = new File(ConfigTracker.CONFIG_DIR + modConfig.getFileName());
        if(f.exists())
        {
            Logger.info("KEX-ConfigSpec", "Loading default config file from path " + f.getAbsolutePath());
            FileUtils.copy(f, file);
        } else {
            file.createNewFile();
            conf.initEmptyFile(file);
        }
        return true;
    }

    public static void backUpConfig(final CommentedFileConfig commentedFileConfig)
    {
        backUpConfig(commentedFileConfig, 5);
    }

    public static void backUpConfig(final CommentedFileConfig commentedFileConfig, final int maxBackups)
    {
        File bakFileLocation = commentedFileConfig.getFile().getParentFile();
        String configFileName = commentedFileConfig.getFile().getName();
        int dotIndex = configFileName.lastIndexOf(".");
        String bakFileName = configFileName.substring(0, dotIndex);
        String bakFileExtension = configFileName.substring(dotIndex, configFileName.length()) + ".bak";
        File bakFile = new File(bakFileLocation, bakFileName + "-1." + bakFileExtension);
        try {
            for(int i = maxBackups; i > 0; i--)
            {
                File oldBak = new File(bakFileLocation, bakFileName + "-" + i + "." + bakFileExtension);
                if(oldBak.exists())
                {
                    if(i < maxBackups)
                        FileUtils.copy(oldBak, new File(bakFileLocation, bakFileName + "-" + (i + 1) + "." + bakFileExtension));
                    FileTools.delete(oldBak.getAbsolutePath());
                }
            }
            FileUtils.copy(commentedFileConfig.getFile(), bakFile);
        } catch(IOException exception) {
            Logger.warning("[KEX-ConfigSpec] Failed to back up config file " + commentedFileConfig.getFile().toString());
            Logger.warning("[KEX-ConfigSpec] " + String.join("\n", Arrays.stream(exception.getStackTrace())
                .map(StackTraceElement::toString)
                .collect(Collectors.toList())));
        }
    }

    // rewrite of CommentedFileConfig.builder because d8 omits it :(
    @SuppressWarnings("unchecked")
    private static CommentedFileConfigBuilder commentedFileConfigBuilder(File file)
    {
        ConfigFormat<? extends CommentedConfig> format = (ConfigFormat<? extends CommentedConfig>) FormatDetector.detect(file);
        if(format == null)
            throw new NoFormatFoundException("No suitable format for " + file.getName());
        else if(!format.supportsComments())
            throw new NoFormatFoundException("The available format doesn't support comments for " + file.getName());
        else return new CommentedFileConfigBuilder(file, format);
    }

    private static class ConfigWatcher implements Runnable {

        private final ModConfig modConfig;
        private final CommentedFileConfig commentedFileConfig;
        private final ClassLoader realClassLoader;

        ConfigWatcher(final ModConfig modConfig, final CommentedFileConfig commentedFileConfig, final ClassLoader classLoader)
        {
            this.modConfig = modConfig;
            this.commentedFileConfig = commentedFileConfig;
            this.realClassLoader = classLoader;
        }

        @Override public void run()
        {
            Thread.currentThread().setContextClassLoader(this.realClassLoader);
            if(!this.modConfig.getSpec().isCorrecting())
            {
                try {
                    this.commentedFileConfig.load();
                    if(!this.modConfig.getSpec().isCorrect(this.commentedFileConfig))
                    {
                        Logger.warning(String.format("[KEX-ConfigSpec] Configuration file %s is not correct. Correcting", this.commentedFileConfig.getFile().getAbsolutePath()));
                        ConfigFileTypeHandler.backUpConfig(this.commentedFileConfig);
                        this.modConfig.getSpec().correct(this.commentedFileConfig);
                        this.commentedFileConfig.save();
                    }
                } catch(ParsingException ex) { throw new ConfigLoadingException(this.modConfig, ex); }
                Logger.debug("KEX-ConfigSpec", String.format("Config file %s changed, sending notifies", this.modConfig.getFileName()));
                this.modConfig.getSpec().afterReload();
                this.modConfig.fireEventReload();
            }
        }

    }

    private static class ConfigLoadingException extends RuntimeException {

        public ConfigLoadingException(ModConfig config, Exception cause)
        {
            super(String.format("Failed loading config file %s of type %s for modid %s", config.getFileName(), config.getType().extension(), config.getModId()), cause);
        }

    }

}
