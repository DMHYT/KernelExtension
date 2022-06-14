#include <jni.h>

#include <innercore/id_conversion_map.h>
#include <innercore/vtable.h>

#include <ActorUniqueID.hpp>
#include <ActorDamageSource.hpp>
#include <Block.hpp>
#include <BlockLegacy.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_ActorDamageSource_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jboolean, IsEntitySource) {
        VTABLE_FIND_OFFSET(ActorDamageSource_isEntitySource, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource14isEntitySourceEv);
        return VTABLE_CALL<bool>(ActorDamageSource_isEntitySource, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jboolean, IsChildEntitySource) {
        VTABLE_FIND_OFFSET(ActorDamageSource_isChildEntitySource, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource19isChildEntitySourceEv);
        return VTABLE_CALL<bool>(ActorDamageSource_isChildEntitySource, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jboolean, IsBlockSource) {
        VTABLE_FIND_OFFSET(ActorDamageSource_isBlockSource, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource13isBlockSourceEv);
        return VTABLE_CALL<bool>(ActorDamageSource_isBlockSource, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jboolean, IsCreative) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getIsCreative, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource13getIsCreativeEv);
        return VTABLE_CALL<bool>(ActorDamageSource_getIsCreative, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jboolean, IsWorldBuilder) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getIsWorldBuilder, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource17getIsWorldBuilderEv);
        return VTABLE_CALL<bool>(ActorDamageSource_getIsWorldBuilder, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jlong, GetEntityUniqueID) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getEntityUniqueID, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource17getEntityUniqueIDEv);
        return VTABLE_CALL<ActorUniqueID>(ActorDamageSource_getEntityUniqueID, (ActorDamageSource*) ptr).id;
    }
    __EXPORT__(jint, GetEntityType) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getEntityType, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource13getEntityTypeEv);
        return (int) VTABLE_CALL<ActorType>(ActorDamageSource_getEntityType, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jint, GetEntityCategories) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getEntityCategories, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource19getEntityCategoriesEv);
        return VTABLE_CALL<int>(ActorDamageSource_getEntityCategories, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jboolean, IsDamagingEntityCreative) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getDamagingEntityIsCreative, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource27getDamagingEntityIsCreativeEv);
        return VTABLE_CALL<bool>(ActorDamageSource_getDamagingEntityIsCreative, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jboolean, IsDamagingEntityWorldBuilder) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getDamagingEntityIsWorldBuilder, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource31getDamagingEntityIsWorldBuilderEv);
        return VTABLE_CALL<bool>(ActorDamageSource_getDamagingEntityIsWorldBuilder, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jlong, GetDamagingEntityUniqueID) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getDamagingEntityUniqueID, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource25getDamagingEntityUniqueIDEv);
        return VTABLE_CALL<ActorUniqueID>(ActorDamageSource_getDamagingEntityUniqueID, (ActorDamageSource*) ptr).id;
    }
    __EXPORT__(jint, GetDamagingEntityType) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getDamagingEntityType, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource21getDamagingEntityTypeEv);
        return (int) VTABLE_CALL<ActorType>(ActorDamageSource_getDamagingEntityType, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jint, GetDamagingEntityCategories) {
        VTABLE_FIND_OFFSET(ActorDamageSource_getDamagingEntityCategories, _ZTV17ActorDamageSource, _ZNK17ActorDamageSource27getDamagingEntityCategoriesEv);
        return VTABLE_CALL<int>(ActorDamageSource_getDamagingEntityCategories, (ActorDamageSource*) ptr);
    }
    __EXPORT__(jint, GetCause) {
        return ((ActorDamageSource*) ptr)->getCause();
    }
    __EXPORT__(void, SetCause, jint cause) {
        ((ActorDamageSource*) ptr)->setCause((ActorDamageCause) cause);
    }
    __EXPORT__(jlong, GetBlock) {
        Block* block = ((ActorDamageByBlockSource*) ptr)->getBlock();
        if(block == nullptr) return 0;
        int id = IdConversion::dynamicToStatic(block->legacy->id, IdConversion::BLOCK);
        int data = block->getVariant();
        int runtimeId = (int) block->getRuntimeId();
        return (jlong) ((((unsigned long long) id << 16) | (unsigned long long) data) | ((unsigned long long) runtimeId << 32));
    }
}


#undef __EXPORT__