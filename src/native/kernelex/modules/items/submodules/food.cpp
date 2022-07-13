#include <stl/string>
#include <stl.h>

#include <math.h>

#include <hook.h>
#include <symbol.h>

#include "food.hpp"
#include "../module.hpp"

std::unordered_map<std::string, float> KEXItemsFoodModule::customFoodSaturationModifiers;
ItemStack KEXItemsFoodModule::cachedFoodStack;


void KEXItemsFoodModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_Z24FoodSaturationFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE"),
        LAMBDA((HookManager::CallbackController* controller, const stl::string& str), {
            controller->replace();
            float defaultResult = controller->call<float>(str);
            if(roundf(defaultResult * 100) / 100 == 0.6f && str != "normal") {
                auto found = customFoodSaturationModifiers.find(str.c_str());
                if(found != customFoodSaturationModifiers.end()) {
                    return found->second;
                }
            }
            return defaultResult;
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN23FoodItemComponentLegacy3useER9ItemStackR6Player"),
        LAMBDA((FoodItemComponentLegacy* food, ItemStack& stack, Player& player), {
            auto item = stack.getItem();
            if(item != nullptr) {
                int staticId = IdConversion::dynamicToStatic(item->id, IdConversion::ITEM);
                auto mod = KEXItemsModule::getModifierOrNull(staticId);
                if(mod != nullptr && mod->dynamicFoodValues) {
                    cachedFoodStack = stack;
                    KEXJavaBridge::ItemsModule::getDynamicFoodValues((jlong) &cachedFoodStack, (jlong) food);
                }
            }
        }, ),
        HookManager::CALL | HookManager::LISTENER
    );

}