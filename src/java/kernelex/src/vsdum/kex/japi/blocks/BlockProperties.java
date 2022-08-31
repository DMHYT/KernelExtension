package vsdum.kex.japi.blocks;

import com.zhekasmirnov.apparatus.minecraft.enums.GameEnums;
import com.zhekasmirnov.innercore.api.NativeBlock;

import vsdum.kex.japi.blocks.enums.BlockColorSource;
import vsdum.kex.modules.ToolsModule;

public class BlockProperties {

    public static final BlockProperties DEFAULT = new BlockProperties();

    private boolean canBeExtraBlock = false;
    private boolean canContainLiquid = false;
    private BlockColorSource colorSource = BlockColorSource.NONE;
    private int destroyLevel = 0;
    private float destroyTime = 1.0f;
    private float explosionResistance = 3.0f;
    private float friction = .6f;
    private int lightLevel = 0;
    private int lightOpacity = 0;
    private int mapColor = 0;
    private String material = null;
    private int materialBase = 0;
    private boolean renderAllFaces = false;
    private int renderLayer = GameEnums.getInt(GameEnums.getSingleton().getEnum("block_render_layer", "alpha"));
    private int renderType = 0;
    private boolean solid = false;
    private String sound = "";
    private int terrainMaterial = 3;
    private float translucency = 1.0f;

    public BlockProperties() {}

    public BlockProperties(BlockProperties parent)
    {
        this.canBeExtraBlock = parent.canBeExtraBlock;
        this.canContainLiquid = parent.canContainLiquid;
        this.colorSource = parent.colorSource;
        this.destroyLevel = parent.destroyLevel;
        this.destroyTime = parent.destroyTime;
        this.explosionResistance = parent.explosionResistance;
        this.friction = parent.friction;
        this.lightLevel = parent.lightLevel;
        this.lightOpacity = parent.lightOpacity;
        this.mapColor = parent.mapColor;
        this.material = parent.material;
        this.materialBase = parent.materialBase;
        this.renderAllFaces = parent.renderAllFaces;
        this.renderLayer = parent.renderLayer;
        this.renderType = parent.renderType;
        this.solid = parent.solid;
        this.sound = parent.sound;
        this.terrainMaterial = parent.terrainMaterial;
        this.translucency = parent.translucency;
    }

    public final BlockProperties copy()
    {
        return new BlockProperties(this);
    }

    public final void apply(Block block)
    {
        NativeBlock.setCanBeExtraBlock(block.id, this.canBeExtraBlock);
        NativeBlock.setCanContainLiquid(block.id, this.canContainLiquid);
        NativeBlock.setBlockColorSource(block.id, this.colorSource.ordinal());
        ToolsModule.setBlockDestroyLevel(block.id, this.destroyLevel);
        NativeBlock.setDestroyTime(block.id, this.destroyTime);
        NativeBlock.setExplosionResistance(block.id, this.explosionResistance);
        NativeBlock.setFriction(block.id, this.friction);
        NativeBlock.setLightLevel(block.id, this.lightLevel);
        NativeBlock.setLightOpacity(block.id, this.lightOpacity);
        NativeBlock.setMapColor(block.id, this.mapColor);
        ToolsModule.setBlockMaterialName(block.id, this.material);
        NativeBlock.setMaterialBase(block.id, this.materialBase);
        NativeBlock.setRenderAllFaces(block.id, this.renderAllFaces);
        NativeBlock.setRenderLayer(block.id, this.renderLayer);
        NativeBlock.setRenderType(block.id, this.renderType);
        NativeBlock.setSolid(block.id, this.solid);
        NativeBlock.setSoundType(block.id, this.sound);
        NativeBlock.setMaterial(block.id, this.terrainMaterial);
        NativeBlock.setTranslucency(block.id, this.translucency);
    }

    public BlockProperties setCanBeExtraBlock(boolean can)
    {
        this.canBeExtraBlock = can;
        return this;
    }

    public BlockProperties setCanContainLiquid(boolean can)
    {
        this.canContainLiquid = can;
        return this;
    }

    public BlockProperties setColorSource(BlockColorSource colorSource)
    {
        this.colorSource = colorSource;
        return this;
    }

    public BlockProperties setDestroyLevel(int destroyLevel)
    {
        this.destroyLevel = destroyLevel;
        return this;
    }

    public BlockProperties setDestroyTime(float destroyTime)
    {
        this.destroyTime = destroyTime;
        return this;
    }

    public BlockProperties setExplosionResistance(float explosionResistance)
    {
        this.explosionResistance = explosionResistance;
        return this;
    }

    public BlockProperties setFriction(float friction)
    {
        this.friction = friction;
        return this;
    }

    public BlockProperties setLightLevel(int lightLevel)
    {
        this.lightLevel = lightLevel;
        return this;
    }

    public BlockProperties setLightOpacity(int lightOpacity)
    {
        this.lightOpacity = lightOpacity;
        return this;
    }

    public BlockProperties setMapColor(int mapColor)
    {
        this.mapColor = mapColor;
        return this;
    }

    public BlockProperties setMaterial(String material)
    {
        this.material = material;
        return this;
    }

    public BlockProperties setMaterialBase(int baseID)
    {
        this.materialBase = baseID;
        return this;
    }

    public BlockProperties setRenderAllFaces(boolean renderAllFaces)
    {
        this.renderAllFaces = renderAllFaces;
        return this;
    }

    public BlockProperties setRenderLayer(int renderLayer)
    {
        this.renderLayer = renderLayer;
        return this;
    }

    public BlockProperties setRenderType(int renderType)
    {
        this.renderType = renderType;
        return this;
    }

    public BlockProperties setSolid(boolean solid)
    {
        this.solid = solid;
        return this;
    }

    public BlockProperties setSound(String sound)
    {
        this.sound = sound;
        return this;
    }

    public BlockProperties setTerrainMaterial(int terrainMaterial)
    {
        this.terrainMaterial = terrainMaterial;
        return this;
    }

    public BlockProperties setTranslucency(float translucency)
    {
        this.translucency = translucency;
        return this;
    }

}
