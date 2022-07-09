#include <jni.h>

#include <hook.h>
#include <symbol.h>
#include <static_symbol.h>

#include <mce/UUID.hpp>
#include <Level.hpp>

#include "chunks.hpp"


TickingAreaAddResult KEXChunksModule::addArea(TickingAreasManager* mgr, Dimension& dimension, const stl::string& name, const Bounds& bounds, bool circle) {
    auto dimensionId = dimension.getDimensionId();
    auto& areasVector = mgr->getPendingAreasForDimension(dimensionId);
    auto areasList = dimension.getTickingAreas();
    if(areasList->hasTickingAreaNamed(name) || mgr->_hasPendingTickingAreaNamed(name, areasVector))
        return NAME_ALREADY_EXISTS;
    stl::string areaName = name.empty() ? mgr->_findUsableDefaultName(*areasList, areasVector) : name;
    auto area = PendingArea::constructArea(areaName, bounds, circle);
    areasVector.emplace_back(*area);
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