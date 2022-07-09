#include <jni.h>

#include <logger.h>

#include <BlockSource.hpp>
#include <Dimension.hpp>
#include <TickingAreasManager.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_TickingAreasManager_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jboolean, HasActiveAreas) {
        TickingAreasManager* mgr = (TickingAreasManager*) ptr; 
        return mgr->hasActiveAreas();
    }
    __EXPORT__(jint, CountAreasIn, jlong dimensionPtr) {
        TickingAreasManager* mgr = (TickingAreasManager*) ptr;
        Dimension* dimension = (Dimension*) dimensionPtr;
        return mgr->countPendingAreas(*dimension);
    }
    __EXPORT__(jint, CountAllAreas) {
        TickingAreasManager* mgr = (TickingAreasManager*) ptr;
        return mgr->countStandaloneTickingAreas();
    }
    __EXPORT__(jboolean, HasArea, jstring areaName, jint dimensionId) {
        const char* cAreaName = env->GetStringUTFChars(areaName, 0);
        TickingAreasManager* mgr = (TickingAreasManager*) ptr;
        AutomaticID<Dimension, int> dim(dimensionId);
        bool result = mgr->_hasPendingTickingAreaNamed(cAreaName, mgr->getPendingAreasForDimension(dim));
        env->ReleaseStringUTFChars(areaName, cAreaName);
        return result;
    }
    __EXPORT__(void, AddRectangleArea, jlong dimensionPtr, jstring areaName, jint x1, jint z1, jint x2, jint z2) {
        const char* cAreaName = env->GetStringUTFChars(areaName, 0);
        TickingAreasManager* mgr = (TickingAreasManager*) ptr;
        Dimension* dimension = (Dimension*) dimensionPtr;
        mgr->addArea(*dimension, cAreaName, BlockPos(x1, 0, z1), BlockPos(x2, 0, z2));
        env->ReleaseStringUTFChars(areaName, cAreaName);
    }
    __EXPORT__(void, AddCircleArea, jlong dimensionPtr, jstring areaName, jint x, jint z, jint radius) {
        const char* cAreaName = env->GetStringUTFChars(areaName, 0);
        TickingAreasManager* mgr = (TickingAreasManager*) ptr;
        Dimension* dimension = (Dimension*) dimensionPtr;
        mgr->addArea(*dimension, cAreaName, BlockPos(x, 0, z), radius);
        env->ReleaseStringUTFChars(areaName, cAreaName);
    }
    __EXPORT__(void, RemoveAreaByPosition, jlong dimensionPtr, jint x, jint z) {
        TickingAreasManager* mgr = (TickingAreasManager*) ptr;
        Dimension* dimension = (Dimension*) dimensionPtr;
        mgr->removePendingAreaByPosition(*dimension, BlockPos(x, 0, z));
    }
    __EXPORT__(void, RemoveAreaByName, jlong dimensionPtr, jstring areaName) {
        const char* cAreaName = env->GetStringUTFChars(areaName, 0);
        TickingAreasManager* mgr = (TickingAreasManager*) ptr;
        Dimension* dimension = (Dimension*) dimensionPtr;
        mgr->removePendingAreaByName(*dimension, cAreaName);
        env->ReleaseStringUTFChars(areaName, cAreaName);
    }
    __EXPORT__(jstring, FindUsableDefaultName, jlong dimensionPtr) {
        TickingAreasManager* mgr = (TickingAreasManager*) ptr;
        Dimension* dimension = (Dimension*) dimensionPtr;
        auto areasList = dimension->getTickingAreas();
        auto& areasVector = mgr->getPendingAreasForDimension(dimension->getDimensionId());
        auto areaName = mgr->_findUsableDefaultName(*areasList, areasVector);
        return env->NewStringUTF(areaName.c_str());
    }
}


#undef __EXPORT__