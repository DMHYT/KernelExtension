#include <string>
#include <unordered_map>

#include <mod.h>

#include <innercore/id_conversion_map.h>

#include <Item.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>
#include <FoodItemComponentLegacy.hpp>

#include "../../../utils/java_utils.hpp"

#ifndef KEX_MODULES_ITEMS_SUBMODULES_FOOD_HPP
#define KEX_MODULES_ITEMS_SUBMODULES_FOOD_HPP


class KEXItemsFoodModule : public Module {
    public:
    static std::unordered_map<std::string, float> customFoodSaturationModifiers;
    static ItemStack cachedFoodStack;
    KEXItemsFoodModule(Module* parent): Module(parent, "kex.items.food") {}
    virtual void initialize();
};


#endif //KEX_MODULES_ITEMS_SUBMODULES_FOOD_HPP