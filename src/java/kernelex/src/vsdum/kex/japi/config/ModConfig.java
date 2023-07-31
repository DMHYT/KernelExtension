package vsdum.kex.japi.config;

import java.io.File;
import java.util.Locale;

import com.electronwill.nightconfig.core.CommentedConfig;
import com.electronwill.nightconfig.core.file.CommentedFileConfig;
import com.electronwill.nightconfig.toml.TomlFormat;
import com.electronwill.nightconfig.toml.TomlParser;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

public class ModConfig {

    private static final TomlParser PARSER = TomlFormat.instance().createParser();

    private final Type type;
    private final IConfigSpec<?> spec;
    private final String modId;
    private final String fileName;
    private CommentedConfig configData;

    public ModConfig(final Type type, final IConfigSpec<?> spec, final String modId)
    {
        this(type, spec, modId, String.format(Locale.ROOT, "%s-%s.toml", modId, type.extension()));
    }

    public ModConfig(final Type type, final IConfigSpec<?> spec, final String modId, final String fileName)
    {
        this.type = type;
        this.spec = spec;
        this.modId = modId;
        String extension = fileName.substring(fileName.lastIndexOf("."), fileName.length());
        if(!extension.equalsIgnoreCase(".toml"))
        {
            Logger.warning(String.format("[KEX-ConfigSpec] Illegal config file name %s with extension %s, only toml is supported, appending '.toml' to the end.", fileName, extension));
            this.fileName = fileName + ".toml";
        } else this.fileName = fileName;
        ConfigTracker.INSTANCE.trackConfig(this);
    }

    public Type getType()
    {
        return this.type;
    }

    public String getFileName()
    {
        return this.fileName;
    }

    @SuppressWarnings("unchecked")
    public <T extends IConfigSpec<T>> IConfigSpec<T> getSpec()
    {
        return (IConfigSpec<T>) this.spec;
    }

    public String getModId()
    {
        return this.modId;
    }

    public CommentedConfig getConfigData()
    {
        return this.configData;
    }

    public void setConfigData(final CommentedConfig configData)
    {
        this.configData = configData;
        this.spec.acceptConfig(this.configData);
    }

    public void fireEventReload()
    {
        ConfigManager.eventsReloading.forEach(handler -> handler.function.accept(this));
    }

    public void fireEventLoad()
    {
        ConfigManager.eventsLoading.forEach(handler -> handler.function.accept(this));
    }

    public void fireEventUnload()
    {
        ConfigManager.eventsUnloading.forEach(handler -> handler.function.accept(this));
    }

    public void save()
    {
        ((CommentedFileConfig) this.configData).save();
    }

    public File getFile()
    {
        return ((CommentedFileConfig) this.configData).getFile();
    }

    public void acceptSyncedConfig(String s)
    {
        this.setConfigData(PARSER.parse(s));
        this.fireEventReload();
    }

    public static enum Type {

        COMMON, CLIENT, SERVER;

        public String extension()
        {
            return this.name().toLowerCase();
        }

    }

}
