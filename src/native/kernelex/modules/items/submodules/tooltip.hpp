#include <stl/string>
#include <stl.h>

#include <unordered_map>

#include <mod.h>

#include <Item.hpp>
#include <ItemStackBase.hpp>
#include <Level.hpp>

#ifndef KEX_MODULES_ITEMS_SUBMODULES_TOOLTIP_HPP
#define KEX_MODULES_ITEMS_SUBMODULES_TOOLTIP_HPP


class KEXItemsTooltipModule : public Module {
    public:
    static std::unordered_map<long long, std::string> tooltipCache;
    static std::unordered_map<int, bool> isCallbackForced;
    static unsigned short currentCalls;
    static long long lastTimestamp;
    static inline bool isCachePresent(long long idDataLong) {
        return tooltipCache.find(idDataLong) != tooltipCache.end();
    }
    static inline bool isTooltipCallbackForced(int id) {
        auto found = isCallbackForced.find(id);
        return found != isCallbackForced.end() ? found->second : false;
    }
    static void append(int, int, const ItemStackBase*, Level*, stl::string&);
    KEXItemsTooltipModule(Module* parent): Module(parent, "kex.items.tooltip") {}
    virtual void initialize();
};


#endif //KEX_MODULES_ITEMS_SUBMODULES_TOOLTIP_HPP