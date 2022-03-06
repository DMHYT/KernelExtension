const LootModule = WRAP_JAVA("vsdum.kex.modules.LootModule");

const MobEffect = WRAP_JAVA("vsdum.kex.natives.MobEffect");
const MobEffectInstance = WRAP_JAVA("vsdum.kex.natives.MobEffectInstance");
const Actor = WRAP_JAVA("vsdum.kex.natives.Actor");
const Mob = WRAP_JAVA("vsdum.kex.natives.Mob");
const Slime = WRAP_JAVA("vsdum.kex.natives.Slime");

const MAIN = WRAP_JAVA("vsdum.kex.KernelExtension");

ModAPI.registerAPI("KernelExtension", {
    ItemsModule,
    LootModule,
    ToolsModule,

    MobEffect,
    MobEffectInstance,
    Actor,
    Mob,
    Slime,

    AddonUtils,

    getKEXVersion: () => MAIN.getVersion(),
    getKEXVersionCode: () => MAIN.getVersionCode()
});