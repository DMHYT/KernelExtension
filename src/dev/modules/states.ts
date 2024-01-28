type IntegerProperty = vsdum.kex.modules.states.properties.IntegerProperty;
type BooleanProperty = vsdum.kex.modules.states.properties.BooleanProperty;
const IntegerProperty = WRAP_JAVA("vsdum.kex.modules.states.properties.IntegerProperty");
const BooleanProperty = WRAP_JAVA("vsdum.kex.modules.states.properties.BooleanProperty");
const KEXBlockState = WRAP_JAVA("vsdum.kex.modules.states.BlockState");
const VanillaStates = WRAP_JAVA("vsdum.kex.modules.states.VanillaStates");


namespace BlockStates {

    export const createIntegerProperty: typeof IntegerProperty.create = (name, min, max) => IntegerProperty.create(name, min, max);
    export const createBooleanProperty: typeof BooleanProperty.create = name => BooleanProperty.create(name);
    
    export enum AnvilDamage {
        UNDAMAGED = 0,
        SLIGHTLY_DAMAGED = 1,
        VERY_DAMAGED = 2,
        BROKEN = 3
    }

    export enum BambooLeaves {
        NONE = 0,
        SMALL = 1,
        LARGE = 2
    }

    export enum BellAttachment {
        FLOOR = 0,
        CEILING = 1,
        SINGLE_WALL = 2,
        DOUBLE_WALL = 3
    }

    export enum BlockColor {
        WHITE = 0,
        ORANGE = 1,
        MAGENTA = 2,
        LIGHT_BLUE = 3,
        YELLOW = 4,
        LIME = 5,
        PINK = 6,
        GRAY = 7,
        SILVER = 8,
        CYAN = 9,
        PURPLE = 10,
        BLUE = 11,
        BROWN = 12,
        GREEN = 13,
        RED = 14,
        BLACK = 15
    }

    export enum CoralColor {
        BLUE = 0,
        PINK = 1,
        PURPLE = 2,
        RED = 3,
        YELLOW = 4
    }

    export enum HatchLevel {
        NO_CRACKS = 0,
        CRACKED = 1,
        MAX_CRACKED = 2
    }

    export enum LeverDirection {
        DOWN_EAST_WEST = 0,
        EAST = 1,
        WEST = 2,
        SOUTH = 3,
        NORTH = 4,
        UP_NORTH_SOUTH = 5,
        UP_EAST_WEST = 6,
        DOWN_NORTH_SOUTH = 7
    }

    export enum PillarAxis {
        Y = 0, X = 1, Z = 2
    }
    
    export enum PortalAxis {
        UNKNOWN = 0, X = 1, Z = 2
    }

    export enum RailShape {
        NORTH_SOUTH = 0,
        EAST_WEST = 1,
        ASCENDING_EAST = 2,
        ASCENDING_WEST = 3,
        ASCENDING_NORTH = 4,
        ASCENDING_SOUTH = 5,
        SOUTH_EAST = 6,
        SOUTH_WEST = 7,
        NORTH_WEST = 8,
        NORTH_EAST = 9
    }

    export enum StalkThickness {
        THIN = 0, THICK = 1
    }

    export enum StructureBlockType {
        DATA = 0,
        SAVE = 1,
        LOAD = 2,
        CORNER = 3,
        INVALID = 4,
        EXPORT = 5
    }

    export enum StructureVoidType {
        VOID = 0, AIR = 1
    }

    export enum TorchFacing {
        UNKNOWN = 0,
        WEST = 1,
        EAST = 2,
        NORTH = 3,
        SOUTH = 4,
        TOP = 5
    }

    export enum WallConnectionType {
        NONE = 0,
        SHORT = 1,
        TALL = 2
    }

}