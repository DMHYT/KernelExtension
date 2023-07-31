package vsdum.kex.japi.config;

import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Objects;

import com.electronwill.nightconfig.core.CommentedConfig;
import com.electronwill.nightconfig.core.Config;
import com.electronwill.nightconfig.core.UnmodifiableConfig;
import com.electronwill.nightconfig.core.ConfigSpec.CorrectionAction;
import com.electronwill.nightconfig.core.ConfigSpec.CorrectionListener;
import com.electronwill.nightconfig.core.file.FileConfig;
import com.electronwill.nightconfig.core.utils.UnmodifiableConfigWrapper;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

import android.support.annotation.Nullable;
import vsdum.kex.japi.config.builder.ConfigBuilder;
import vsdum.kex.japi.config.builder.ValueSpec;
import vsdum.kex.japi.config.value.ConfigValue;

public class ConfigSpec extends UnmodifiableConfigWrapper<UnmodifiableConfig> implements IConfigSpec<ConfigSpec> {

    private Map<List<String>, String> levelComments;
    private Map<List<String>, String> levelTranslationKeys;
    private UnmodifiableConfig values;
    private boolean isCorrecting = false;
    public Config childConfig;

    public ConfigSpec(UnmodifiableConfig storage, UnmodifiableConfig values, Map<List<String>, String> levelComments, Map<List<String>, String> levelTranslationKeys)
    {
        super(storage);
        this.values = values;
        this.levelComments = levelComments;
        this.levelTranslationKeys = levelTranslationKeys;
    }

    public static ConfigBuilder builder()
    {
        return new ConfigBuilder();
    }

    public String getLevelComment(List<String> path)
    {
        return this.levelComments.get(path);
    }

    public String getLevelTranslationKey(List<String> path)
    {
        return this.levelTranslationKeys.get(path);
    }

    public void setConfig(CommentedConfig config)
    {
        this.childConfig = config;
        if(config != null && !this.isCorrect(config))
        {
            String configName = config instanceof FileConfig
                ? ((FileConfig) config).getFile().getAbsolutePath().replace(ConfigTracker.CONFIG_DIR, "")
                : config.toString();
            Logger.warning(String.format("[KEX-ConfigSpec] Configuration file %s is not correct. Correcting...", configName));
            this.correct(config,
                (action, path, incorrectValue, correctedValue) ->
                    Logger.warning(String.format("[KEX-ConfigSpec] Incorrect key %s was corrected from %s to its default, %s. %s", String.join(".", path), incorrectValue, correctedValue, incorrectValue == correctedValue ? "This seems to be an error." : "")),
                (action, path, incorrectValue, correctedValue) -> 
                    Logger.warning(String.format("[KEX-ConfigSpec] The comment on key %s does not match the spec. This may create a backup.", String.join(".", path))));
            if(config instanceof FileConfig) ((FileConfig) config).save();
        }
        this.afterReload();
    }

    @Override public void acceptConfig(final CommentedConfig data)
    {
        this.setConfig(data);
    }

    @Override public boolean isCorrecting()
    {
        return this.isCorrecting;
    }

    public boolean isLoaded()
    {
        return this.childConfig != null;
    }

    public UnmodifiableConfig getSpec()
    {
        return this.config;
    }

    public UnmodifiableConfig getValues()
    {
        return this.values;
    }

    @Override public void afterReload()
    {
        this.resetCaches(this.getValues().valueMap().values());
    }

    private void resetCaches(final Iterable<Object> configValues)
    {
        configValues.forEach(value -> {
            if (value instanceof ConfigValue) {
                final ConfigValue<?> configValue = (ConfigValue<?>) value;
                configValue.clearCache();
            } else if (value instanceof Config) {
                final Config innerConfig = (Config) value;
                this.resetCaches(innerConfig.valueMap().values());
            }
        });
    }

    public void save()
    {
        Objects.requireNonNull(this.childConfig, "Cannot save config value without assigned Config object present");
        if(this.childConfig instanceof FileConfig) ((FileConfig) this.childConfig).save();
    }

    @Override public synchronized boolean isCorrect(CommentedConfig config)
    {
        LinkedList<String> parentPath = new LinkedList<>();
        return this.correct(this.config, config, parentPath, Collections.unmodifiableList(parentPath), (a, b, c, d) -> {}, null, true) == 0;
    }

    @Override public int correct(CommentedConfig config)
    {
        return this.correct(config, (action, path, incorrectValue, correctedValue) -> {}, null);
    }

    public synchronized int correct(CommentedConfig config, CorrectionListener listener)
    {
        return this.correct(config, listener, null);
    }

    public synchronized int correct(CommentedConfig config, CorrectionListener listener, CorrectionListener commentListener)
    {
        LinkedList<String> parentPath = new LinkedList<>();
        int ret = -1;
        try {
            this.isCorrecting = true;
            ret = this.correct(this.config, config, parentPath, Collections.unmodifiableList(parentPath), listener, commentListener, false);
        } finally { this.isCorrecting = false; }
        return ret;
    }

    private int correct(UnmodifiableConfig spec, CommentedConfig config, LinkedList<String> parentPath, List<String> parentPathUnmodifiable, CorrectionListener listener, CorrectionListener commentListener, boolean dryRun)
    {
        int count = 0;
        Map<String, Object> specMap = spec.valueMap();
        Map<String, Object> configMap = config.valueMap();
        for(Map.Entry<String, Object> specEntry : specMap.entrySet())
        {
            final String key = specEntry.getKey();
            final Object specValue = specEntry.getValue();
            final Object configValue = configMap.get(key);
            final CorrectionAction action = configValue == null ? CorrectionAction.ADD : CorrectionAction.REPLACE;
            parentPath.addLast(key);
            if(specValue instanceof Config)
            {
                if(configValue instanceof CommentedConfig)
                {
                    count += this.correct((Config) specValue, (CommentedConfig) configValue, parentPath, parentPathUnmodifiable, listener, commentListener, dryRun);
                    if(count > 0 && dryRun) return count;
                } else if(dryRun) return 1; else {
                    CommentedConfig newValue = config.createSubConfig();
                    configMap.put(key, newValue);
                    listener.onCorrect(action, parentPathUnmodifiable, configValue, newValue);
                    count++;
                    count += this.correct((Config) specValue, newValue, parentPath, parentPathUnmodifiable, listener, commentListener, dryRun);
                }
                String newComment = levelComments.get(parentPath);
                String oldComment = config.getComment(key);
                if(!stringsMatchIgnoringNewlines(oldComment, newComment))
                {
                    if(commentListener != null) commentListener.onCorrect(action, parentPathUnmodifiable, oldComment, newComment);
                    if(dryRun) return 1;
                    config.setComment(key, newComment);
                }
            } else {
                ValueSpec valueSpec = (ValueSpec) specValue;
                if(!valueSpec.test(configValue))
                {
                    if(dryRun) return 1;
                    Object newValue = valueSpec.correct(configValue);
                    configMap.put(key, newValue);
                    listener.onCorrect(action, parentPathUnmodifiable, configValue, newValue);
                    count++;
                }
                String oldComment = config.getComment(key);
                if(!stringsMatchIgnoringNewlines(oldComment, valueSpec.getComment()))
                {
                    if(commentListener != null) commentListener.onCorrect(action, parentPathUnmodifiable, oldComment, valueSpec.getComment());
                    if(dryRun) return 1;
                    config.setComment(key, valueSpec.getComment());
                }
            }
            parentPath.removeLast();
        }
        for(Iterator<Map.Entry<String, Object>> iter = configMap.entrySet().iterator(); iter.hasNext();)
        {
            Map.Entry<String, Object> entry = iter.next();
            if(!specMap.containsKey(entry.getKey()))
            {
                if(dryRun) return 1;
                iter.remove();
                parentPath.addLast(entry.getKey());
                listener.onCorrect(CorrectionAction.REMOVE, parentPathUnmodifiable, entry.getValue(), null);
                parentPath.removeLast();
                count++;
            }
        }
        return count;
    }

    private static boolean stringsMatchIgnoringNewlines(@Nullable Object o1, @Nullable Object o2)
    {
        if(o1 instanceof String && o2 instanceof String)
        {
            String s1 = (String) o1;
            String s2 = (String) o2;
            if(s1.length() > 0 && s2.length() > 0)
                return s1.replaceAll("\r\n", "\n").equals(s2.replaceAll("\r\n", "\n"));
        }
        return Objects.equals(o1, o2);
    }

}
