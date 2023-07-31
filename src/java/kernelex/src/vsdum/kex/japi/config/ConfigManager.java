package vsdum.kex.japi.config;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.EnumMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.function.Consumer;
import java.util.stream.Collectors;

import org.json.JSONException;
import org.json.JSONObject;

import com.zhekasmirnov.apparatus.multiplayer.NetworkJsAdapter;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI.MCSystem;
import com.zhekasmirnov.innercore.api.runtime.saver.world.WorldDataSaverHandler;
import com.zhekasmirnov.innercore.utils.FileTools;

import vsdum.kex.common.CallbackFunction;

public final class ConfigManager {

    static final Map<ModConfig.Type, Set<ModConfig>> configs = new EnumMap<>(ModConfig.Type.class);
    static final List<CallbackFunction<Consumer<ModConfig>>> eventsReloading = new ArrayList<>();
    static final List<CallbackFunction<Consumer<ModConfig>>> eventsLoading = new ArrayList<>();
    static final List<CallbackFunction<Consumer<ModConfig>>> eventsUnloading = new ArrayList<>();

    public static void addOnReloadEventHandler(Consumer<ModConfig> handler)
    {
        addOnReloadEventHandler(handler, 0);
    }

    public static void addOnReloadEventHandler(Consumer<ModConfig> handler, int priority)
    {
        CallbackFunction.addToList(new CallbackFunction<Consumer<ModConfig>>(handler, priority), eventsReloading);
    }

    public static void addOnLoadEventHandler(Consumer<ModConfig> handler)
    {
        addOnLoadEventHandler(handler, 0);
    }

    public static void addOnLoadEventHandler(Consumer<ModConfig> handler, int priority)
    {
        CallbackFunction.addToList(new CallbackFunction<Consumer<ModConfig>>(handler, priority), eventsLoading);
    }

    public static void addOnUnloadEventHandler(Consumer<ModConfig> handler)
    {
        addOnUnloadEventHandler(handler, 0);
    }

    public static void addOnUnloadEventHandler(Consumer<ModConfig> handler, int priority)
    {
        CallbackFunction.addToList(new CallbackFunction<Consumer<ModConfig>>(handler, priority), eventsUnloading);
    }

    public static void registerConfig(ModConfig.Type type, IConfigSpec<?> spec, String modId)
    {
        if(spec.isEmpty())
        {
            Logger.debug("KEX-ConfigSpec", String.format("Attempted to register an empty config for type %s on mod %s", type.extension(), modId));
            return;
        }
        configs.putIfAbsent(type, new HashSet<>());
        configs.get(type).add(new ModConfig(type, spec, modId));
    }

    public static void registerConfig(ModConfig.Type type, IConfigSpec<?> spec, String modId, String fileName)
    {
        if(spec.isEmpty())
        {
            Logger.debug("KEX-ConfigSpec", String.format("Attempted to register an empty config for type %s on mod %s using file name %s", type.extension(), modId, fileName));
            return;
        }
        configs.putIfAbsent(type, new HashSet<>());
        configs.get(type).add(new ModConfig(type, spec, modId, fileName));
    }

    public static void forEachConfig(ModConfig.Type type, Consumer<ModConfig> action)
    {
        Optional.ofNullable(configs.get(type))
            .ifPresent(set -> set.forEach(action));
    }

    private static boolean initialized = false;

    public static void init()
    {
        if(!initialized)
        {
            initialized = true;
            FileTools.assureDir(ConfigTracker.CONFIG_DIR);
            File configBasePath = new File(ConfigTracker.CONFIG_DIR);
            ConfigTracker.INSTANCE.loadConfigs(ModConfig.Type.CLIENT, configBasePath);
            ConfigTracker.INSTANCE.loadConfigs(ModConfig.Type.COMMON, configBasePath);
            NetworkJsAdapter network = MCSystem.getNetwork();
            // syncing server configurations on all clients
            network.getServer().addOnClientConnectedListener(client -> {
                JSONObject packet = new JSONObject();
                ConfigTracker.INSTANCE.configSets().get(ModConfig.Type.SERVER)
                    .stream()
                    .collect(Collectors.toMap(ModConfig::getFileName, mc -> {
                        try {
                            return FileTools.readFileText(mc.getFile().getAbsolutePath());
                        } catch(IOException ex) { throw new RuntimeException(ex); }
                    }))
                    .forEach((fileName, fileText) -> {
                        try {
                            packet.put(fileName, fileText);
                        } catch(JSONException ex) { throw new RuntimeException(ex); }
                    });
                client.send("kex.config.sync", packet);
            });
            network.addClientPacket("kex.config.sync", (packetObj, str, clazz) -> {
                if(network.inRemoteWorld() && packetObj instanceof JSONObject)
                {
                    JSONObject packetJSON = (JSONObject) packetObj;
                    packetJSON.keys().forEachRemaining(fileName -> {
                        Optional.ofNullable(packetJSON.optString(fileName))
                            .ifPresent(fileText -> 
                                Optional.ofNullable(ConfigTracker.INSTANCE.fileMap().get(fileName))
                                    .ifPresent(modConfig -> modConfig.acceptSyncedConfig(fileText)));
                    });
                }
            });
        }
    }

    private static String currentServerConfigDir = null;

    public static void onLevelSelected()
    {
        if(!MCSystem.getNetwork().inRemoteWorld())
        {
            String worldDir = WorldDataSaverHandler.getInstance().getWorldDataSaver().getWorldDirectory().getAbsolutePath();
            currentServerConfigDir = worldDir + "/serverconfig/";
            FileTools.assureDir(currentServerConfigDir);
            ConfigTracker.INSTANCE.loadConfigs(ModConfig.Type.SERVER, new File(currentServerConfigDir));
        }
    }

    public static void onLevelLeft()
    {
        if(!MCSystem.getNetwork().inRemoteWorld())
        {
            ConfigTracker.INSTANCE.unloadConfigs(ModConfig.Type.SERVER, new File(currentServerConfigDir));
            currentServerConfigDir = null;
        }
    }

}
