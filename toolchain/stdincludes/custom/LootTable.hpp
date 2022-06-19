#include <stl/string>
#include <stl/vector>
#include <stl.h>

#include <ItemStackBase.hpp>
#include <ItemStack.hpp>

#ifndef KEX_LOOTTABLE_HPP
#define KEX_LOOTTABLE_HPP


class Container;
#ifndef KEX_LEVEL_HPP
    class Level;
#endif
#ifndef KEX_LOOTTABLECONTEXT_HPP
    class LootTableContext {public:};
#endif
class Random {public:};
class ResourcePackManager;

class LootTable {
    public:
    LootTable(stl::string);
    LootTable();
    ~LootTable();
    stl::vector<ItemStack> getRandomItems(Random&, LootTableContext&) const;
    void* getAvailableSlots(Container&, Random&);
    stl::string getDir() const;
    // void deserialize(Json::Value);
    // void shuffleAndSplitItems(stl::vector<ItemStack>&, int, Random&);
    void fill(Container&, Random&, LootTableContext&);
};

class LootTables {
    public:
    LootTable* lookupByName(const stl::string&, ResourcePackManager&);
};

class Util {
    public:
    class LootTableUtils {
        public:
        static void fillContainer(Level&, Container&, Random&, const stl::string&, Actor*);
    };
};


#endif //KEX_LOOTTABLE_HPP