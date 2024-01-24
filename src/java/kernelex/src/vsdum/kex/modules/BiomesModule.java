package vsdum.kex.modules;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Consumer;

import org.json.JSONObject;

import com.zhekasmirnov.innercore.utils.FileTools;

import android.support.annotation.Nullable;
import vsdum.kex.natives.I18n;
import vsdum.kex.util.LangInjector;

public class BiomesModule {

    private static final Map<String, String> customBiomeTranslationKeys = new HashMap<>();
    private static final Map<Integer, BiomeInterface> biomesById = new HashMap<>();
    private static final Map<String, BiomeInterface> biomesByName = new HashMap<>();
    private static boolean biomesInitialized = false;

    public static void setBiomeTranslationKey(String biomeNameID, String key)
    {
        customBiomeTranslationKeys.put(biomeNameID, key);
    }

    public static void appendBiomeNameTranslations(String biomeNamesPath)
    {
        Map<String, Map<String, String>> translations = LangInjector.addSection("BIOME NAMES");
        try {
            JSONObject biomeNamesJson = FileTools.readJSON(biomeNamesPath);
            biomeNamesJson.keys().forEachRemaining(languageCode -> {
                translations.putIfAbsent(languageCode, new HashMap<>());
                JSONObject biomeNamesLanguage = biomeNamesJson.optJSONObject(languageCode);
                biomeNamesLanguage.keys().forEachRemaining(
                    biomeKey -> translations.get(languageCode)
                        .put(biomeKey, biomeNamesLanguage.optString(biomeKey)));
            });
        } catch(Throwable ex) { ex.printStackTrace(); }
    }

    public static void onLevelLeft()
    {
        biomesInitialized = false;
        biomesById.clear();
        biomesByName.clear();
    }

    public static void cacheBiomeInterfaces(int[] id, String[] name, float[] temperature, float[] downfall, boolean[] humid, boolean[] snow)
    {
        biomesInitialized = true;
        for(int i = 0; i < id.length; i++)
        {
            BiomeInterface b = new BiomeInterface(id[i], name[i], temperature[i], downfall[i], humid[i], snow[i]);
            biomesById.put(id[i], b);
            biomesByName.put(name[i], b);
        }
        CallbacksModule.onBiomesInitialized();
    }

    @Nullable public static BiomeInterface getBiomeById(int id)
    {
        if(!biomesInitialized)
            throw new IllegalStateException("Cannot call BiomesModule.getBiomeById before biomes initialized (when entering the world). Create a handler for \"BiomesInitialized\" callback to solve this problem.");
        return biomesById.containsKey(id) ? biomesById.get(id) : null;
    }

    @Nullable public static BiomeInterface getBiomeByName(String name)
    {
        if(!biomesInitialized)
            throw new IllegalStateException("Cannot call BiomesModule.getBiomeByName before biomes initialized (when entering the world). Create a handler for \"BiomesInitialized\" callback to solve this problem.");
        return biomesByName.containsKey(name) ? biomesByName.get(name) : null;
    }

    public static final void forEachBiome(Consumer<BiomeInterface> callback)
    {
        biomesById.values().forEach(callback);
    }

    public static final class BiomeInterface {

        private final int id;
        private final String name;
        private final float temperature;
        private final float downfall;
        private final boolean humid;
        private final boolean snow;

        public BiomeInterface(int id, String name, float temperature, float downfall, boolean humid, boolean snow)
        {
            this.id = id;
            this.name = name;
            this.temperature = temperature;
            this.downfall = downfall;
            this.humid = humid;
            this.snow = snow;
        }

        public final int getNumericID()
        {
            return this.id;
        }

        public final String getNameID()
        {
            return this.name;
        }

        public final float getTemperature()
        {
            return this.temperature;
        }

        public final float getDownfall()
        {
            return this.downfall;
        }

        public final boolean isHumid()
        {
            return this.humid;
        }

        public final boolean isSnowCovered()
        {
            return this.snow;
        }

        public final boolean isVanilla()
        {
            return this.getNumericID() < 1024;
        }

        public final boolean isModded()
        {
            return !this.isVanilla();
        }

        public final String getTranslationKey()
        {
            String defaultKey = String.format("biome.%s.%s", this.isVanilla() ? "minecraft" : "innercore", this.getNameID());
            return customBiomeTranslationKeys.getOrDefault(this.getNameID(), defaultKey);
        }

        public final String getName()
        {
            return I18n.translate(this.getTranslationKey());
        }

    }

}
