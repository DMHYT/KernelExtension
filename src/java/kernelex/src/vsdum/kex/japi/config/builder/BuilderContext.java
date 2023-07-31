package vsdum.kex.japi.config.builder;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

public class BuilderContext {

    private final List<String> comment = new LinkedList<>();
    private String langKey;
    private Range<?> range;
    private boolean worldRestart = false;
    private Class<?> clazz;

    public void addComment(String value)
    {
        Objects.requireNonNull(value, "Passed in null value for comment");
        this.comment.add(value);
    }

    public void clearComment()
    {
        this.comment.clear();
    }

    public boolean hasComment()
    {
        return this.comment.size() > 0;
    }

    public String buildComment()
    {
        return this.buildComment(Arrays.asList("unknown", "unknown"));
    }

    public String buildComment(final List<String> path)
    {
        boolean allBlank = true;
        for(String comment : this.comment)
            if(comment.trim().isEmpty())
            {
                allBlank = false;
                break;
            }
        if(allBlank)
        {
            Logger.warning(String.format("[KEX-ConfigSpec] Detected a comment that is all whitespace for config option %s. Please report this to the mod author.", String.join(".", path)));
            return "A developer of this mod has defined this config option with a blank comment. Please report this to them.";
        }
        return String.join("\n", this.comment);
    }

    public void setTranslationKey(String value)
    {
        this.langKey = value;
    }

    public String getTranslationKey()
    {
        return this.langKey;
    }

    public <V extends Comparable<? super V>> void setRange(Range<V> value)
    {
        this.range = value;
        this.setClazz(value.getClazz());
    }

    @SuppressWarnings("unchecked")
    public <V extends Comparable<? super V>> Range<V> getRange()
    {
        return (Range<V>) this.range;
    }

    public void worldRestart()
    {
        this.worldRestart = true;
    }

    public boolean needsWorldRestart()
    {
        return this.worldRestart;
    }

    public void setClazz(Class<?> clazz)
    {
        this.clazz = clazz;
    }

    public Class<?> getClazz()
    {
        return this.clazz;
    }

    public void ensureEmpty()
    {
        if(this.hasComment()) throw new IllegalStateException("Non-empty comment when empty expected");
        if(this.langKey != null) throw new IllegalStateException("Non-null translation key when null expected");
        if(this.range != null) throw new IllegalStateException("Non-null range when null expected");
        if(this.worldRestart) throw new IllegalStateException("Dangeling world restart value set to true");
    }

}
