const LootModule = WRAP_JAVA("vsdum.kex.modules.LootModule");

const LootTableContext = WRAP_JAVA("vsdum.kex.natives.LootTableContext");
const MobEffect = WRAP_JAVA("vsdum.kex.natives.MobEffect");
const MobEffectInstance = WRAP_JAVA("vsdum.kex.natives.MobEffectInstance");
const Actor = WRAP_JAVA("vsdum.kex.natives.Actor");
const Mob = WRAP_JAVA("vsdum.kex.natives.Mob");
const KEXPlayer = WRAP_JAVA("vsdum.kex.natives.Player");
const LocalPlayer = WRAP_JAVA("vsdum.kex.natives.LocalPlayer");
const Slime = WRAP_JAVA("vsdum.kex.natives.Slime");
const FoodItemComponent = WRAP_JAVA("vsdum.kex.natives.FoodItemComponent");
const ReachDistanceModifier = WRAP_JAVA("vsdum.kex.modules.misc.ReachDistanceModifier");
const CameraRollModifier = WRAP_JAVA("vsdum.kex.modules.misc.CameraRollModifier");

const GlobalContext = WRAP_JAVA("vsdum.kex.natives.GlobalContext");
const I18n = WRAP_JAVA("vsdum.kex.natives.I18n");

// ItemsModule.setDynamicFoodValues(VanillaItemID.sweet_berries, (stack) => {
//     return new FoodItemComponent.Builder()
//         .nutrition(Math.floor(Math.random() * 3) + 1)
//         .saturationMod(ESaturationModifier.NORMAL)
//         .alwaysEat();
// });




const testRollMod = new CameraRollModifier().enable();
let roll: number = 0.0;

Callback.on("LocalTick", () => {
    roll += Math.PI / 30.0;
    testRollMod.setModifier(roll);
});




ModAPI.registerAPI("KernelExtension", {
    ItemsModule,
    LootModule,
    ToolsModule,

    LootTableContext,
    MobEffect,
    MobEffectInstance,
    Actor,
    Mob,
    Player: KEXPlayer,
    LocalPlayer,
    Slime,
    FoodItemComponent,
    ReachDistanceModifier,
    CameraRollModifier,

    GlobalContext,
    I18n,

    AddonUtils,

    ESaturationModifier,
    EDamageCause,

    getKEXVersion: () => MAIN.getVersion(),
    getKEXVersionCode: () => MAIN.getVersionCode()
});