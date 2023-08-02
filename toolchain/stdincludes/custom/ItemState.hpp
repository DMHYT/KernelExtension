#ifndef KEX_ITEMSTATE_HPP
#define KEX_ITEMSTATE_HPP


class ItemState {
    public:
    void** vtable; // 4
    unsigned int id; // 8
    char filler[56]; // 64
};

class VanillaStates {
    public:
    static ItemState AgeBit;
    static ItemState Age;
    static ItemState AttachedBit;
    static ItemState PortalAxis;
    static ItemState BiteCounter;
    static ItemState BrewingStandSlotABit;
    static ItemState BrewingStandSlotBBit;
    static ItemState BrewingStandSlotCBit;
    static ItemState ButtonPressedBit;
    static ItemState ConditionalBit;
    static ItemState CoveredBit;
    static ItemState Damage;
    static ItemState DisarmedBit;
    static ItemState DoorHingeBit;
    static ItemState UpperBlockBit;
    static ItemState Direction;
    static ItemState EndPortalEyeBit;
    static ItemState ExplodeBit;
    static ItemState FacingDirection;
    static ItemState FillLevel;
    static ItemState Growth;
    static ItemState HeadPieceBit;
    static ItemState Height;
    static ItemState InfiniburnBit;
    static ItemState InWallBit;
    static ItemState LiquidDepth;
    static ItemState MoisturizedAmount;
    static ItemState NoDropBit;
    static ItemState KelpAge;
    static ItemState OccupiedBit;
    static ItemState OpenBit;
    static ItemState OutputSubtractBit;
    static ItemState OutputLitBit;
    static ItemState PersistentBit;
    static ItemState PoweredBit;
    static ItemState RailDataBit;
    static ItemState RailDirection;
    static ItemState RedstoneSignal;
    static ItemState RepeaterDelay;
    static ItemState SuspendedBit;
    static ItemState ToggleBit;
    static ItemState TopSlotBit;
    static ItemState TriggeredBit;
    static ItemState UpdateBit;
    static ItemState UpsideDownBit;
    static ItemState VineDirectionBits;
    static ItemState AllowUnderwaterBit;
    static ItemState ColorBit;
    static ItemState DeadBit;
    static ItemState ClusterCount;
    static ItemState ItemFrameMapBit;
    static ItemState SaplingType;
    static ItemState TorchFacingDirection;
    static ItemState DragDown;
    static ItemState TurtleEggCount;
    static ItemState CrackedState;
    static ItemState StandingRotation; // "ground_sign_direction"
    static ItemState WeirdoDirection;
    static ItemState CoralDirection;
    static ItemState Color;
    static ItemState BambooThickness; // "bamboo_stalk_thickness"
    static ItemState BambooLeafSize;
    static ItemState Stability;
    static ItemState StabilityCheckBit; // "stability_check"
    static ItemState WoodType;
    static ItemState StoneType;
    static ItemState DirtType;
    static ItemState SandType;
    static ItemState OldLogType;
    static ItemState NewLogType;
    static ItemState ChiselType;
    static ItemState DEPRECATED;
    static ItemState OldLeafType;
    static ItemState NewLeafType;
    static ItemState SpongeType;
    static ItemState SandStoneType;
    static ItemState TallGrassType;
    static ItemState FlowerType;
    static ItemState StoneSlabType;
    static ItemState StoneSlabType2;
    static ItemState StoneSlabType3;
    static ItemState StoneSlabType4;
    static ItemState MonsterEggStoneType;
    static ItemState StoneBrickType;
    static ItemState HugeMushroomBits;
    static ItemState WallBlockType;
    static ItemState PrismarineBlockType;
    static ItemState DoublePlantType;
    static ItemState ChemistryTableType;
    static ItemState SeaGrassType;
    static ItemState CoralColor;
    static ItemState CauldronLiquid;
    static ItemState HangingBit; // "hanging"
    static ItemState StrippedBit;
    static ItemState CoralHangTypeBit;
    static ItemState Attachment;
    static ItemState StructureVoidType;
    static ItemState StructureBlockType;
    static ItemState Extinguished;
    static ItemState ComposterFillLevel;
    static ItemState CoralFanDirection;
    static ItemState LeverDirection;
    static ItemState PillarAxis;
    static ItemState BlockLightLevel;
    static ItemState BeehiveHoneyLevel; // "honey_level"
    static ItemState WeepingVinesAge;
    static ItemState WallPostBit;
    static ItemState WallConnectionTypeNorth;
    static ItemState WallConnectionTypeEast;
    static ItemState WallConnectionTypeSouth;
    static ItemState WallConnectionTypeWest;
    static ItemState Rotation;
    static ItemState TwistingVinesAge;
    static ItemState RespawnAnchorCharge;
};


#endif //KEX_ITEMSTATE_HPP