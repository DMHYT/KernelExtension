package vsdum.kex.modules;

import java.util.HashMap;
import java.util.Map;

import org.mozilla.javascript.ScriptableObject;

import com.zhekasmirnov.apparatus.mcpe.NativeBlockSource;
import com.zhekasmirnov.innercore.api.mod.ScriptableObjectHelper;
import com.zhekasmirnov.innercore.api.runtime.other.NameTranslation;

import vsdum.kex.natives.Actor;
import vsdum.kex.natives.ActorDamageSource;
import vsdum.kex.util.CommonTypes;

public class DamageModule {

    protected static native int nativeNewCause(String name);
    protected static native void nativeSetFire(int id);
    protected static native boolean nativeIsFire(int id);
    protected static native void nativeEnableCustomTranslationCallbackFor(int id);
    protected static native void nativeDamageEntityCommon(long entity, int damage, int cause, boolean b1, boolean b2);
    protected static native void nativeDamageEntityActor(long entity, int damage, int cause, boolean b1, boolean b2, long attacker);
    protected static native void nativeDamageEntityWorld(long entity, int damage, int cause, boolean b1, boolean b2, long bsptr);
    protected static native void nativeDamageEntityBlock(long entity, int damage, int cause, boolean b1, boolean b2, long bsptr, int x, int y, int z);

    public static interface CustomTranslationCallback {
        public String get(ActorDamageSource source, String nickname, Actor actor);
    }

    private static final Map<Integer, CustomTranslationCallback> customTranslationCallbacks = new HashMap<>();

    public static String getDeathMessage(long sourcePtr, String nickname, long actorPtr)
    {
        ActorDamageSource source = new ActorDamageSource(sourcePtr);
        Actor actor = new Actor(actorPtr);
        int cause = source.getCause();
        if(!customTranslationCallbacks.containsKey(cause)) return "death.kex.unknown";
        return customTranslationCallbacks.get(cause).get(source, nickname, actor);
    }

    private static final Map<String, Map<String, String>> deathMessageTranslations = new HashMap<>();

    private static Map<String, String> getTranslationsMapForCause(String causeName)
    {
        if(!deathMessageTranslations.containsKey(causeName)) deathMessageTranslations.put(causeName, new HashMap<>());
        return deathMessageTranslations.get(causeName);
    }

    private static String translateDeathMessage(String causeName)
    {
        if(!deathMessageTranslations.containsKey(causeName)) return "death.kex." + causeName;
        Map<String, String> translations = deathMessageTranslations.get(causeName);
        String language = CommonTypes.getShortLanguageName(NameTranslation.getLanguage());
        if(!translations.containsKey(language))
        {
            if(!translations.containsKey("en")) return "death.kex." + causeName;
            return translations.get("en");
        }
        return translations.get(language);
    }

    public static String translateAndFormatDeathMessage(String causeName, String[] formatData)
    {
        String translated = translateDeathMessage(causeName);
        if(translated.equals("death.kex." + causeName)) return translated;
        return CommonTypes.formatLikeInVanilla(translated, formatData);
    }
    
    public static class CustomCause {

        public final String name;
        public final int id;

        public CustomCause(String name)
        {
            this.name = name;
            this.id = nativeNewCause(this.name);
            if(this.id == -1) throw new IllegalArgumentException("Custom damage cause \"" + name + "\" has already been registered before! Try using another name!");
        }

        public CustomCause setFire()
        {
            nativeSetFire(this.id);
            return this;
        }

        public CustomCause setDeathMessage(String message)
        {
            getTranslationsMapForCause(this.name).put("en", message);
            return this;
        }

        public CustomCause setDeathMessage(ScriptableObject translations)
        {
            Object[] keys = translations.getAllIds();
            Map<String, String> translationsMap = getTranslationsMapForCause(this.name);
            for(int i = 0; i < keys.length; i++)
            {
                Object obj = keys[i];
                if(obj instanceof String)
                {
                    String str = (String) obj;
                    translationsMap.put(str, new StringBuilder().append("").append(translations.get(str, translations)).toString());
                }
            }
            return this;
        }

        public CustomCause setDeathMessageCallback(CustomTranslationCallback callback)
        {
            nativeEnableCustomTranslationCallbackFor(this.id);
            customTranslationCallbacks.put(this.id, callback);
            return this;
        }

    }

    public static void damageEntity(long entity, int damage, int cause)
    {
        nativeDamageEntityCommon(entity, damage, cause, false, false);
    }

    public static void damageEntity(long entity, int damage, int cause, ScriptableObject params)
    {
        boolean b1 = ScriptableObjectHelper.getBooleanProperty(params, "bool1", false);
        boolean b2 = ScriptableObjectHelper.getBooleanProperty(params, "bool2", false);
        if(ScriptableObject.hasProperty(params, "source"))
        {
            String source = ScriptableObjectHelper.getStringProperty(params, "source", "");
            if(source.equals("actor") || source.equals("entity"))
            {
                if(ScriptableObject.hasProperty(params, "attacker"))
                {
                    nativeDamageEntityActor(entity, damage, cause, b1, b2, ScriptableObjectHelper.getLongProperty(params, "attacker", 0));
                } else throw new IllegalArgumentException("If you specify actor|entity source type in DamageModule.damageEntity params object, you have to specify attacker entity UID in attacker field. It was not found!");
            } else if(source.equals("blocksource") || source.equals("world")) {
                Object world;
                if(ScriptableObject.hasProperty(params, "world"))
                {
                    world = ScriptableObject.getProperty(params, "world");
                } else if(ScriptableObject.hasProperty(params, "region")) {
                    world = ScriptableObject.getProperty(params, "region");
                } else throw new IllegalArgumentException("If you specify blocksource|world source type in DamageModule.damageEntity params object, you have to specify BlockSource object in world or region field. It was not found!");
                if(world instanceof NativeBlockSource)
                {
                    nativeDamageEntityWorld(entity, damage, cause, b1, b2, ((NativeBlockSource) world).getPointer());
                } else throw new IllegalArgumentException("world|region field in DamageModule.dealDamage params object is not an instance of BlockSource!");
            } else if(source.equals("block")) {
                Object world;
                if(ScriptableObject.hasProperty(params, "world"))
                {
                    world = ScriptableObject.getProperty(params, "world");
                } else if(ScriptableObject.hasProperty(params, "region")) {
                    world = ScriptableObject.getProperty(params, "region");
                } else throw new IllegalArgumentException("If you specify block source type in DamageModule.damageEntity params object, you have to specify BlockSource object in world or region field. It was not found!");
                if(world instanceof NativeBlockSource)
                {
                    if(ScriptableObject.hasProperty(params, "pos")) {
                        ScriptableObject pos = ScriptableObjectHelper.getScriptableObjectProperty(params, "pos", null);
                        if(pos != null)
                        {
                            int[] coords = CommonTypes.deserializeIntVec3(pos);
                            nativeDamageEntityBlock(entity, damage, cause, b1, b2, ((NativeBlockSource) world).getPointer(), coords[0], coords[1], coords[2]);
                        } else throw new IllegalArgumentException("pos field in DamageModule.dealDamage params object is not valid!");
                    } else if(ScriptableObject.hasProperty(params, "position")) {
                        ScriptableObject position = ScriptableObjectHelper.getScriptableObjectProperty(params, "position", null);
                        if(position != null)
                        {
                            int[] coords = CommonTypes.deserializeIntVec3(position);
                            nativeDamageEntityBlock(entity, damage, cause, b1, b2, ((NativeBlockSource) world).getPointer(), coords[0], coords[1], coords[2]);
                        } else throw new IllegalArgumentException("position field in DamageModule.dealDamage params object is not valid!");
                    } else {
                        int[] coords = CommonTypes.deserializeIntVec3(params);
                        nativeDamageEntityBlock(entity, damage, cause, b1, b2, ((NativeBlockSource) world).getPointer(), coords[0], coords[1], coords[2]);
                    }
                } else throw new IllegalArgumentException("world|region field in DamageModule.dealDamage params object is not an instance of BlockSource!");
                
            } else throw new IllegalArgumentException(String.format("DamageModule.damageEntity does not take source type %s, possible sources are: actor|entity, blocksource|world, block!", new Object[]{ source }));
        } else nativeDamageEntityCommon(entity, damage, cause, b1, b2);
    }

    public static native boolean isFire(int id);

}