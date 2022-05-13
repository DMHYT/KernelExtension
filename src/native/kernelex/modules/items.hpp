#include <unordered_map>

#include <mod.h>

#include <ItemStackBase.hpp>
#include <ItemStack.hpp>

#ifndef KEX_MODULES_ITEMS_HPP
#define KEX_MODULES_ITEMS_HPP


class ItemParamsModifier {
    public:
    bool requiresWorldBuilder = false;
    bool explodable = true;
    bool fireResistant = false;
    bool shouldDespawn = true;
    bool mirroredArt = false;
    float furnaceBurnIntervalMultiplier = -1.0f;
    float furnaceXPMultiplier = -1.0f;
    bool cannotBeRepairedInAnvil = false;
    int cooldownTime = -1;
    bool dynamicUseDuration = false;
    ItemParamsModifier() {}
    void applyTo(int id);
    static bool _anvilRepairDisable(ItemStackBase const&, ItemStackBase const&) {
        return false;
    }
    static int _getCooldownTimePatch(Item* item);
    static int _getMaxUseDurationPatch(Item* item, ItemStackBase const* stack);
};


class KEXItemsModule : public Module {
    public:
    static std::unordered_map<int, ItemParamsModifier*> itemParamsModifiers;
    static std::unordered_map<std::string, float> customFoodSaturationModifiers;
    static ItemParamsModifier* getOrCreateModifier(int);
    static ItemParamsModifier* getModifierOrNull(int id) {
        auto found = itemParamsModifiers.find(id);
        if(found == itemParamsModifiers.end()) return nullptr;
        return found->second;
    }
    static inline bool hasModifier(int id) {
        return itemParamsModifiers.find(id) != itemParamsModifiers.end();
    }
    KEXItemsModule(Module* parent): Module(parent, "kex.items") {}
    virtual void initialize();
};


#endif //KEX_MODULES_ITEMS_HPP