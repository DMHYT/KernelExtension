const ItemFactoryHelper = WRAP_JAVA("vsdum.kex.util.ItemFactoryHelper");
const ToolsModule = WRAP_JAVA("vsdum.kex.modules.ToolsModule");
type ItemTier = vsdum.kex.modules.ToolsModule.ItemTier;


declare namespace ToolAPI {
    export var blockMaterials: any;
    export var toolMaterials: { [materialName: string]: ToolMaterial };
    export var toolData: { [numericId: number]: ToolParams };
    export var blockData: { [numericId: number]: { material: string, level: number, isNative: boolean } };
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
            Object.keys(toolParams.blockMaterials).forEach(k => toolParams.blockMaterials[k] && blockMaterialsArr.push(k));
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
    export function objectFromTier(tier: ItemTier, name: string): ToolAPI.ToolMaterial {
        return {
            damage: tier.getAttackDamageBonus(),
            durability: tier.getUses(),
            efficiency: tier.getSpeed(),
            enchantability: tier.getEnchantmentValue(),
            level: tier.getLevel(), name
        }
    }
}

ToolAPI.blockData = {};
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
        const tier = new ToolsModule.ItemTier(name,
            material.level || 0, 
            material.durability || 1, 
            material.efficiency || 1, 
            material.damage || 0, 
            material.enchantability || 14);
        ToolAPI.toolMaterials[name] = material;
        ToolAPI.toolMaterials[name].level = tier.getLevel();
        ToolAPI.toolMaterials[name].durability = tier.getUses();
        ToolAPI.toolMaterials[name].efficiency = tier.getSpeed();
        ToolAPI.toolMaterials[name].damage = tier.getAttackDamageBonus();
        ToolAPI.toolMaterials[name].enchantability = tier.getEnchantmentValue();
        ToolAPI.toolMaterials[name].name = name;
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
ToolAPI.registerBlockDiggingLevel = (blockID, level) => {
    ToolsModule.setBlockDestroyLevel(blockID, level);
}
ToolAPI.registerBlockMaterial = (blockID, materialName, level, isNative) => {
    ToolsModule.setBlockData(blockID, materialName, level || 0, isNative || false);
}
ToolAPI.resetEngine = () => {}
ToolAPI.registerTool = (id, toolMaterial, blockMaterials, params) => {
    let materialName: string = "";
    if(typeof toolMaterial === "object") {
        materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
        ToolAPI.addToolMaterial(materialName, toolMaterial);
    }
    let tier: vsdum.kex.modules.ToolsModule.ItemTier = ToolsModule.getTierByName(materialName);
    if(tier == null) {
        materialName = "wood";
        tier = ToolsModule.getTierByName(materialName);
    }
    if(typeof params !== "undefined") {
        if(typeof params.toolMaterial === "undefined") {
            params.toolMaterial = {
                level: tier.getLevel(),
                durability: tier.getUses(),
                efficiency: tier.getSpeed(),
                damage: tier.getAttackDamageBonus(),
                enchantability: tier.getEnchantmentValue(),
                name: materialName
            }
        }
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
            default:
                if(typeof params.blockMaterials === "undefined" && Array.isArray(blockMaterials)) {
                    params.blockMaterials = {};
                    blockMaterials.forEach(material => params.blockMaterials[material] = true);
                }
                Item.createCustomTool(factory.nameId, factory.nameToDisplay, { name: String(factory.iconName), meta: factory.iconIndex }, { stack: factory.stack, tier: materialName }, params, id);
        }
        factory.applyOldFactoryProperties(id);
    }
}
ToolAPI.registerSword = (id, toolMaterial, params) => {
    let materialName: string = "";
    if(typeof toolMaterial === "object") {
        materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
        ToolAPI.addToolMaterial(materialName, toolMaterial);
    }
    const tier = ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("wood");
    const factory = ItemFactoryHelper.killItem(id);
    if(typeof params === "object" && Object.keys(params).length - Number(typeof params.__flag !== "undefined") > 0) {
        Item.createCustomTool(factory.nameId, factory.nameToDisplay, { name: String(factory.iconName), meta: factory.iconIndex }, { stack: factory.stack, tier: materialName }, params);
    } else ToolsModule.registerSword(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier);
}
ToolAPI.startDestroyHook = () => {}
ToolAPI.destroyBlockHook = (c, b, i, p) => ToolsModule.destroyBlockHook(c, b, i, p);
ToolAPI.playerAttackHook = (a, v, i) => ToolsModule.playerAttackHook(a, v, i);
ToolAPI.getToolData = itemID => typeof ToolAPI.toolData[itemID] !== "undefined" ? ToolAPI.toolData[itemID] : null;
ToolAPI.getToolLevel = itemID => typeof ToolAPI.toolData[itemID] !== "undefined" && !ToolAPI.toolData[itemID].isWeapon ? ToolsModule.getToolLevel(itemID) : 0;
ToolAPI.getToolLevelViaBlock = (itemID, blockID) => typeof ToolAPI.toolData[itemID] !== "undefined" && !ToolAPI.toolData[itemID].isWeapon ? ToolsModule.getToolLevelViaBlock(itemID, blockID) : 0;
ToolAPI.getDestroyTimeViaTool = (fullBlock, toolItem, coords) => typeof ToolAPI.toolData[toolItem.id] !== "undefined" && !ToolAPI.toolData[toolItem.id].isWeapon ? ToolsModule.getDestroyTimeViaTool(fullBlock, coords.x, coords.y, coords.z, coords.side, toolItem.id, toolItem.count, toolItem.data, toolItem.extra ?? null) : Block.getDestroyTime(fullBlock.id);
Block.setDestroyLevelForID = (blockID, level) => ToolAPI.registerBlockDiggingLevel(blockID, level);


(() => {
    for(let k in ToolAPI.blockMaterials) ToolAPI.addBlockMaterial(k, ToolAPI.blockMaterials[k].multiplier);
    const materialsToDelete = [ "wood", "stone", "iron", "diamond", "golden", "netherite" ];
    for(let materialName in ToolAPI.toolMaterials) {
        const copy = { ...ToolAPI.toolMaterials[materialName] };
        if(!!~materialsToDelete.indexOf(materialName)) delete ToolAPI.toolMaterials[materialName];
        else ToolAPI.addToolMaterial(materialName, copy);
    }
    for(let id in ToolAPI.toolData) {
        const copy = { ...ToolAPI.toolData[id] };
        delete ToolAPI.toolData[id];
        const numericId = parseInt(id);
        if(!IDRegistry.isVanilla(numericId)) {
            ToolAPI.registerTool(numericId, copy.toolMaterial, [], copy);
        }
    }
    for(let id in ToolAPI.blockData) {
        const numericId = parseInt(id);
        ToolAPI.registerBlockMaterial(numericId, ToolAPI.blockData[id].material, ToolAPI.blockData[id].level, typeof ToolAPI.blockData[id].isNative === "boolean" ? ToolAPI.blockData[id].isNative : false);
    }
    ToolAPI.blockData = {};
    type StandardTools = "sword" | "axe" | "pickaxe" | "shovel" | "hoe";
    interface JSONToolAPIData {
        materials: { [key: string]: (number | string)[] },
        destroy_levels: (number | string)[][],
        vanilla_tools: { [key: string]: { [key in StandardTools]: number } },
        tool_block_types: { [key in (StandardTools | "shears")]: string[] };
    }
    const json = FileTools.ReadJSON(`${__dir__}/data/toolapi_data.json`) as JSONToolAPIData;
    for(let materialName in json.materials) ToolAPI.registerBlockMaterialAsArray(materialName, json.materials[materialName].map(val => typeof val === "number" ? val : VanillaTileID[val]), true);
    json.destroy_levels.forEach((el, level) => el.forEach(id => {
        id = typeof id === "number" ? id : VanillaTileID[id];
        typeof Block.dropFunctions[id] !== "undefined" && delete Block.dropFunctions[id];
        Block.setDestroyLevelForID(id as number, level + 1);
    }));
    Object.keys(json.tool_block_types).forEach((toolType: StandardTools | "shears") => json.tool_block_types[toolType].forEach(material => ToolAPI.toolBlockTypes[toolType][material] = true));
    Object.keys(json.vanilla_tools).forEach(tier => {
        const tierObj = ToolAPI.objectFromTier(ToolsModule.getTierByName(tier), tier);
        Object.keys(json.vanilla_tools[tier]).forEach(toolType => ToolAPI.toolData[json.vanilla_tools[tier][toolType]] = { toolMaterial: tierObj, isWeapon: toolType === "sword", blockMaterials: ToolAPI.toolBlockTypes[toolType] });
    });
})();