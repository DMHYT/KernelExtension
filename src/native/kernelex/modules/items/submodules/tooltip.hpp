#include <unordered_map>

#include <mod.h>

#ifndef KEX_MODULES_ITEMS_SUBMODULES_TOOLTIP_HPP
#define KEX_MODULES_ITEMS_SUBMODULES_TOOLTIP_HPP


class KEXItemsTooltipModule : public Module {
    public:
    // static int currentCalls;
    // static long long lastTimestamp;
    // static std::unordered_map<int, bool> isCallbackForced;
    // static bool isRecursive;
    // static bool wasCalled;
    // static std::string tooltip;
    // struct TooltipCache {
    //     std::string tooltip;
    //     long long timestamp = -1;
    //     bool isCalled = false;
    // };
    // static std::unordered_map<int, TooltipCache> cachedTooltipMap;
    // static inline bool updateTimestamp(int);
    KEXItemsTooltipModule(Module* parent): Module(parent, "kex.items.tooltip") {}
    virtual void initialize();
};


#endif //KEX_MODULES_ITEMS_SUBMODULES_TOOLTIP_HPP