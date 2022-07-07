#include <jni.h>

#include <hook.h>
#include <symbol.h>
#include <static_symbol.h>

#include <mce/UUID.hpp>
#include <Level.hpp>

#include "chunks.hpp"


TickingAreaAddResult KEXChunksModule::addArea(TickingAreasManager* mgr, Dimension& dimension, const stl::string& name, const Bounds& bounds, bool circle) {
    STATIC_SYMBOL(getAreasVector, "_ZNSt6__ndk113unordered_mapI11AutomaticIDI9DimensioniENS_6vectorI11PendingAreaNS_9allocatorIS5_EEEENS_4hashIS3_EENS_8equal_toIS3_EENS6_INS_4pairIKS3_S8_EEEEEixEOS3_", (void*, const AutomaticID<Dimension, int>&), stl::vector<PendingArea>&);
    STATIC_SYMBOL(generateUUID, "_ZN6Crypto6Random12generateUUIDEv", (), mce::UUID);
    STATIC_SYMBOL(constructArea, "_ZN11PendingAreaC2EN3mce4UUIDERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERK6Boundsb", (PendingArea*, const stl::string*, mce::UUID, const stl::string*, const Bounds*, bool), void);
    auto dimensionId = dimension.getDimensionId();
    auto& areasVector = getAreasVector( (void*) ((char*) mgr + 4), dimensionId );
    auto areasList = dimension.getTickingAreas();
    if(areasList->hasTickingAreaNamed(name) || mgr->_hasPendingTickingAreaNamed(name, areasVector))
        return NAME_ALREADY_EXISTS;
    stl::string areaName = name.empty() ? mgr->_findUsableDefaultName(*areasList, areasVector) : name;
    auto uuid = generateUUID();
    PendingArea* area = (PendingArea*) operator new(96);
    constructArea(area, &name, uuid, &name, &bounds, circle);
    areasVector.emplace_back(PendingArea(*area));
    delete area;
    auto levelStorage = dimension.getLevel()->getLevelStorage();
    mgr->_savePendingArea(*levelStorage, dimensionId, areasVector.back());
    return SUCCESS;
}


void KEXChunksModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN19TickingAreasManager8_addAreaER9DimensionRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERK6Boundsb"),
        LAMBDA((HookManager::CallbackController* controller, TickingAreasManager* mgr, Dimension& dimension, const stl::string& name, const Bounds& bounds, bool circle), {
            controller->replace();
            return addArea(mgr, dimension, name, bounds, circle);
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

}