#include <stl/string>
#include <stl/vector>
#include <stl.h>

#include <hook.h>
#include <symbol.h>
#include <logger.h>

#include <Item.hpp>
#include <ItemStackBase.hpp>
#include <Level.hpp>

#include "tooltip.hpp"


void KEXItemsTooltipModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    // HookManager::addCallback(
    //     SYMBOL("mcpe", "_ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb"),
    //     LAMBDA((Item* item, const ItemStackBase& stack, Level& level, stl::string& text, bool b), {
            
    //     }, ),
    //     HookManager::RETURN | HookManager::LISTENER
    // )

}