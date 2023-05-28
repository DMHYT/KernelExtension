package vsdum.kex.japi.internal.block.model;

import java.util.Iterator;
import java.util.Map;
import java.util.Optional;

import org.json.JSONArray;
import org.json.JSONObject;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Pair;
import vsdum.kex.japi.internal.block.model.element.*;
import vsdum.kex.util.mcmath.Direction;
import vsdum.kex.util.mcmath.Vec2f;
import vsdum.kex.util.mcmath.Vec3d;

public class BlockModelParser {

    private final String resourceLocation;
    private final JSONObject json;
    @Nullable private BakedBlockModel bakedModel = null;

    public BlockModelParser(String resourceLocation, JSONObject json)
    {
        this.resourceLocation = resourceLocation;
        this.json = json;
    }

    @Nullable public BakedBlockModel bake()
    {
        return this.bakedModel;
    }

    public BlockModelParser parse()
    {
        this.checkParent();
        if(this.bakedModel == null) this.bakedModel = new BakedBlockModel();
        this.parseTextureVariables();
        this.resolveTexturesInParentCubes();
        this.parseCubes();
        this.parseItemModelModifications();
        return this;
    }

    private void checkParent()
    {
        if(!this.json.has("parent")) return;
        String parentLocation = this.json.optString("parent");
        if(parentLocation == null) return;
        BakedBlockModel parentModel = BlockModelManager.getBakedModelByResourceLocation(parentLocation);
        if(parentModel == null) return;
        this.bakedModel = parentModel.copy();
    }

    private void parseTextureVariables()
    {
        JSONObject textures = this.json.optJSONObject("textures");
        if(textures == null) return;
        Iterator<String> variables = textures.keys();
        while(variables.hasNext())
        {
            String variable = variables.next();
            if(variable.equals("particle")) continue;
            String texture = textures.optString(variable);
            if(texture == null) continue;
            Pair<String, Integer> texturePair = getTexturePair(texture);
            if(texturePair == null)
            {
                Logger.warning(String.format("[KEX-BlockModelParser] failed to parse block texture \"%s\" (variable #%s in model \"%s\")", texture, variable, this.resourceLocation));
                continue;
            }
            this.bakedModel.textureVariables.put("#" + variable, texturePair);
        }
        this.resolveVariablesRecursively();
        this.parseParticleTexture(textures);
    }

    private void resolveVariablesRecursively()
    {
        int unspecifiedCount = 0;
        for(Map.Entry<String, Pair<String, Integer>> e : this.bakedModel.textureVariables.entrySet())
        {
            Pair<String, Integer> texturePair = e.getValue();
            if(texturePair.first.startsWith("#") && this.bakedModel.textureVariables.containsKey(texturePair.first))
            {
                Pair<String, Integer> p = this.bakedModel.textureVariables.get(texturePair.first);
                if(texturePair != null)
                {
                    e.setValue(p);
                    unspecifiedCount++;
                }
            }
        }
        if(unspecifiedCount > 0) this.resolveVariablesRecursively();
    }

    private void resolveTexturesInParentCubes()
    {
        this.bakedModel.elements.forEach(cube -> {
            for(Face face : cube.faces)
                if(face != null && face.textureName.startsWith("#") && this.bakedModel.textureVariables.containsKey(face.textureName))
                {
                    Pair<String, Integer> texturePair = this.bakedModel.textureVariables.get(face.textureName);
                    if(texturePair == null) return;
                    face.textureName = texturePair.first;
                    face.textureMeta = texturePair.second;
                }
        });
    }

    private void parseParticleTexture(@NonNull JSONObject textures)
    {
        if(textures.has("particle"))
        {
            String particleTexture = textures.optString("particle");
            if(particleTexture == null) return;
            Pair<String, Integer> particlePair = getTexturePair(particleTexture);
            if(particlePair == null)
            {
                Logger.warning(String.format("[KEX-BlockModelParser] failed to parse block particle texture \"%s\" in model \"%s\"", particleTexture, this.resourceLocation));
                return;
            }
            this.bakedModel.particleTexture = new Pair<>(particlePair.first, particlePair.second);
        }
        if(this.bakedModel.particleTexture.first.startsWith("#") && this.bakedModel.textureVariables.containsKey(this.bakedModel.particleTexture.first))
        {
            Pair<String, Integer> pair = this.bakedModel.textureVariables.get(this.bakedModel.particleTexture.first);
            this.bakedModel.particleTexture = new Pair<>(pair.first, pair.second);
        }
    }

    private void parseCubes()
    {
        if(!this.json.has("elements")) return;
        JSONArray cubesArray = this.json.optJSONArray("elements");
        if(cubesArray == null) return;
        this.bakedModel.elements.clear();
        for(int i = 0; i < cubesArray.length(); i++)
        {
            JSONObject cubeJson = cubesArray.optJSONObject(i);
            if(cubeJson == null) continue;
            Cube cube = this.parseCube(cubeJson);
            if(cube == null) continue;
            this.bakedModel.elements.add(cube);
        }
    }

    @Nullable private Cube parseCube(@NonNull JSONObject cubeJson)
    {
        Vec3d from = deserializeCoordinates(cubeJson.optJSONArray("from"), -16D, 32D, false);
        Vec3d to = deserializeCoordinates(cubeJson.optJSONArray("to"), -16D, 32D, false);
        if(from == null || to == null) return null;
        Cube result = new Cube((float) from.x, (float) from.y, (float) from.z, (float) to.x, (float) to.y, (float) to.z);
        parseCubeRotation(cubeJson.optJSONObject("rotation"), result);
        this.parseCubeFaces(cubeJson.optJSONObject("faces"), result);
        return result;
    }

    private static void parseCubeRotation(@Nullable JSONObject rotationJson, @NonNull Cube cube)
    {
        if(rotationJson == null) return;
        String axisString = rotationJson.optString("axis");
        byte axis = axisString == null ? -1 : rotationAxisFromString(axisString);
        if(axis == -1) return;
        double angle = rotationJson.optDouble("angle");
        if(angle == Double.NaN) return;
        angle = ((int) (angle / 22.5D)) * 22.5D;
        if(angle < -45D || angle > 45D) return;
        Vec3d origin = deserializeCoordinates(rotationJson.optJSONArray("origin"), -80D, 80D, false);
        origin = origin == null ? new Vec3d(.5D, .5D, .5D) : origin;
        cube.rot(axis, (float) angle, (float) origin.x, (float) origin.y, (float) origin.z, rotationJson.optBoolean("rescale", false));
    }

    private void parseCubeFaces(@Nullable JSONObject facesJson, @NonNull Cube cube)
    {
        for(Direction dir : Direction.values())
            this.parseCubeFace(dir.getIndex(), facesJson.optJSONObject(dir.toString()), cube);
    }

    private void parseCubeFace(int index, @Nullable JSONObject faceJson, @NonNull Cube cube)
    {
        if(faceJson == null) return;
        JSONArray uvArr = faceJson.optJSONArray("uv");
        if(uvArr == null) uvArr = new JSONArray().put(0).put(0).put(16).put(16);
        Pair<Vec2f, Vec2f> uv = deserializeUV(uvArr);
        if(uv == null) return;
        String textureVariable = faceJson.optString("texture");
        if(textureVariable == null || !textureVariable.startsWith("#")) return;
        Pair<String, Integer> texture = this.bakedModel.textureVariables.getOrDefault(textureVariable, new Pair<>(textureVariable, 0));
        int rightAngles = (faceJson.optInt("rotation", 0) % 360) / 90;
        cube.face(index, texture.first, texture.second, uv.first.x, uv.first.y, uv.second.x, uv.second.y, rightAngles);
    }

    @Nullable private static Pair<String, Integer> getTexturePair(@NonNull String texture)
    {
        String[] split = texture.split(":");
        if(split.length == 1) return new Pair<>(split[0], 0);
        if(split.length == 2) return new Pair<>(split[0], split[1].isEmpty() ? 0 : Integer.parseInt(split[1]));
        return null;
    }

    private static byte rotationAxisFromString(@NonNull String axis)
    {
        if(axis.equals("x")) return 0;
        if(axis.equals("y")) return 1;
        if(axis.equals("z")) return 2;
        return -1;
    }

    @Nullable public static Vec3d deserializeCoordinates(@Nullable JSONArray arr, double lowerClamp, double upperClamp, boolean clamp)
    {
        if(arr == null || arr.length() != 3) return null;
        double[] coords = new double[3];
        for(int i = 0; i < 3; i++)
        {
            double coord = arr.optDouble(i);
            if(coord == Double.NaN) return null;
            if(!clamp && (coord < lowerClamp || coord > upperClamp)) return null;
            if(coord < lowerClamp) coord = lowerClamp;
            if(coord > upperClamp) coord = upperClamp;
            if(coord == Double.NaN || coord < lowerClamp || coord > upperClamp) return null;
            coords[i] = coord;
        }
        return new Vec3d(coords[0], coords[1], coords[2]).scale(0.0625D);
    }

    @Nullable private static Pair<Vec2f, Vec2f> deserializeUV(@Nullable JSONArray arr)
    {
        if(arr == null || arr.length() != 4) return null;
        float[] uvs = new float[4];
        for(int i = 0; i < 4; i++)
        {
            double coord = arr.optDouble(i);
            if(coord == Double.NaN || coord < 0D || coord > 16D) return null;
            coord /= 16;
            uvs[i] = (float) coord;
        }
        return new Pair<>(new Vec2f(uvs[0], uvs[1]), new Vec2f(uvs[2], uvs[3]));
    }

    private void parseItemModelModifications()
    {
        if(this.json.has("display")) return;
        JSONObject display = this.json.optJSONObject("display");
        if(display == null) return;
        this.bakedModel.handModel = Optional.ofNullable(BakedBlockModel.ItemModelModifications.parse(display.optJSONObject("hand")));
        this.bakedModel.guiModel = Optional.ofNullable(BakedBlockModel.ItemModelModifications.parse(display.optJSONObject("gui")));
    }

}
