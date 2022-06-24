const CommandsModule = WRAP_JAVA("vsdum.kex.modules.CommandsModule");
type CommandOverloadBase = vsdum.kex.modules.CommandsModule.CommandOverloadBase;
type CommandArgument = vsdum.kex.modules.CommandsModule.CommandArgument;
type CommandExecuteCallback = vsdum.kex.modules.CommandsModule.CommandExecuteCallback;


type CommandOverload = { args: Commands.Arguments[], callback: Commands.ExecuteCallback }
class KEXCommandBuilder implements Commands.CustomCommandBuilder<KEXCommandBuilder> {

    private readonly overloads: CommandOverload[] = [];

    constructor(private readonly name: string, private readonly permissionLevel: number) {}

    public addOverload(args: Commands.Arguments[], callback: Commands.ExecuteCallback): KEXCommandBuilder {
        this.overloads.push({ args, callback });
        return this;
    }

    public register(): void {
        const commandBase = CommandsModule.newCommand(this.name, this.permissionLevel);
        this.overloads.forEach(overload => {
            var node: CommandOverloadBase | CommandArgument = commandBase;
            overload.args.forEach((arg, index) => {
                if(arg.optional == true) {
                    node.executes(KEXCommandBuilder.buildExecuteCallback(overload, index));
                }
                const next = KEXCommandBuilder.buildArgument(arg);
                node.then(next);
                node = next;
            });
            node.executes(KEXCommandBuilder.buildExecuteCallback(overload, overload.args.length));
        });
        CommandsModule.registerCommand(commandBase);
    }

    private static buildArgument(arg: Commands.Arguments): CommandArgument {
        switch(arg.type) {
            case "int": case "integer":
                return typeof arg.default !== "number" ?
                    CommandsModule.intArg(arg.label) :
                    CommandsModule.intArg(arg.label, Math.floor(arg.default));
            case "float":
                return typeof arg.default !== "number" ?
                    CommandsModule.floatArg(arg.label) :
                    CommandsModule.floatArg(arg.label, arg.default);
            case "bool": case "boolean":
                return typeof arg.default !== "boolean" ?
                    CommandsModule.boolArg(arg.label) :
                    CommandsModule.boolArg(arg.label, arg.default);
            case "relfloat": case "relativefloat":
                return typeof arg.default !== "number" ?
                    CommandsModule.relativeFloatArg(arg.label) :
                    CommandsModule.relativeFloatArg(arg.label, arg.default);
            case "pos": case "position":
                return typeof arg.default !== "object" ?
                    CommandsModule.positionArg(arg.label) :
                    CommandsModule.positionArg(arg.label, arg.default.x ?? 0, arg.default.y ?? 0, arg.default.z ?? 0);
            case "floatpos": case "floatposition":
                return typeof arg.default !== "object" ?
                    CommandsModule.floatPositionArg(arg.label) :
                    CommandsModule.floatPositionArg(arg.label, arg.default.x ?? 0.0, arg.default.y ?? 0.0, arg.default.z ?? 0.0);
            case "str": case "string":
                return typeof arg.default !== "string" ?
                    CommandsModule.stringArg(arg.label) :
                    CommandsModule.stringArg(arg.label, arg.default);
            case "msg": case "message":
                return CommandsModule.messageArg(arg.label);
            case "json":
                return CommandsModule.jsonArg(arg.label);
            case "entity":
                return CommandsModule.entityArg(arg.label);
            case "player":
                return CommandsModule.playerArg(arg.label);
            case "enum":
                return typeof arg.default !== "number" ?
                    CommandsModule.enumArg(arg.label, arg.name) :
                    CommandsModule.enumArg(arg.label, arg.name, Math.floor(arg.default));
            case "strenum": case "stringenum":
                return CommandsModule.stringEnumArg(arg.label, arg.name, arg.default);
            case "literal":
                return CommandsModule.literal(arg.label);
        }
    }

    private static buildExecuteCallback(overload: CommandOverload, paramsCount: number): CommandExecuteCallback {
        return ctx => {
            const obj = {};
            for(let i = 0; i < paramsCount; i++) {
                const arg = overload.args[i];
                switch(arg.type) {
                    case "int": case "integer": case "enum":
                        obj[arg.label] = ctx.getInt(arg.label); break;
                    case "float":
                        obj[arg.label] = ctx.getFloat(arg.label); break;
                    case "bool": case "boolean":
                        obj[arg.label] = ctx.getBool(arg.label); break;
                    case "pos": case "position":
                        obj[arg.label] = ctx.getPosition(arg.label); break;
                    case "floatpos": case "floatposition":
                        obj[arg.label] = ctx.getFloatPosition(arg.label); break;
                    case "str": case "string": case "strenum": case "stringenum":
                        obj[arg.label] = ctx.getString(arg.label); break;
                    case "msg": case "message":
                        obj[arg.label] = ctx.getMessage(arg.label); break;
                    case "json":
                        obj[arg.label] = ctx.getJson(arg.label); break;
                    case "entity":
                        const entitiesArr = [];
                        const entitiesIter = ctx.getEntities(arg.label).iterator();
                        while(entitiesIter.hasNext()) entitiesArr.push(entitiesIter.next());
                        obj[arg.label] = entitiesArr; break;
                    case "player":
                        const playersArr = [];
                        const playersIter = ctx.getPlayers(arg.label).iterator();
                        while(playersIter.hasNext()) playersArr.push(playersIter.next());
                        obj[arg.label] = playersArr; break;
                }
            }
            overload.callback(obj, ctx);
        }
    }

}


Commands.newEnum = enumName => CommandsModule.newEnum(enumName);
Commands.newStringEnum = enumName => CommandsModule.newStringEnum(enumName);
Commands.create = (commandName: string, permissionLevel: number = 0) => new KEXCommandBuilder(commandName, permissionLevel);