#include <stl/vector>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>

#ifndef KEX_LOOTTABLE_HPP
#define KEX_LOOTTABLE_HPP


class Container;
class LootTableContext {public:};
class Random {public:};

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


#endif //KEX_LOOTTABLE_HPP