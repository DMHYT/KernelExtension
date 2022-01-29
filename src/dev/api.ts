const LootModule = WRAP_JAVA("vsdum.kex.modules.LootModule");

const Actor = WRAP_JAVA("vsdum.kex.natives.Actor");
const Mob = WRAP_JAVA("vsdum.kex.natives.Mob");
const Slime = WRAP_JAVA("vsdum.kex.natives.Slime");


ModAPI.registerAPI("KernelExtension", {
    ItemsModule,
    LootModule,
    ToolsModule,

    Actor,
    Mob,
    Slime
});