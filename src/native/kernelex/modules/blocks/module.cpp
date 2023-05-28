#include <jni.h>

#include <innercore_callbacks.h>

#include <innercore/block_registry.h>
#include <innercore/vtable.h>

#include "module.hpp"


std::unordered_map<int, KEXBlocksModule::BlockParamsModifier*> KEXBlocksModule::modifiers;


void KEXBlocksModule::BlockParamsModifier::applyTo(int id) {
    BlockLegacy* block = BlockRegistry::getBlockById(IdConversion::staticToDynamic(id, IdConversion::BLOCK));
    if(block == nullptr) return;
    void** vtable = *(void***) block;
    if(emitsComparatorSignal) {
        VTABLE_FIND_OFFSET(BlockLegacy_hasComparatorSignal, _ZTV11BlockLegacy, _ZNK11BlockLegacy19hasComparatorSignalEv);
        vtable[BlockLegacy_hasComparatorSignal] = ADDRESS(ComparatorSignal::_enableComparatorSignal);
        VTABLE_FIND_OFFSET(BlockLegacy_getComparatorSignal, _ZTV11BlockLegacy, _ZNK11BlockLegacy19getComparatorSignalER11BlockSourceRK8BlockPosRK5Blockh);
        vtable[BlockLegacy_getComparatorSignal] = ADDRESS(ComparatorSignal::get);
    }
    if(dynamicLightEmission) {
        VTABLE_FIND_OFFSET(BlockLegacy_getLightEmission, _ZTV11BlockLegacy, _ZNK11BlockLegacy16getLightEmissionERK5Block);
        vtable[BlockLegacy_getLightEmission] = ADDRESS(LightEmission::_getLightEmissionPatch);
    }
    if(onStepOffCallbackEnabled) {
        VTABLE_FIND_OFFSET(BlockLegacy_onStepOff, _ZTV11BlockLegacy, _ZNK11BlockLegacy9onStepOffER5ActorRK8BlockPos);
        vtable[BlockLegacy_onStepOff] = ADDRESS(_patchedOnStepOff);
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

    __EXPORT__(void, nativeEnableComparatorSignalCallback, jboolean isCallbackForced) {
        MOD->emitsComparatorSignal = true;
        if(isCallbackForced) KEXBlocksModule::ComparatorSignal::forced.emplace(id);
    }
    __EXPORT__(void, nativeEnableDynamicLightEmission) {
        MOD->dynamicLightEmission = true;
        KEXBlocksModule::LightEmission::lightData.emplace(id, 0ll);
    }
    __EXPORT__(void, nativeEnableOnStepOffCallback) {
        MOD->onStepOffCallbackEnabled = true;
    }
    __EXPORT__(void, nativeSetLightEmission, jint data, jbyte lightLevel) {
        KEXBlocksModule::LightEmission::set(id, data, (unsigned char) lightLevel);
    }
    __EXPORT__(jbyte, nativeGetLightEmission, jint data) {
        return (jbyte) KEXBlocksModule::LightEmission::get(id, data);
    }

    #undef MOD

}


#undef __EXPORT__