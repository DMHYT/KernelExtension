#include <stl/string>
#include <stl/vector>

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
    LootTable(std::__ndk1::string);
    LootTable();
    ~LootTable();
    std::__ndk1::vector<ItemStack> getRandomItems(Random&, LootTableContext&) const;
    void* getAvailableSlots(Container&, Random&);
    std::__ndk1::string getDir() const;
    // void deserialize(Json::Value);
    // void shuffleAndSplitItems(std::__ndk1::vector<ItemStack>&, int, Random&);
    void fill(Container&, Random&, LootTableContext&);
};

class LootTables {
    public:
    LootTable* lookupByName(std::__ndk1::string const&, ResourcePackManager&);
};

class Util {
    public:
    class LootTableUtils {
        public:
        static void fillContainer(Level&, Container&, Random&, std::__ndk1::string const&, Actor*);
    };
};


#endif //KEX_LOOTTABLE_HPP