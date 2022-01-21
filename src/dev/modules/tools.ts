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
        enchantability?: number;
    }
    export function startDestroyHook(coords: Callback.ItemUseCoordinates, block: Tile, carried: ItemInstance): void;
    export function destroyBlockHook(coords: Callback.ItemUseCoordinates, block: Tile, item: ItemInstance, player: number): void;
    export function playerAttackHook(attacker: number, victim: number, item: ItemInstance): void;
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
    export function createSwordItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        ToolsModule.registerSword(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed sword>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("wood"),
            typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
    }
    export function createAxeItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        ToolsModule.registerAxe(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed axe>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("wood"),
            typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
    }
    export function createPickaxeItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        ToolsModule.registerPickaxe(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed pickaxe>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("wood"),
            typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
    }
    export function createShovelItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        ToolsModule.registerShovel(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed shovel>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("wood"),
            typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
    }
    export function createHoeItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
        ToolsModule.registerHoe(
            ItemID[id], id, 
            typeof name === "string" ? name : "<unnamed hoe>", 
            typeof texture.name === "string" ? texture.name : "missing_item",
            typeof texture.meta === "number" && texture.meta > 0 ? texture.meta : typeof texture.data === "number" && texture.data > 0 ? texture.data : 0,
            ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("wood"),
            typeof params.isTech === "boolean" ? params.isTech : false
        );
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
    }
    export function createCustomTool(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }, toolParams?: ToolAPI.ToolParams, numericId?: number): void {
        let materialName: string = "";
        if(typeof params.tier === "object") {
            materialName = `__unnamedToolMaterial${ToolAPI.unnamedMaterialNum++}`;
            ToolAPI.addToolMaterial(materialName, params.tier);
        } else materialName = params.tier;
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
            ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("wood"),
            typeof params.isTech === "boolean" ? params.isTech : false,
            typeof toolParams === "object" && typeof toolParams.isWeapon === "boolean" ? toolParams.isWeapon : false,
            blockMaterialsArr,
            typeof toolParams === "object" && typeof toolParams.brokenId === "number" && toolParams.brokenId != 0 ? toolParams.brokenId : 0,
            typeof toolParams === "object" && typeof toolParams.damage === "number" && toolParams.damage > 0 ? toolParams.damage : 0,
            typeof toolParams.enchantType === "number" ? toolParams.enchantType : EEnchantType.ALL
        );
        if(typeof toolParams === "object") {
            typeof toolParams.calcDestroyTime === "function" && ToolsModule.addCalcDestroyTimeCallback(numericId, toolParams.calcDestroyTime);
            typeof toolParams.modifyEnchant === "function" && ToolsModule.addModifyEnchantCallback(numericId, toolParams.modifyEnchant);
            typeof toolParams.onAttack === "function" && ToolsModule.addOnAttackCallback(numericId, toolParams.onAttack);
            typeof toolParams.onBroke === "function" && ToolsModule.addOnBrokeCallback(numericId, toolParams.onBroke);
            typeof toolParams.onDestroy === "function" && ToolsModule.addOnDestroyCallback(numericId, toolParams.onDestroy);
            typeof toolParams.onMineBlock === "function" && ToolsModule.addOnMineBlockCallback(numericId, toolParams.onMineBlock);
            ToolAPI.toolData[numericId] = toolParams;
        }
        if(typeof params.stack === "number" && params.stack > 1) Item.getItemById(id).setMaxStackSize(params.stack);
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
    if(ToolsModule.getTierByName(name) == null || name !== "golden") {
        const tier = new ToolsModule.ItemTier(name,
            material.level || 0, 
            material.durability || 1, 
            material.efficiency || 1, 
            material.damage || 0, 
            material.enchantability || 14);
        ToolAPI.toolMaterials[name] = { level: tier.getLevel(), durability: tier.getUses(), efficiency: tier.getSpeed(), damage: tier.getAttackDamageBonus(), enchantability: tier.getEnchantmentValue() }
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
    return materialName == null ? null : { name: materialName, multiplier: ToolsModule.getBlockMaterialBreakingMultiplier(materialName) }
}
ToolAPI.getBlockMaterialName = blockID => ToolsModule.getBlockMaterialName(blockID);
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
    const tier = ToolsModule.getTierByName(materialName) ?? ToolsModule.getTierByName("wood");
    if(typeof params !== "undefined") {
        const factory = ItemFactoryHelper.killItem(id);
        if(factory == null) throw new java.lang.IllegalStateException("You cannot call ToolAPI.registerTool before creating the item itself!");
        switch(params.__flag) {
            case "__sword": ToolsModule.registerSword(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
            case "__axe": ToolsModule.registerAxe(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
            case "__pickaxe": ToolsModule.registerPickaxe(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
            case "__shovel": ToolsModule.registerShovel(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
            case "__hoe": ToolsModule.registerHoe(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier); break;
            default:
                if(typeof params.blockMaterials === "undefined" && Array.isArray(blockMaterials)) {
                    params.blockMaterials = {};
                    blockMaterials.forEach(material => params.blockMaterials[material] = true);
                }
                Item.createCustomTool(factory.nameId, factory.nameToDisplay, { name: factory.iconName, meta: factory.iconIndex }, { stack: factory.stack, tier: materialName }, params, id);
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
        Item.createCustomTool(factory.nameId, factory.nameToDisplay, { name: factory.iconName, meta: factory.iconIndex }, { stack: factory.stack, tier: materialName }, params);
    } else ToolsModule.registerSword(id, factory.nameId, factory.nameToDisplay, factory.iconName, factory.iconIndex, tier);
}
ToolAPI.startDestroyHook = () => {}
ToolAPI.destroyBlockHook = () => {}
ToolAPI.playerAttackHook = () => {}
ToolAPI.getToolData = itemID => typeof ToolAPI.toolData[itemID] !== "undefined" ? ToolAPI.toolData[itemID] : null;
ToolAPI.getToolLevel = itemID => ToolsModule.getToolLevel(itemID);
ToolAPI.getToolLevelViaBlock = (itemID, blockID) => ToolsModule.getToolLevelViaBlock(itemID, blockID);
ToolAPI.getDestroyTimeViaTool = (fullBlock, toolItem, coords) => ToolsModule.getDestroyTimeViaTool(fullBlock, coords.x, coords.y, coords.z, coords.side, toolItem);
Block.isNativeTile = blockID => ToolsModule.getBlockIsNative(blockID);
Block.setDestroyLevelForID = (blockID, level) => ToolAPI.registerBlockDiggingLevel(blockID, level);


(() => {
    for(let k in ToolAPI.blockMaterials) ToolAPI.addBlockMaterial(k, ToolAPI.blockMaterials[k].multiplier);
    ToolAPI.blockMaterials = null;
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
    interface JSONToolAPIData {
        materials: { [key: string]: (number | string)[] },
        destroy_levels: (number | string)[][];
    }
    const json = FileTools.ReadJSON(`${__dir__}/data/toolapi_data.json`) as JSONToolAPIData;
    for(let materialName in json.materials) ToolAPI.registerBlockMaterialAsArray(materialName, json.materials[materialName].map(val => typeof val === "number" ? val : VanillaTileID[val]), true);
    json.destroy_levels.forEach((el, level) => el.forEach(id => {
        id = typeof id === "number" ? id : VanillaTileID[id];
        typeof Block.dropFunctions[id] !== "undefined" && delete Block.dropFunctions[id];
        Block.setDestroyLevelForID(id as number, level + 1);
    }));
})();


Callback.addCallback("ItemUse", (c, i, b, e, p) => Debug.m(`${Item.getMaxDamage(i.id)}`));