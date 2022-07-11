const ItemFactoryHelper = WRAP_JAVA("vsdum.kex.util.ItemFactoryHelper");
const ToolsModule = WRAP_JAVA("vsdum.kex.modules.ToolsModule");
type ItemTier = vsdum.kex.modules.ToolsModule.ItemTier;


declare namespace ToolAPI {
    interface BlockMaterial {
        name: string,
        multiplier: number;
    }
    export var blockMaterials: { [materialName: string]: BlockMaterial };
    export var toolMaterials: { [materialName: string]: ToolMaterial };
    export var toolData: { [numericId: number]: ToolParams };
    export var blockData: { [numericId: number]: { material: BlockMaterial, level: number, isNative: boolean } };
    export var unnamedMaterialNum: number;
    export var ToolType: {
        readonly sword: {},
        readonly axe: {},
        readonly pickaxe: {},
        readonly shovel: {},
        readonly hoe: {}
    }
    export interface ToolMaterial {
        level?: number,
        durability?: number,
        efficiency?: number,
        damage?: number,
        enchantability?: number,
        name: string;
    }
    export function startDestroyHook(coords: Callback.ItemUseCoordinates, block: Tile, carried: ItemInstance): void;
    export function destroyBlockHook(coords: Callback.ItemUseCoordinates, block: Tile, item: ItemInstance, player: number): void;
    export function playerAttackHook(attacker: number, victim: number, item: ItemInstance): void;
    export interface ExtendedToolParams extends ToolParams {
        getAttackDamageBonus?: (stack: ItemInstance) => number;
    }
}


declare namespace Block {
    export const idSource: typeof BlockID;
    export var clickFunctions: {[numericId: number]: Block.ClickFunction};
    export var dropFunctions: {[numericId: number]: Block.DropFunction};
    export var popResourceFunctions: {[numericId: number]: Block.PopResourcesFunction};
    export var entityInsideFunctions: {[numericId: number]: Block.EntityInsideFunction};
    export var entityStepOnFunctions: {[numericId: number]: Block.EntityStepOnFunction};
    export var neighbourChangeFunctions: {[numericId: number]: Block.NeighbourChangeFunction};
}


namespace Item {
    // @ts-ignore
    export function createSwordItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        let tier: vsdum.kex.modules.ToolsModule.ItemTier = ToolsModule.getTierByName(materialName);
        if(tier == null) {
            materialName = "wood";
            tier = ToolsModule.getTierByName(materialName);
        }
        ToolsModule.registerSword(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed sword>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            tier, typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
        ToolAPI.toolData[ItemID[id]] ??= { toolMaterial: ToolAPI.objectFromTier(tier, materialName), isWeapon: true, blockMaterials: ToolAPI.toolBlockTypes.sword };
    }
    // @ts-ignore
    export function createAxeItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        let tier: vsdum.kex.modules.ToolsModule.ItemTier = ToolsModule.getTierByName(materialName);
        if(tier == null) {
            materialName = "wood";
            tier = ToolsModule.getTierByName(materialName);
        }
        ToolsModule.registerAxe(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed axe>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            tier, typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
        ToolAPI.toolData[ItemID[id]] ??= { toolMaterial: ToolAPI.objectFromTier(tier, materialName), isWeapon: false, blockMaterials: ToolAPI.toolBlockTypes.axe };
    }
    // @ts-ignore
    export function createPickaxeItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        let tier: vsdum.kex.modules.ToolsModule.ItemTier = ToolsModule.getTierByName(materialName);
        if(tier == null) {
            materialName = "wood";
            tier = ToolsModule.getTierByName(materialName);
        }
        ToolsModule.registerPickaxe(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed pickaxe>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            tier, typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
        ToolAPI.toolData[ItemID[id]] ??= { toolMaterial: ToolAPI.objectFromTier(tier, materialName), isWeapon: false, blockMaterials: ToolAPI.toolBlockTypes.pickaxe };
    }
    // @ts-ignore
    export function createShovelItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        let tier: vsdum.kex.modules.ToolsModule.ItemTier = ToolsModule.getTierByName(materialName);
        if(tier == null) {
            materialName = "wood";
            tier = ToolsModule.getTierByName(materialName);
        }
        ToolsModule.registerShovel(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed shovel>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            tier, typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
        ToolAPI.toolData[ItemID[id]] ??= { toolMaterial: ToolAPI.objectFromTier(tier, materialName), isWeapon: false, blockMaterials: ToolAPI.toolBlockTypes.shovel };
    }
    // @ts-ignore
    export function createHoeItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        let tier: vsdum.kex.modules.ToolsModule.ItemTier = ToolsModule.getTierByName(materialName);
        if(tier == null) {
            materialName = "wood";
            tier = ToolsModule.getTierByName(materialName);
        }
        ToolsModule.registerHoe(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed hoe>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            tier, typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
        ToolAPI.toolData[ItemID[id]] ??= { toolMaterial: ToolAPI.objectFromTier(tier, materialName), isWeapon: false, blockMaterials: ToolAPI.toolBlockTypes.hoe };
    }
    // @ts-ignore
    export function createShearsItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial, durability?: number }): void {
        let materialName: string = "";
        if(typeof params.tier !== "undefined") {
            if(typeof params.tier === "object") {
                materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
                ToolAPI.addToolMaterial(materialName, params.tier);
            } else materialName = params.tier;
        }
        const tierOrDurability = typeof params.tier !== "undefined" ? (ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("iron")) : typeof params.durability === "number" && params.durability > 0 ? params.durability : 238;
        if(ToolsModule.getTierByName(materialName) == null) materialName = "iron";
        ToolsModule.registerShears(
            ItemID[id], id,
            typeof name === "string" ? name: "<unnamed shears>",
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            tierOrDurability, typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
        Item.registerUseFunctionForID(ItemID[id], (coords, item, block, player) => ToolsModule.useCustomShearsOn(coords.x, coords.y, coords.z, coords.side, coords.relative.x, coords.relative.y, coords.relative.z, player));
        ToolAPI.toolData[ItemID[id]] ??= { toolMaterial: typeof tierOrDurability === "number" ? { durability: tierOrDurability, name: materialName } : ToolAPI.objectFromTier(tierOrDurability, materialName), isWeapon: false, blockMaterials: ToolAPI.toolBlockTypes.shears };
    }
    // @ts-ignore
    export function createFlintAndSteelItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, durability?: number }): void {
        params ??= {};
        params.stack ??= 1;
        params.durability ??= 64;
        ToolsModule.registerFlintAndSteel(
            ItemID[id], id,
            typeof name === "string" ? name: "<unnamed flint and steel>",
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            params.durability, typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
        Item.registerUseFunctionForID(ItemID[id], (coords, item, block, player) => ToolsModule.useCustomFlintAndSteelOn(coords.relative.x, coords.relative.y, coords.relative.z, coords.side, coords.relative.x, coords.relative.y, coords.relative.z, player));
    }
    // @ts-ignore
    export function createCustomTool(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }, toolParams?: ToolAPI.ExtendedToolParams, numericId?: number): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        let tier: vsdum.kex.modules.ToolsModule.ItemTier = ToolsModule.getTierByName(materialName);
        if(tier == null) {
            materialName = "wood";
            tier = ToolsModule.getTierByName(materialName);
        }
        let blockMaterialsArr: Nullable<string[]> = null;
        if(typeof toolParams === "object" && typeof toolParams.blockMaterials === "object") {
            blockMaterialsArr = [];
            for(let blockMaterial in toolParams.blockMaterials)
                toolParams.blockMaterials[blockMaterial] == true && blockMaterialsArr.push(blockMaterial);
        }
        numericId = typeof numericId !== "undefined" ? numericId : ItemID[id];
        ToolsModule.registerCustomTool(
            numericId, id,
            typeof name === "string" ? name : "<unnamed custom tool>",
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            tier, typeof params.isTech === "boolean" ? params.isTech : false,
            typeof toolParams === "object" && typeof toolParams.isWeapon === "boolean" ? toolParams.isWeapon : false,
            blockMaterialsArr,
            typeof toolParams === "object" && typeof toolParams.brokenId === "number" && toolParams.brokenId != 0 ? toolParams.brokenId : 0,
            typeof toolParams === "object" && typeof toolParams.damage === "number" && toolParams.damage > 0 ? toolParams.damage : 0,
            typeof toolParams.enchantType === "number" ? toolParams.enchantType : EEnchantType.ALL,
            typeof toolParams === "object" ? toolParams : {}
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
        if(typeof toolParams === "object" && typeof toolParams.getAttackDamageBonus === "function") ToolsModule.enableDynamicDamageFor(numericId);
        toolParams ??= {};
        toolParams.toolMaterial ??= ToolAPI.objectFromTier(tier, materialName);
        ToolAPI.toolData[ItemID[id]] ??= toolParams;
    }
}


namespace ToolAPI {
    export const toolBlockTypes = { sword: {}, axe: {}, pickaxe: {}, shovel: {}, hoe: {}, shears: {} };
    export function objectFromTier(tier: ItemTier, name: string): ToolMaterial {
        return {
            damage: tier.getAttackDamageBonus(),
            durability: tier.getUses(),
            efficiency: tier.getSpeed(),
            enchantability: tier.getEnchantmentValue(),
            level: tier.getLevel(), name
        }
    }
}


ToolAPI.unnamedMaterialNum = 0;
ToolAPI.ToolType = {
    sword: { __flag: "__sword" },
    axe: { __flag: "__axe" },
    pickaxe: { __flag: "__pickaxe" },
    shovel: { __flag: "__shovel" },
    hoe: { __flag: "__hoe" }
}
ToolAPI.addBlockMaterial = (name, breakingMultiplier) => ToolsModule.addBlockMaterial(name, breakingMultiplier);
ToolAPI.addToolMaterial = (name, material) => {
    if(ToolsModule.getTierByName(name) == null) {
        ToolAPI.toolMaterials[name] = ToolAPI.objectFromTier(new ToolsModule.ItemTier(name, 
            Math.floor(material.level) || 0, 
            Math.floor(material.durability) || 1, 
            Math.floor(material.efficiency) || 1, 
            Math.floor(material.damage) || 1, 
            Math.floor(material.enchantability) || 14
        ), name);
    } else Logger.Log(`Tool material with name \'${name}\' has already been registered before! Skipping...`, "KEX-WARNING");
}
ToolAPI.dropExpOrbs = (x, y, z, value, blockSource?: BlockSource) => (blockSource || BlockSource.getCurrentClientRegion()).spawnExpOrbs(x, y, z, value);
ToolAPI.getBlockData = blockID => {
    const material = ToolAPI.getBlockMaterial(blockID);
    const data = ToolsModule.getBlockData(blockID);
    return { material, level: data.destroyLevel, isNative: data.isNative };
}
ToolAPI.getBlockDestroyLevel = blockID => ToolsModule.getBlockDestroyLevel(blockID);
ToolAPI.getBlockMaterial = blockID => {
    const materialName = ToolsModule.getBlockMaterialName(blockID);
    return materialName == null ? null : { name: String(materialName), multiplier: ToolsModule.getBlockMaterialBreakingMultiplier(materialName) }
}
ToolAPI.getBlockMaterialName = blockID => String(ToolsModule.getBlockMaterialName(blockID));
ToolAPI.registerBlockDiggingLevel = (blockID, level) => ToolsModule.setBlockDestroyLevel(blockID, level);
ToolAPI.registerBlockMaterial = (blockID, materialName, level, isNative) => ToolsModule.setBlockData(blockID, materialName, level || 0, isNative || false);
ToolAPI.resetEngine = () => {}
ToolAPI.registerTool = (id, toolMaterial, blockMaterials, params) => {
    params ??= {};
    params.brokenId ??= 0;
    params.damage ??= 0;
    params.blockMaterials ??= {};
    if(Array.isArray(blockMaterials))
        blockMaterials.forEach(materialName => params.blockMaterials[materialName] = true);
    let materialName: string = "";
    if(typeof toolMaterial === "object") {
        if(typeof toolMaterial.name === "string") {
            if(ToolsModule.getTierByName(toolMaterial.name) == null)
                ToolAPI.addToolMaterial(toolMaterial.name, toolMaterial);
            materialName = toolMaterial.name;
        } else {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, toolMaterial);
        }
    } else if(typeof toolMaterial === "string") materialName = toolMaterial;
    let tier: vsdum.kex.modules.ToolsModule.ItemTier = ToolsModule.getTierByName(materialName);
    if(tier == null) {
        materialName = "wood";
        tier = ToolsModule.getTierByName(materialName);
    }
    params.toolMaterial = {
        level: tier.getLevel(),
        durability: tier.getUses(),
        efficiency: tier.getSpeed(),
        damage: tier.getAttackDamageBonus(),
        enchantability: tier.getEnchantmentValue(),
        name: materialName
    }
    params.calcDestroyTime ??= (to, c, b, ti, defaultTime) => defaultTime;
    ToolAPI.toolData[id] = params;
    const factory = ItemFactoryHelper.killItem(id);
    if(factory == null) throw new java.lang.IllegalStateException("You cannot call ToolAPI.registerTool before creating the item itself!");
    switch(params.__flag) {
        case "__sword": ToolsModule.registerSword(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
        case "__axe": ToolsModule.registerAxe(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
        case "__pickaxe": ToolsModule.registerPickaxe(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
        case "__shovel": ToolsModule.registerShovel(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
        case "__hoe": ToolsModule.registerHoe(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
        case "__shears": ToolsModule.registerShears(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
        default: Item.createCustomTool(String(factory.nameId), String(factory.nameToDisplay), { name: String(factory.iconName), meta: factory.iconIndex }, { stack: factory.stack, tier: materialName }, params, id);
    }
    factory.applyOldFactoryProperties(id);
}
ToolAPI.registerSword = (id, toolMaterial, params) => {
    params ??= {};
    params.isWeapon = true;
    params.damage ??= 4;
    let materialName: string = "";
    if(typeof toolMaterial === "object") {
        materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
        ToolAPI.addToolMaterial(materialName, toolMaterial);
    }
    const tier = ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("wood");
    const factory = ItemFactoryHelper.killItem(id);
    if(Object.keys(params).length - Number(typeof params.__flag !== "undefined") > 1) {
        Item.createCustomTool(String(factory.nameId), String(factory.nameToDisplay), { name: String(factory.iconName), meta: factory.iconIndex }, { stack: factory.stack, tier: materialName }, params);
    } else ToolsModule.registerSword(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier);
}
ToolAPI.startDestroyHook = () => {}
ToolAPI.destroyBlockHook = (c, b, i, p) => ToolsModule.destroyBlockHook(c, b, i, p);
ToolAPI.playerAttackHook = (a, v, i) => ToolsModule.playerAttackHook(a, v, i);
ToolAPI.getToolData = itemID => typeof ToolAPI.toolData[itemID] !== "undefined" ? ToolAPI.toolData[itemID] : null;
ToolAPI.getToolLevel = itemID => typeof ToolAPI.toolData[itemID] !== "undefined" && !ToolAPI.toolData[itemID].isWeapon ? ToolsModule.getToolLevel(itemID) : 0;
ToolAPI.getToolLevelViaBlock = (itemID, blockID) => typeof ToolAPI.toolData[itemID] !== "undefined" && !ToolAPI.toolData[itemID].isWeapon ? ToolsModule.getToolLevelViaBlock(itemID, blockID) : 0;
Block.setDestroyLevelForID = (blockID, level) => ToolAPI.registerBlockDiggingLevel(blockID, level);


(() => {

    type StandardTools = "sword" | "axe" | "pickaxe" | "shovel" | "hoe";
    interface JSONToolAPIData {
        materials: { [key: string]: (number | string)[] },
        destroy_levels: (number | string)[][],
        vanilla_tools: { [key: string]: { [key in StandardTools]: number } },
        tool_block_types: { [key: string]: string[] },
        tool_types_base_damage: { [key in StandardTools]: number };
    }

    for(let materialName in ToolAPI.blockMaterials)
        ToolAPI.addBlockMaterial(materialName, ToolAPI.blockMaterials[materialName].multiplier);
    for(let materialName in ToolAPI.toolMaterials)
        ToolAPI.addToolMaterial(materialName, ToolAPI.toolMaterials[materialName]);
    for(let id in ToolAPI.toolData) {
        const data = ToolAPI.toolData[id];
        delete ToolAPI.toolData[id];
        const numericId = Number(id);
        if(!IDRegistry.isVanilla(numericId))
            ToolAPI.registerTool(numericId, data.toolMaterial, null, data);
    }
    for(let id in ToolAPI.blockData) {
        const data = ToolAPI.blockData[id];
        delete ToolAPI.blockData[id];
        const numericId = Number(id);
        if(!IDRegistry.isVanilla(numericId))
            ToolAPI.registerBlockMaterial(numericId, data.material.name, data.level, typeof data.isNative === "boolean" ? data.isNative : false);
    }

    const json = FileTools.ReadJSON(`${__dir__}/data/toolapi_data.json`) as JSONToolAPIData;
    for(let materialName in json.materials)
        ToolAPI.registerBlockMaterialAsArray(materialName, json.materials[materialName].map(val => typeof val === "number" ? val : VanillaTileID[val]), true);
    json.destroy_levels.forEach((ids, level) => {
        ids.forEach(id => {
            const numericId = typeof id === "number" ? id : VanillaTileID[id];
            Block.setDestroyLevelForID(numericId, level + 1);
        });
    });
    for(let toolType in json.tool_block_types)
        json.tool_block_types[toolType].forEach(materialName => ToolAPI.toolBlockTypes[toolType][materialName] = true);
    for(let tier in json.vanilla_tools)
        for(let toolType in json.vanilla_tools[tier])
            ToolAPI.toolData[json.vanilla_tools[tier][toolType]] = {
                toolMaterial: ToolAPI.objectFromTier(ToolsModule.getTierByName(tier), tier),
                isWeapon: toolType === "sword",
                blockMaterials: ToolAPI.toolBlockTypes[toolType],
                damage: json.tool_types_base_damage[toolType],
                isNative: true, brokenId: 0,
                calcDestroyTime: (to, c, b, ti, defaultTime) => defaultTime
            }

})();