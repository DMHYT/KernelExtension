#include <stl/string>
#include <stl.h>

#include <unordered_map>

#include <mod.h>

#include <Item.hpp>
#include <ItemStackBase.hpp>
#include <Level.hpp>

#ifndef KEX_MODULES_ITEMS_SUBMODULES_TOOLTIP_HPP
#define KEX_MODULES_ITEMS_SUBMODULES_TOOLTIP_HPP


long long getTimeMilliseconds();

class KEXItemsTooltipModule : public Module {
    public:
    static std::unordered_map<int, std::string> tooltipCache;
    static std::unordered_map<int, bool> isCallbackForced;
    static unsigned short currentCalls;
    static long long lastTimestamp;
    static inline bool isCachePresent(int id) {
        return tooltipCache.find(id) != tooltipCache.end();
    }
    static inline bool isTooltipCallbackForced(int id) {
        auto found = isCallbackForced.find(id);
        return found != isCallbackForced.end() ? found->second : false;
    }
    static void append(int, const ItemStackBase*, Level*, stl::string&);
    KEXItemsTooltipModule(Module* parent): Module(parent, "kex.items.tooltip") {}
    virtual void initialize();
};


#endif //KEX_MODULES_ITEMS_SUBMODULES_TOOLTIP_HPP