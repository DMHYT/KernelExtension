package vsdum.kex.japi.internal.block;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.zhekasmirnov.innercore.api.NativeAPI;
import com.zhekasmirnov.innercore.api.NativeBlockRenderer;
import com.zhekasmirnov.innercore.api.NativeICRender;
import com.zhekasmirnov.innercore.api.NativeItemModel;
import com.zhekasmirnov.innercore.api.NativeICRender.*;
import com.zhekasmirnov.innercore.utils.FileTools;

import android.support.annotation.Nullable;
import android.util.Pair;
import vsdum.kex.japi.blocks.Block;
import vsdum.kex.japi.blocks.BlockRegistry;
import vsdum.kex.japi.blocks.components.ICustomCollisionShape;
import vsdum.kex.japi.internal.ResourceManager;
import vsdum.kex.japi.internal.block.model.BakedBlockModel;
import vsdum.kex.japi.internal.block.model.BlockModelManager;
import vsdum.kex.japi.internal.block.model.WeightedRandomRenderCondition;
import vsdum.kex.util.AddonUtils;
import vsdum.kex.util.mcmath.BlockPos;
import vsdum.kex.util.mcmath.Direction;

public class BlockVariantParser {
    
    public static void onModsLoaded()
    {
        ResourceManager.forEachFileIn("blockstates", file -> {
            String fileName = file.getName();
            if(fileName.toLowerCase().endsWith(".json"))
            {
                fileName = fileName.substring(0, fileName.length() - 5);
                String blockNameID = "block_" + NativeAPI.convertNameId(fileName);
                int blockID = AddonUtils.getNumericIdFromIdentifier(blockNameID);
                if(blockID != -1)
                {
                    try {
                        JSONObject json = FileTools.readJSON(file.getAbsolutePath());
                        Map<Integer, Pair<String, Integer>> particleTextures = parseBlockStateJson(blockID, json);
                        Block block = BlockRegistry.getBlockById(blockID);
                        if(block != null && block.defineData == null) fillBlockDefineData(block, json, particleTextures);
                    } catch(Throwable ex) { ex.printStackTrace(); }
                }
            }
        });
    }

    private static void fillBlockDefineData(Block block, JSONObject json, Map<Integer, Pair<String, Integer>> particleTextures)
    throws JSONException
    {
        if(json.has("variants") && json.get("variants") instanceof JSONArray)
        {
            block.defineData = new JSONArray();
            JSONArray variants = json.getJSONArray("variants");
            for(int meta = 0; meta < Math.min(variants.length(), 16); meta++)
            {
                Object variantObj = variants.get(meta);
                if(variantObj instanceof JSONObject || variantObj instanceof JSONArray)
                {
                    Pair<String, Integer> particleTexture = particleTextures.getOrDefault(meta, new Pair<>("missing_texture", 0));
                    block.defineData.put(new JSONObject()
                        .put("name", "block." + NativeAPI.convertNameId(block.nameID) + ".name")
                        .put("texture", new JSONArray().put(new JSONArray().put(particleTexture.first).put(particleTexture.second)))
                        .put("inCreative", true));
                }
            }
        } else if(json.has("multipart")) {
            Pair<String, Integer> particleTexture = particleTextures.getOrDefault(0, new Pair<>("missing_texture", 0));
            block.defineData = new JSONArray()
                .put(new JSONObject()
                    .put("name", "block." + NativeAPI.convertNameId(block.nameID) + ".name")
                    .put("texture", new JSONArray().put(new JSONArray().put(particleTexture.first).put(particleTexture.second)))
                    .put("inCreative", true));
        }
        block.getRegistryObject().register();
    }

    private static Map<Integer, Pair<String, Integer>> parseBlockStateJson(int blockID, JSONObject json)
    throws Throwable
    {
        Map<Integer, Pair<String, Integer>> result = new HashMap<>();
        if(json.has("variants") && json.get("variants") instanceof JSONArray)
        {
            JSONArray variantsArray = json.getJSONArray("variants");
            for(int variant = 0; variant < Math.min(variantsArray.length(), 16); variant++)
            {
                Object variantObj = variantsArray.get(variant);
                if(!(variantObj instanceof JSONObject || variantObj instanceof JSONArray)) continue;
                result.put(variant, parseBlockVariant(blockID, variant, variantObj));
            }
        } else result.put(0, parseBlockVariant(blockID, -1, json));
        return result;
    }

    private static Pair<String, Integer> parseBlockVariant(int blockID, int meta, Object variant)
    throws Throwable
    {
        Model model = new Model();
        Model handModel = null;
        Model guiModel = null;
        Set<Pair<BakedBlockModel, WeightedRandomRenderCondition>> parsed = parseWeightedModelVariants(variant);
        Pair<String, Integer> result = new Pair<>("missing_texture", 0);
        if(!parsed.isEmpty())
        {
            for(Pair<BakedBlockModel, WeightedRandomRenderCondition> pair : parsed)
            {
                RenderEntry entry = model.addEntry(pair.first.mesh);
                if(pair.second != null) entry.setCondition((WeightedRandomRenderCondition) pair.second);
                if(pair.first.handModel.isPresent())
                {
                    if(handModel == null) handModel = new Model();
                    RenderEntry handEntry = handModel.addEntry(pair.first.handMesh);
                    if(pair.second != null) handEntry.setCondition((WeightedRandomRenderCondition) pair.second);
                }
                if(pair.first.guiModel.isPresent())
                {
                    if(guiModel == null) guiModel = new Model();
                    RenderEntry guiEntry = guiModel.addEntry(pair.first.guiMesh);
                    if(pair.second != null) guiEntry.setCondition((WeightedRandomRenderCondition) pair.second);
                }
            }
            Set<Pair<BakedBlockModel, Object>> parsedCopy = new HashSet<>();
            for(Pair<BakedBlockModel, WeightedRandomRenderCondition> pair : parsed)
                parsedCopy.add(new Pair<>(pair.first, pair.second));
            tryAutoSetCollisionShapeFor(blockID, meta, parsedCopy);
            result = determineParticleTexture(parsed);
        } else if(variant instanceof JSONObject) {
            JSONObject variantJson = (JSONObject) variant;
            if(variantJson.optJSONArray("multipart") != null)
                result = parseMultipartBlockJson(blockID, meta, model, handModel, guiModel, variantJson.getJSONArray("multipart"));
        }
        NativeBlockRenderer.setStaticICRender(blockID, meta, model);
        NativeItemModel itemModel = NativeItemModel.getFor(blockID, meta);
        if(handModel != null) itemModel.setHandModel(handModel);
        if(guiModel != null) itemModel.setUiModel(guiModel);
        return result;
    }

    private static Pair<String, Integer> parseMultipartBlockJson(int blockID, int meta, Model model, @Nullable Model handModel, @Nullable Model guiModel, JSONArray entries)
    throws Throwable
    {
        CollisionShape collisionShape = canAutoSetCollisionShapeFor(blockID, meta) ? new CollisionShape() : null;
        Set<Pair<BakedBlockModel, WeightedRandomRenderCondition>> allModels = new HashSet<>();
        for(int i = 0; i < entries.length(); i++)
        {
            JSONObject entry = entries.optJSONObject(i);
            if(entry == null || !entry.has("apply")) continue;
            Set<Pair<BakedBlockModel, WeightedRandomRenderCondition>> parsed = parseWeightedModelVariants(entry.get("apply"));
            if(parsed.isEmpty()) continue;
            Object condition = null;
            if(entry.has("when"))
            {
                JSONObject entryWhen = entry.optJSONObject("when");
                if(entryWhen != null) condition = parseBlockModelPartCondition(entryWhen);
            }
            for(Pair<BakedBlockModel, WeightedRandomRenderCondition> pair : parsed)
            {
                RenderEntry renderEntry = model.addEntry(pair.first.mesh);
                Object entryCondition = WeightedRandomRenderCondition.mergeWithInnerCore(pair.second, condition);
                if(entryCondition != null) renderEntry.setCondition((AND) entryCondition);
                if(pair.first.handModel.isPresent())
                {
                    if(handModel == null) handModel = new Model();
                    RenderEntry handEntry = handModel.addEntry(pair.first.handMesh);
                    if(entryCondition != null) handEntry.setCondition((AND) entryCondition);
                }
                if(pair.first.guiModel.isPresent())
                {
                    if(guiModel == null) guiModel = new Model();
                    RenderEntry guiEntry = guiModel.addEntry(pair.first.guiMesh);
                    if(entryCondition != null) guiEntry.setCondition((AND) entryCondition);
                }
            }
            Set<Pair<BakedBlockModel, Object>> parsedCopy = new HashSet<>();
            for(Pair<BakedBlockModel, WeightedRandomRenderCondition> pair : parsed)
                parsedCopy.add(new Pair<>(pair.first, WeightedRandomRenderCondition.mergeWithInnerCore(pair.second, condition)));
            tryAutoSetCollisionShapeFor(blockID, meta, parsedCopy);
            allModels.addAll(parsed);
        }
        if(collisionShape != null) NativeBlockRenderer.setCustomCollisionAndRaycastShape(blockID, meta, collisionShape);
        return determineParticleTexture(allModels);
    }

    @Nullable private static Object parseBlockModelPartCondition(JSONObject when)
    throws Throwable
    {
        Object result = null;
        if(when.has("OR"))
            result = parseConditionOperator(when, "OR", OR.class);
        else if(when.has("AND"))
            result = parseConditionOperator(when, "AND", AND.class);
        else {
            Set<Object> options = new HashSet<>();
            for(Direction dir : Direction.VALUES)
                checkForBlock(when, dir, options);
            if(!options.isEmpty())
                result = options.size() == 1 ? options.toArray()[0] : AND.class.getConstructors()[0].newInstance(options.toArray());
        }
        return result;
    }

    @Nullable private static Object parseConditionOperator(JSONObject conditionJson, String key, Class<?> conditionClass)
    throws Throwable
    {
        JSONArray operator = conditionJson.optJSONArray(key);
        if(operator == null) return null;
        Set<Object> options = new HashSet<>();
        for(int i = 0; i < operator.length(); i++)
        {
            JSONObject option = operator.optJSONObject(i);
            if(option == null) continue;
            Object compiledOption = parseBlockModelPartCondition(option);
            if(compiledOption == null) continue;
            options.add(compiledOption);
        }
        return options.isEmpty() ? null : conditionClass.getConstructors()[0].newInstance(options.toArray());
    }

    private static void checkForBlock(JSONObject when, Direction dir, Set<Object> options)
    throws Throwable
    {
        String key = dir.toString();
        if(when.has(key))
        {
            String conditionValue = when.optString(key);
            if(conditionValue == null) return;
            String[] groups = conditionValue.split("\\|");
            BlockPos pos = BlockPos.ORIGIN.offset(dir);
            if(groups.length == 1) options.add(parseBlockCondition(groups[0], pos.x, pos.y, pos.z));
            else {
                Object[] orEntries = new Object[groups.length];
                for(int i = 0; i < groups.length; i++)
                    orEntries[i] = parseBlockCondition(groups[i], pos.x, pos.y, pos.z);
                options.add(OR.class.getConstructors()[0].newInstance(orEntries));
            }
        }
    }

    private static Object parseBlockCondition(String str, int x, int y, int z)
    {
        boolean exclude = str.startsWith("!");
        String group = exclude ? str.substring(1) : str;
        return new BLOCK(x, y, z, NativeICRender.getGroup(group), exclude);
    }

    @Nullable private static Set<Pair<BakedBlockModel, WeightedRandomRenderCondition>> parseWeightedModelVariants(Object modelObj)
    throws JSONException
    {
        if(!(modelObj instanceof JSONObject || modelObj instanceof JSONArray)) return new HashSet<>();
        Set<JSONObject> models = new HashSet<>();
        if(modelObj instanceof JSONObject) models.add((JSONObject) modelObj);
        else {
            JSONArray modelsArr = (JSONArray) modelObj;
            for(int i = 0; i < modelsArr.length(); i++)
            {
                Object modelJson = modelsArr.get(i);
                if(modelJson instanceof JSONObject) models.add((JSONObject) modelJson);
            }
        }
        if(models.isEmpty()) return new HashSet<>();
        int weightSum = 0;
        if(models.size() > 1)
            for(JSONObject modelJson : models)
                weightSum += parseModelVariantWeight(modelJson);
        int minWeightValue = 1;
        Set<Pair<BakedBlockModel, WeightedRandomRenderCondition>> result = new HashSet<>();
        for(JSONObject modelJson : models)
        {
            BakedBlockModel bakedModel = getBakedModelFromJson(modelJson);
            if(bakedModel == null) continue;
            WeightedRandomRenderCondition condition = null;
            if(weightSum > 0)
            {
                int weight = parseModelVariantWeight(modelJson);
                int minValue = minWeightValue;
                minWeightValue += weight;
                condition = new WeightedRandomRenderCondition(minValue, minWeightValue - 1, weightSum, weight);
            }
            result.add(new Pair<>(bakedModel, condition));
        }
        return result;
    }

    @Nullable private static BakedBlockModel getBakedModelFromJson(JSONObject json)
    {
        return BlockModelManager.getBakedModelWithRotation(
            json.optString("model", "block/cube"),
            json.optInt("x", 0) / 90 * 90,
            json.optInt("y", 0) / 90 * 90,
            json.optBoolean("uvlock", false)
        );
    }

    private static int parseModelVariantWeight(JSONObject modelJson)
    {
        return Math.max(modelJson.optInt("weight", 1), 1);
    }

    private static void tryAutoSetCollisionShapeFor(int blockID, int meta, Set<Pair<BakedBlockModel, Object>> parsed)
    {
        if(canAutoSetCollisionShapeFor(blockID, meta))
        {
            CollisionShape shape = new CollisionShape();
            for(Pair<BakedBlockModel, Object> pair : parsed)
            {
                CollisionEntry entry = shape.addEntry();
                if(pair.second != null) entry.setCondition((WeightedRandomRenderCondition) pair.second);
                pair.first.elements.forEach(cube -> cube.addToCollisionShape(entry));
            }
            NativeBlockRenderer.setCustomCollisionAndRaycastShape(blockID, meta, shape);
        }
    }

    private static boolean canAutoSetCollisionShapeFor(int blockID, int meta)
    {
        Block block = BlockRegistry.getBlockById(blockID);
        if(block == null) return true;
        if(!(block instanceof ICustomCollisionShape)) return true;
        ICustomCollisionShape component = (ICustomCollisionShape) block;
        if(!component.hasCollision(meta)) return false;
        CollisionShape shape = component.getCollisionShape(meta);
        if(shape == null) return true;
        shape.clear();
        return false;
    }

    private static Pair<String, Integer> determineParticleTexture(Set<Pair<BakedBlockModel, WeightedRandomRenderCondition>> bakedModelSet)
    {
        Map<String, Integer> textureCounts = new HashMap<>();
        for(Pair<BakedBlockModel, WeightedRandomRenderCondition> pair : bakedModelSet)
        {
            BakedBlockModel bakedModel = pair.first;
            String particleTexture = String.format("%s:%d", bakedModel.particleTexture.first, bakedModel.particleTexture.second);
            int count = textureCounts.getOrDefault(particleTexture, 0);
            textureCounts.put(particleTexture, count + pair.second.getWeight());
        }
        String[] chosen = getMostUsedTexture(textureCounts);
        return new Pair<>(chosen[0], Integer.parseInt(chosen[1]));
    }

    private static String[] getMostUsedTexture(Map<String, Integer> textureCounts)
    {
        Map.Entry<String, Integer> maxEntry = null;
        for(Map.Entry<String, Integer> entry : textureCounts.entrySet())
            if(maxEntry == null || entry.getValue().compareTo(maxEntry.getValue()) > 0)
                maxEntry = entry;
        return maxEntry.getKey().split(":");
    }

}
