#include <cstdlib>
#include <jni.h>

#include <static_symbol.h>

#include <innercore/block_registry.h>
#include <innercore/id_conversion_map.h>

#include <commontypes.hpp>

#include <Block.hpp>
#include <BlockLegacy.hpp>

#include "../module.hpp"
#include "states.hpp"


std::vector<ItemState*> KEXBlockStatesModule::vanillaStates {
    &VanillaStates::AgeBit,
    &VanillaStates::Age,
    &VanillaStates::AttachedBit,
    &VanillaStates::PortalAxis,
    &VanillaStates::BiteCounter,
    &VanillaStates::BrewingStandSlotABit,
    &VanillaStates::BrewingStandSlotBBit,
    &VanillaStates::BrewingStandSlotCBit,
    &VanillaStates::ButtonPressedBit,
    &VanillaStates::ConditionalBit,
    &VanillaStates::CoveredBit,
    &VanillaStates::Damage,
    &VanillaStates::DisarmedBit,
    &VanillaStates::DoorHingeBit,
    &VanillaStates::UpperBlockBit,
    &VanillaStates::Direction,
    &VanillaStates::EndPortalEyeBit,
    &VanillaStates::ExplodeBit,
    &VanillaStates::FacingDirection,
    &VanillaStates::FillLevel,
    &VanillaStates::Growth,
    &VanillaStates::HeadPieceBit,
    &VanillaStates::Height,
    &VanillaStates::InfiniburnBit,
    &VanillaStates::InWallBit,
    &VanillaStates::LiquidDepth,
    &VanillaStates::MoisturizedAmount,
    &VanillaStates::NoDropBit,
    &VanillaStates::KelpAge,
    &VanillaStates::OccupiedBit,
    &VanillaStates::OpenBit,
    &VanillaStates::OutputSubtractBit,
    &VanillaStates::OutputLitBit,
    &VanillaStates::PersistentBit,
    &VanillaStates::PoweredBit,
    &VanillaStates::RailDataBit,
    &VanillaStates::RailDirection,
    &VanillaStates::RedstoneSignal,
    &VanillaStates::RepeaterDelay,
    &VanillaStates::SuspendedBit,
    &VanillaStates::ToggleBit,
    &VanillaStates::TopSlotBit,
    &VanillaStates::TriggeredBit,
    &VanillaStates::UpdateBit,
    &VanillaStates::UpsideDownBit,
    &VanillaStates::VineDirectionBits,
    &VanillaStates::AllowUnderwaterBit,
    &VanillaStates::ColorBit,
    &VanillaStates::DeadBit,
    &VanillaStates::ClusterCount,
    &VanillaStates::ItemFrameMapBit,
    &VanillaStates::SaplingType,
    &VanillaStates::TorchFacingDirection,
    &VanillaStates::DragDown,
    &VanillaStates::TurtleEggCount,
    &VanillaStates::CrackedState,
    &VanillaStates::StandingRotation,
    &VanillaStates::WeirdoDirection,
    &VanillaStates::CoralDirection,
    &VanillaStates::Color,
    &VanillaStates::BambooThickness,
    &VanillaStates::BambooLeafSize,
    &VanillaStates::Stability,
    &VanillaStates::StabilityCheckBit,
    &VanillaStates::WoodType,
    &VanillaStates::StoneType,
    &VanillaStates::DirtType,
    &VanillaStates::SandType,
    &VanillaStates::OldLogType,
    &VanillaStates::NewLogType,
    &VanillaStates::ChiselType,
    &VanillaStates::DEPRECATED,
    &VanillaStates::OldLeafType,
    &VanillaStates::NewLeafType,
    &VanillaStates::SpongeType,
    &VanillaStates::SandStoneType,
    &VanillaStates::TallGrassType,
    &VanillaStates::FlowerType,
    &VanillaStates::StoneSlabType,
    &VanillaStates::StoneSlabType2,
    &VanillaStates::StoneSlabType3,
    &VanillaStates::StoneSlabType4,
    &VanillaStates::MonsterEggStoneType,
    &VanillaStates::StoneBrickType,
    &VanillaStates::HugeMushroomBits,
    &VanillaStates::WallBlockType,
    &VanillaStates::PrismarineBlockType,
    &VanillaStates::DoublePlantType,
    &VanillaStates::ChemistryTableType,
    &VanillaStates::SeaGrassType,
    &VanillaStates::CoralColor,
    &VanillaStates::CauldronLiquid,
    &VanillaStates::HangingBit,
    &VanillaStates::StrippedBit,
    &VanillaStates::CoralHangTypeBit,
    &VanillaStates::Attachment,
    &VanillaStates::StructureVoidType,
    &VanillaStates::StructureBlockType,
    &VanillaStates::Extinguished,
    &VanillaStates::ComposterFillLevel,
    &VanillaStates::CoralFanDirection,
    &VanillaStates::LeverDirection,
    &VanillaStates::PillarAxis,
    &VanillaStates::BlockLightLevel,
    &VanillaStates::BeehiveHoneyLevel,
    &VanillaStates::WeepingVinesAge,
    &VanillaStates::WallPostBit,
    &VanillaStates::WallConnectionTypeNorth,
    &VanillaStates::WallConnectionTypeEast,
    &VanillaStates::WallConnectionTypeSouth,
    &VanillaStates::WallConnectionTypeWest,
    &VanillaStates::Rotation,
    &VanillaStates::TwistingVinesAge,
    &VanillaStates::RespawnAnchorCharge
};


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_modules_states_BlockState_##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)
#define __BLOCK__ Block* block = BlockStatesRegistry::getBlockByRuntimeId(runtimeID);


extern "C" {
    
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_states_properties_Property_getVanillaPointer
    (JNIEnv*, jclass, jint id) {
        return (jlong) KEXBlockStatesModule::vanillaStates[id];
    }

    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_states_properties_Property_nativeCreateIntegerProperty
    (JNIEnv* env, jclass, jstring name, jint id, jint possibleValuesCount) {
        STATIC_SYMBOL(ItemStateVariantInt, "_ZN16ItemStateVariantIiEC2EjRK12HashedStringj", (ItemState*, unsigned int, const HashedString&, unsigned int), void)
        ItemState* state = (ItemState*) malloc(64);
        const char* cName = env->GetStringUTFChars(name, 0);
        ItemStateVariantInt(state, (unsigned int) id, HashedString(cName), (unsigned int) possibleValuesCount);
        env->ReleaseStringUTFChars(name, cName);
        return (jlong) state;
    }

    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_states_properties_Property_nativeCreateBooleanProperty
    (JNIEnv* env, jclass, jstring name, jint id) {
        STATIC_SYMBOL(ItemStateVariantBool, "_ZN16ItemStateVariantIbEC2EjRK12HashedStringSt16initializer_listIbE", (ItemState*, unsigned int, const HashedString&, int, unsigned int), void)
        ItemState* state = (ItemState*) malloc(64);
        const char* cName = env->GetStringUTFChars(name, 0);
        ItemStateVariantBool(state, (unsigned int) id, HashedString(cName), 256, 2u);
        env->ReleaseStringUTFChars(name, cName);
        return (jlong) state;
    }

    __EXPORT__(jlong, blockLongFromRuntimeID, jint runtimeID) {
        __BLOCK__ return block == nullptr ? 0 : KEXBlocksModule::packBlockLong(IdConversion::dynamicToStatic(block->legacy->id, IdConversion::BLOCK), block->getVariant(), block->getRuntimeId());
    }

    __EXPORT__(jint, runtimeIDFromIDData, jint id, jint data) {
        Block* block = BlockRegistry::getBlockStateForIdData(IdConversion::staticToDynamic(id, IdConversion::BLOCK), data);
        return block == nullptr ? 0 : block->getRuntimeId();
    }

    __EXPORT__(jboolean, nativeHasState, jint id, jlong statePtr) {
        BlockLegacy* block = BlockRegistry::getBlockById(IdConversion::staticToDynamic(id, IdConversion::BLOCK));
        if(block == nullptr) return false;
        ItemState* state = (ItemState*) statePtr;
        return block->hasState(*state);
    }

    __EXPORT__(jint, nativeGetState, jint runtimeID, jlong statePtr) {
        __BLOCK__ if(block == nullptr) return 0;
        ItemState* state = (ItemState*) statePtr;
        return block->getState<int>(*state);
    }

    __EXPORT__(jint, nativeSetState, jint runtimeID, jlong statePtr, jint value) {
        STATIC_SYMBOL(Block_setState, "_ZNK5Block8setStateIiEEN3gsl8not_nullIPKS_EERK9ItemStateT_", (Block*, const ItemState&, int), Block*)
        __BLOCK__ if(block == nullptr) return runtimeID;
        ItemState* state = (ItemState*) statePtr;
        Block* newBlock = Block_setState(block, *state, value);
        return newBlock == nullptr ? runtimeID : newBlock->getRuntimeId();
    }

    __EXPORT__(jfloat, nativeGetFriction, jint runtimeID) {
        __BLOCK__ return block == nullptr ? .6f : block->getFriction();
    }

    __EXPORT__(jfloat, nativeGetDestroySpeed, jint runtimeID) {
        __BLOCK__ return block == nullptr ? 1.0f : block->getDestroySpeed();
    }

    __EXPORT__(jbyte, nativeGetLightBlock, jint runtimeID) {
        __BLOCK__ return block == nullptr ? 0 : (jbyte) block->getLight();
    }

    __EXPORT__(jbyte, nativeGetLightEmission, jint runtimeID) {
        __BLOCK__ return block == nullptr ? 0 : (jbyte) block->getLightEmission();
    }

}


#undef __EXPORT__
#undef __BLOCK__