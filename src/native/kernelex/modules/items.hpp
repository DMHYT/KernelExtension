#include <unordered_map>
#include <mod.h>
#include <ItemStackBase.hpp>

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
    ItemParamsModifier() {}
    void applyTo(int id);
    static bool _anvilRepairDisable(ItemStackBase const&, ItemStackBase const&) {
        return false;
    }
};


class KEXItemsModule : public Module {
    public:
    static std::unordered_map<int, ItemParamsModifier*> itemParamsModifiers;
    static ItemParamsModifier* getOrCreateModifier(int);
    KEXItemsModule(Module* parent): Module(parent, "kex.items") {}
    virtual void initialize();
};


#endif //KEX_MODULES_ITEMS_HPP