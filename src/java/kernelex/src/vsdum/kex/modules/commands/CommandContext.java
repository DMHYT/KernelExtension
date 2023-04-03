package vsdum.kex.modules.commands;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

import org.json.JSONException;
import org.json.JSONObject;

import com.zhekasmirnov.apparatus.adapter.innercore.game.common.Vector3;

import android.support.annotation.Nullable;
import vsdum.kex.modules.commands.arguments.ArgumentBase;
import vsdum.kex.modules.commands.arguments.CommandArgumentType;
import vsdum.kex.natives.Actor;
import vsdum.kex.natives.Dimension;
import vsdum.kex.natives.Level;
import vsdum.kex.natives.Player;

public class CommandContext {
    
    private final long commandPtr;
    private final long originPtr;
    private final long outputPtr;
    private final Map<String, ArgumentBase> argsByName;
    private final Vector3 sourceBlockPosition;
    private final Vector3 sourceWorldPosition;
    @Nullable private final Level sourceLevel;
    @Nullable private final Dimension sourceDimension;
    @Nullable private final Actor sourceEntity;
    @Nullable private final Player sourcePlayer;

    public CommandContext(long commandPtr, long originPtr, long outputPtr, Map<String, ArgumentBase> argsByName)
    {
        this.commandPtr = commandPtr;
        this.originPtr = originPtr;
        this.outputPtr = outputPtr;
        this.argsByName = argsByName;
        int[] blockpos = CommandsNativeAPI.nativeGetSourceBlockPosition(this.originPtr);
        this.sourceBlockPosition = new Vector3(blockpos[0], blockpos[1], blockpos[2]);
        float[] worldpos = CommandsNativeAPI.nativeGetSourceWorldPosition(this.originPtr);
        this.sourceWorldPosition = new Vector3(worldpos[0], worldpos[1], worldpos[2]);
        long levelPtr = CommandsNativeAPI.nativeGetSourceLevel(this.originPtr);
        long dimensionPtr = CommandsNativeAPI.nativeGetSourceDimension(this.originPtr);
        long entityUID = CommandsNativeAPI.nativeGetSourceEntity(this.originPtr);
        this.sourceLevel = levelPtr == 0L ? null : new Level(levelPtr);
        this.sourceDimension = dimensionPtr == 0L ? null : new Dimension(dimensionPtr);
        this.sourceEntity = entityUID == 0L ? null : new Actor(entityUID);
        this.sourcePlayer = this.sourceEntity.isPlayer() ? this.sourceEntity.asPlayer() : null;
    }

    private void checkArgumentPresence(String name)
    {
        if(!argsByName.containsKey(name))
        {
            throw new IllegalArgumentException(String.format("Argument %s does not exist in this command overload, possible arguments are %s", name, Arrays.toString(this.argsByName.keySet().toArray())));
        }
    }

    private void checkArgumentType(ArgumentBase arg, CommandArgumentType type)
    {
        if(arg.type.type != type.type)
        {
            throw new IllegalArgumentException(String.format("Argument %s is not of type %s", arg.name, type.typeName));
        }
    }

    public int getInt(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        if(arg.type.type != 0 && arg.type.type != 11)
        {
            throw new IllegalArgumentException(String.format("Argument %s is not of type Integer", arg.name));
        }
        return CommandsNativeAPI.nativeGetInt(this.commandPtr, arg.fieldOffset);
    }

    public float getFloat(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        checkArgumentType(arg, CommandArgumentType.FLOAT);
        return CommandsNativeAPI.nativeGetFloat(this.commandPtr, arg.fieldOffset);
    }

    public boolean getBool(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        checkArgumentType(arg, CommandArgumentType.BOOL);
        return CommandsNativeAPI.nativeGetBool(this.commandPtr, arg.fieldOffset);
    }

    public float getRelativeFloat(String name, float center)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        checkArgumentType(arg, CommandArgumentType.RELATIVE_FLOAT);
        return CommandsNativeAPI.nativeGetRelativeFloat(this.commandPtr, arg.fieldOffset, center);
    }

    public Vector3 getPosition(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        checkArgumentType(arg, CommandArgumentType.POSITION);
        return new Vector3(CommandsNativeAPI.nativeGetPosition(this.commandPtr, arg.fieldOffset, this.originPtr));
    }

    public Vector3 getFloatPosition(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        checkArgumentType(arg, CommandArgumentType.FLOAT_POSITION);
        return new Vector3(CommandsNativeAPI.nativeGetFloatPosition(this.commandPtr, arg.fieldOffset, this.originPtr));
    }

    public String getString(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        if(arg.type.type != 6 && arg.type.type != 12)
        {
            throw new IllegalArgumentException(String.format("Argument %s is not of type String", arg.name));
        }
        return CommandsNativeAPI.nativeGetString(this.commandPtr, arg.fieldOffset);
    }

    public String getMessage(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        checkArgumentType(arg, CommandArgumentType.MESSAGE);
        return CommandsNativeAPI.nativeGetMessage(this.commandPtr, arg.fieldOffset, this.originPtr);
    }

    @Nullable public JSONObject getJson(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        checkArgumentType(arg, CommandArgumentType.JSON);
        try {
            JSONObject result = new JSONObject(CommandsNativeAPI.nativeGetJson(this.commandPtr, arg.fieldOffset));
            return result;
        } catch(JSONException ex) {}
        return null;
    }

    public List<Actor> getEntities(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        checkArgumentType(arg, CommandArgumentType.ENTITY);
        List<Actor> result = new ArrayList<>();
        for(long id : CommandsNativeAPI.nativeGetEntities(this.commandPtr, arg.fieldOffset, this.originPtr))
        {
            result.add(new Actor(id));
        }
        return result;
    }

    public List<Player> getPlayers(String name)
    {
        checkArgumentPresence(name);
        ArgumentBase arg = argsByName.get(name);
        checkArgumentType(arg, CommandArgumentType.PLAYER);
        List<Player> result = new ArrayList<>();
        for(long id : CommandsNativeAPI.nativeGetPlayers(this.commandPtr, arg.fieldOffset, this.originPtr))
        {
            result.add(new Player(id));
        }
        return result;
    }

    @Nullable public Player getPlayer(String name)
    {
        List<Player> players = this.getPlayers(name);
        return players.size() == 1 ? players.get(0) : null;
    }

    public final Vector3 getSourceBlockPosition()
    {
        return this.sourceBlockPosition;
    }

    public final Vector3 getSourceWorldPosition()
    {
        return this.sourceWorldPosition;
    }

    @Nullable public final Level getSourceLevel()
    {
        return this.sourceLevel;
    }

    @Nullable public final Dimension getSourceDimension()
    {
        return this.sourceDimension;
    }

    @Nullable public final Actor getSourceEntity()
    {
        return this.sourceEntity;
    }

    @Nullable public final Player getSourcePlayer()
    {
        return this.sourcePlayer;
    }

    public void success()
    {
        CommandsNativeAPI.nativeEmptySuccess(this.outputPtr);
    }

    public void success(String msg)
    {
        CommandsNativeAPI.nativeSuccess(this.outputPtr, msg);
    }

    public void error(String msg)
    {
        CommandsNativeAPI.nativeError(this.outputPtr, msg);
    }
    
}
