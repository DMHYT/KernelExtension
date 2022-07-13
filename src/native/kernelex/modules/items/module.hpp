#include <unordered_map>

#include <mod.h>

#include <innercore/id_conversion_map.h>

#include <Item.hpp>
#include <ItemStackBase.hpp>

#include "../../utils/java_utils.hpp"

#ifndef KEX_MODULES_ITEMS_MODULE_HPP
#define KEX_MODULES_ITEMS_MODULE_HPP


class KEXItemsModule : public Module {
    public:
    class ItemParamsModifier {
        public:
        float furnaceBurnIntervalMultiplier = -1.0f;
        float furnaceXPMultiplier = -1.0f;
        int cooldownTime = -1;
        bool requiresWorldBuilder = false;
        bool explodable = false;
        bool fireResistant = false;
        bool shouldDespawn = true;
        bool mirroredArt = false;
        bool cannotBeRepairedInAnvil = false;
        bool dynamicUseDuration = false;
        bool dynamicFoodValues = false;
        ItemParamsModifier() {}
        void applyTo(int id);
    };
    static std::unordered_map<int, ItemParamsModifier*> modifiers;
    static inline ItemParamsModifier* getOrCreateModifier(int id) {
        auto found = modifiers.find(id);
        if(found != modifiers.end()) return found->second;
        else {
            modifiers.emplace(id, new ItemParamsModifier());
            return modifiers.at(id);
        }
    }
    static inline ItemParamsModifier* getModifierOrNull(int id) {
        auto found = modifiers.find(id);
        return found != modifiers.end() ? found->second : nullptr;
    }
    static inline bool hasModifier(int id) {
        return modifiers.find(id) != modifiers.end();
    }
    static inline bool _anvilRepairDisable(Item*, const ItemStackBase&, const ItemStackBase&) {
        return false;
    }
    static inline int _getCooldownTimePatch(Item* item) {
        return modifiers.at(IdConversion::dynamicToStatic(item->id, IdConversion::ITEM))->cooldownTime;
    }
    static inline int _getMaxUseDurationPatch(Item* item, const ItemStackBase* stack) {
        return KEXJavaBridge::ItemsModule::getUseDurationDynamic((jlong) stack);
    }
    KEXItemsModule(Module* parent): Module(parent, "kex.items") {}
    virtual void initialize();
};


#endif //KEX_MODULES_ITEMS_MODULE_HPP