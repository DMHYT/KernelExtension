#ifndef KEX_ENUMS_HPP
#define KEX_ENUMS_HPP


enum ActorCategory: int {};
enum ActorDamageCause: int {};
enum ActorEvent: int {};
enum ActorFlags: int {};
enum ActorType: int {};
enum AttributeBuffType: int {};
enum ArmorSlot: int {};
enum ArmorTextureType: int {};
enum BlockActorType {
    SIGN = 4
};
enum EquipmentSlot: int {};
enum HandSlot { MAINHAND, OFFHAND };
enum ItemUseMethod: int {};
enum MaterialType: int {};
enum PaletteColor: int {};
enum EquipmentFilter: int {};
enum CreativeItemCategory: int {};
enum ItemAcquisitionMethod: int {};
enum UseAnimation : int {};
enum ActorTarget: int {};
enum MobSpawnMethod: int {};
enum TravelType: int {};
enum AbilitiesIndex: int {};
enum BuildPlatform: int {};
enum ContainerID: int {};
enum ContainerType: int {};
enum GameType {
    SURVIVAL,
    CREATIVE,
    ADVENTURE,
    SPECTATOR
};
enum InputMode: int {};
enum LevelSoundEvent: int {};
enum MovementEventType: int {};
enum PlayerUISlot: int {};
enum Side: int {};
enum Mirror: unsigned char { MIRROR_NONE = 0, X, Z, XZ };
enum CommandParameterDataType {
    NORMAL,
    ENUM,
    SOFT_ENUM,
    POSTFIX
};
enum CommandParameterOption: unsigned char {
    CPOPTION_NONE = 0,
    ENUM_AUTOCOMPLETE_EXPANSION = 1,
    HAS_SEMANTIC_CONSTRAINT = 2,
    ENUM_AS_CHAINED_COMMAND = 4
};
enum CommandFlag {
    CFLAG_NONE = 0,
    USAGE = 1,
    VISIBILITY2 = 2,
    VISIBILITY4 = 4,
    VISIBILITY6 = 6,
    SYNC = 8,
    EXECUTE = 16,
    TYPE = 32,
    CHEAT = 64
};
enum CommandPermissionLevel {
    ANY = 0,
    GAMEMASTERS = 1,
    ADMIN = 2,
    HOST = 3,
    OWNER = 4,
    INTERNAL = 5
};
enum Difficulty: int {};
enum CommandOutputType: int {};
enum CommandSelectionType: unsigned int {};
enum CommandOperator {};


#endif //KEX_ENUMS_HPP