#include <hook.h>
#include <innercore_callbacks.h>
#include <symbol.h>

#include <innercore/block_registry.h>
#include <innercore/id_conversion_map.h>
#include <innercore/vtable.h>

#include <BlockLegacy.hpp>
#include <Block.hpp>
#include <GameMode.hpp>

#include "module.hpp"


std::unordered_map<int, int> KEXTileEntityModule::customTileEntityBlocks;


void KEXTileEntityModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17BlockActorFactory17createBlockEntityE14BlockActorTypeRK8BlockPosRK11BlockLegacy"),
        LAMBDA((HookManager::CallbackController* controller, stl::shared_ptr<BlockActor>* result, int type, const BlockPos& pos, const BlockLegacy& blockLegacy), {
            if(type >= 1024) {
                controller->prevent();
                new (result) stl::shared_ptr<TileEntity>(new TileEntity(type, pos));
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN8GameMode9useItemOnER9ItemStackRK8BlockPoshRK4Vec3PK5Block"),
        LAMBDA((HookManager::CallbackController* controller, GameMode* gm, ItemStack& item, const BlockPos& pos, unsigned char side, const Vec3& vec, const Block& state), {
            auto blockEntity = gm->player->getRegion()->getBlockEntity(pos);
            if(
                blockEntity != nullptr &&
                (int) blockEntity->type >= 1024 &&
                ((KEXTileEntityModule::TileEntity*) blockEntity)->onUse(*(gm->player), side, vec)
            ) {
                controller->replace();
                return true;
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    Callbacks::addCallback("postModItemsInit", 
        CALLBACK([], (), {
            for(auto iter = customTileEntityBlocks.begin(); iter != customTileEntityBlocks.end(); iter++) {
                auto block = BlockRegistry::getBlockById(IdConversion::staticToDynamic(iter->first, IdConversion::BLOCK));
                if(block != nullptr) {
                    block->tileEntityType = iter->second;
                    void** vtable = *(void***) block;
                    VTABLE_FIND_OFFSET(neighborChanged, _ZTV11BlockLegacy, _ZNK11BlockLegacy15neighborChangedER11BlockSourceRK8BlockPosS4_);
                    VTABLE_FIND_OFFSET(triggerEvent, _ZTV11BlockLegacy, _ZNK11BlockLegacy12triggerEventER11BlockSourceRK8BlockPosii);
                    vtable[neighborChanged] = SYMBOL("mcpe", "_ZNK10ActorBlock15neighborChangedER11BlockSourceRK8BlockPosS4_");
                    vtable[triggerEvent] = SYMBOL("mcpe", "_ZNK10ActorBlock12triggerEventER11BlockSourceRK8BlockPosii");
                }
            }
        })
    );

}