package vsdum.kex.util;

import java.util.HashMap;
import java.util.Map;

import com.zhekasmirnov.innercore.utils.FileTools;

import android.support.annotation.Nullable;

public class LangInjector {

    private static final Map<String, Map<String, Map<String, String>>> injectionData = new HashMap<>();
    private static final Map<String, String> fullLanguageNames = new MapBuilder<String, String>()
        .add("bg", "bg_BG")
        .add("cs", "cs_CZ")
        .add("da", "da_DK")
        .add("de", "de_DE")
        .add("el", "el_GR")
        .add("en", "en_US")
        .add("es", "es_ES")
        .add("fi", "fi_FI")
        .add("fr", "fr_FR")
        .add("hu", "hu_HU")
        .add("id", "id_ID")
        .add("it", "it_IT")
        .add("ja", "ja_JP")
        .add("ko", "ko_KR")
        .add("nb", "nb_NO")
        .add("nl", "nl_NL")
        .add("pl", "pl_PL")
        .add("pt", "pt_PT")
        .add("ru", "ru_RU")
        .add("sk", "sk_SK")
        .add("sv", "sv_SE")
        .add("tr", "tr_TR")
        .add("uk", "uk_UA")
        .add("zh", "zh_CN").build();

    @Nullable public static String validateLanguageCode(String code)
    {
        if(fullLanguageNames.values().contains(code)) return code;
        return fullLanguageNames.get(code);
    }

    public static Map<String, Map<String, String>> addSection(String sectionName)
    {
        injectionData.putIfAbsent(sectionName, new HashMap<>());
        return injectionData.get(sectionName);
    }

    public static void run(String dir)
    {
        FileTools.mkdirs(dir);
        Map<String, StringBuilder> builders = new HashMap<>();
        fullLanguageNames.values().forEach(languageName -> builders.put(languageName, new StringBuilder()));
        injectionData.forEach((sectionName, languages) -> {
            languages.forEach((languageName, translations) -> {
                if(builders.containsKey(languageName))
                {
                    writeSection(builders.get(languageName), sectionName, translations);
                }
            });
        });
        builders.forEach((languageName, builder) -> {
            if(builder.length() > 0) try {
                FileTools.writeFileText(dir + languageName + ".lang", builder.toString());
            } catch(Throwable ex) { ex.printStackTrace(); }
        });
    }

    private static void writeSection(StringBuilder content, String sectionName, Map<String, String> translations)
    {
        content.append("## ").append(sectionName).append("\n");
        translations.forEach((key, translated) -> content.append(key).append("=").append(translated).append("\n"));
        content.append("\n");
    }
    
}
