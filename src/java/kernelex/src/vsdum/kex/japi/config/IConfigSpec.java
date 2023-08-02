package vsdum.kex.japi.config;

import com.electronwill.nightconfig.core.CommentedConfig;
import com.electronwill.nightconfig.core.UnmodifiableConfig;

public interface IConfigSpec<T extends IConfigSpec<T>> extends UnmodifiableConfig {

    public void acceptConfig(CommentedConfig data);

    public boolean isCorrecting();

    public boolean isCorrect(CommentedConfig commentedFileConfig);

    public int correct(CommentedConfig commentedFileConfig);

    public void afterReload();

}
