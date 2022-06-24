interface KEXJSTestParams {
    choice: number,
    strchoice: string,
    caller?: vsdum.kex.natives.Player[];
}


Commands.newEnum("Horizoners")
    .add("zheka", 0)
    .add("anton", 1)
    .add("onton", 1)
    .add("zhaba", 1)
    .add("vasya", 2)
    .add("ilya", 3)
    .add("belyash", 4)
    .register();

Commands.newStringEnum("HorizonersS")
    .add("zheka").add("onton").add("zhaba").add("vasya").add("ilya").add("belyash")
    .register();

Commands.create("kexjstest")
    .addOverload([
        { type: "literal", label: "choose" },
        { type: "enum", label: "choice", name: "Horizoners" },
        { type: "stringenum", label: "strchoice", name: "HorizonersS", default: "zheka" },
        { type: "player", label: "caller", optional: true }
    ], (args: KEXJSTestParams, ctx) => {
        ctx.success(`Called kexjstest, horizoner ID is ${args.choice}, name is ${args.strchoice}`);
        var playerUID: number = 0;
        if(typeof args.caller !== "undefined" && args.caller.length > 0) {
            playerUID = args.caller[0].getUniqueID();
        } else {
            const srcPlayer = ctx.getSourcePlayer();
            if(srcPlayer != null) playerUID = srcPlayer.getUniqueID();
        }
        if(playerUID == 0) ctx.success("This command was not called by a player");
        else ctx.success(`This command has been called by ${Entity.getNameTag(playerUID)}`);
    })
    .register();