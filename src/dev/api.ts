/// <reference path="./modules/commands.ts" />


const LootModule = WRAP_JAVA("vsdum.kex.modules.LootModule");
const DamageModule = WRAP_JAVA("vsdum.kex.modules.DamageModule");
const ChunksModule = WRAP_JAVA("vsdum.kex.modules.ChunksModule");

const LootTableContext = WRAP_JAVA("vsdum.kex.natives.LootTableContext");
const MobEffect = WRAP_JAVA("vsdum.kex.natives.MobEffect");
const MobEffectInstance = WRAP_JAVA("vsdum.kex.natives.MobEffectInstance");
const Actor = WRAP_JAVA("vsdum.kex.natives.Actor");
const Mob = WRAP_JAVA("vsdum.kex.natives.Mob");
const KEXPlayer = WRAP_JAVA("vsdum.kex.natives.Player");
const LocalPlayer = WRAP_JAVA("vsdum.kex.natives.LocalPlayer");
const Slime = WRAP_JAVA("vsdum.kex.natives.Slime");
const FoodItemComponent = WRAP_JAVA("vsdum.kex.natives.FoodItemComponent");
const KEXBlockSource = WRAP_JAVA("vsdum.kex.natives.ExtendedBlockSource");
const ReachDistanceModifier = WRAP_JAVA("vsdum.kex.modules.misc.ReachDistanceModifier");
const CameraRollModifier = WRAP_JAVA("vsdum.kex.modules.misc.CameraRollModifier");

const GlobalContext = WRAP_JAVA("vsdum.kex.natives.GlobalContext");
const I18n = WRAP_JAVA("vsdum.kex.natives.I18n");

const TextureWorker = WRAP_JAVA("vsdum.kex.util.TextureWorker");
const ItemAnimHelper = WRAP_JAVA("vsdum.kex.util.ItemAnimHelper");

ModAPI.registerAPI("KernelExtension", {
    ItemsModule,
    LootModule,
    ToolsModule,
    DamageModule,
    CommandsModule,
    ChunksModule,

    LootTableContext,
    MobEffect,
    MobEffectInstance,
    Actor,
    Mob,
    Player: KEXPlayer,
    LocalPlayer,
    Slime,
    FoodItemComponent,
    BlockSource: KEXBlockSource,
    ReachDistanceModifier,
    CameraRollModifier,

    GlobalContext,
    I18n,

    AddonUtils,
    TextureWorker,
    ItemAnimHelper,

    ESaturationModifier,
    EDamageCause,

    getKEXVersion: () => MAIN.getVersion(),
    getKEXVersionCode: () => MAIN.getVersionCode()
});