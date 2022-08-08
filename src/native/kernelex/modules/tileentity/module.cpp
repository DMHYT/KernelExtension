#include <hook.h>
#include <innercore_callbacks.h>
#include <symbol.h>

#include <innercore/block_registry.h>
#include <innercore/id_conversion_map.h>

#include <BlockLegacy.hpp>

#include "module.hpp"


std::unordered_map<int, int> KEXTileEntityModule::customTileEntityBlocks;


void KEXTileEntityModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN17BlockActorFactory17createBlockEntityE14BlockActorTypeRK8BlockPosRK11BlockLegacy"),
        LAMBDA((HookManager::CallbackController* controller, stl::shared_ptr<BlockActor>* result, int type, const BlockPos& pos), {
            if(type >= 1024) {
                controller->prevent();
                *result = stl::shared_ptr<TileEntity>(new TileEntity(type, pos));
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER
    );

    Callbacks::addCallback("postModItemsInit", 
        CALLBACK([], (), {
            for(auto iter = customTileEntityBlocks.begin(); iter != customTileEntityBlocks.end(); iter++) {
                auto block = BlockRegistry::getBlockById(IdConversion::staticToDynamic(iter->first, IdConversion::BLOCK));
                if(block != nullptr) {
                    block->tileEntityType = iter->second;
                }
            }
        })
    );

}