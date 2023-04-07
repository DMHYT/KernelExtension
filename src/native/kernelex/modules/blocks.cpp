#include <jni.h>

#include <hook.h>
#include <innercore_callbacks.h>
#include <symbol.h>

#include <innercore/block_registry.h>
#include <innercore/vtable.h>

#include "blocks.hpp"


std::unordered_map<int, KEXBlocksModule::BlockParamsModifier*> KEXBlocksModule::modifiers;


void KEXBlocksModule::BlockParamsModifier::applyTo(int id) {
    BlockLegacy* block = BlockRegistry::getBlockById(IdConversion::staticToDynamic(id, IdConversion::BLOCK));
    if(block == nullptr) return;
    void** vtable = *(void***) block;
    if(emitsComparatorSignal) {
        VTABLE_FIND_OFFSET(BlockLegacy_hasComparatorSignal, _ZTV11BlockLegacy, _ZNK11BlockLegacy19hasComparatorSignalEv)
        vtable[BlockLegacy_hasComparatorSignal] = ADDRESS(_enableComparatorSignal);
        VTABLE_FIND_OFFSET(BlockLegacy_getComparatorSignal, _ZTV11BlockLegacy, _ZNK11BlockLegacy19getComparatorSignalER11BlockSourceRK8BlockPosRK5Blockh);
        vtable[BlockLegacy_getComparatorSignal] = ADDRESS(_getComparatorSignalPatch);
    }
}


void KEXBlocksModule::initialize() {

    Callbacks::addCallback("postModItemsInit",
        CALLBACK([], (), {
            for(auto iter = modifiers.begin(); iter != modifiers.end(); iter++) {
                iter->second->applyTo(iter->first);
            }
        })
    );

}


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_modules_BlocksModule_##NAME (JNIEnv* env, jclass clazz, jint id, ##__VA_ARGS__)


extern "C" {

    #define MOD KEXBlocksModule::getOrCreateModifier(id)

    __EXPORT__(void, nativeEnableComparatorSignalCallback) {
        MOD->emitsComparatorSignal = true;
    }

    #undef MOD

}


#undef __EXPORT__