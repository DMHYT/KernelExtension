#include <stl/string>

#ifndef KEX_LOOTTABLE_HPP
#define KEX_LOOTTABLE_HPP


class Container;
class LootTableContext;
class Random;

class LootTable {
    public:
    LootTable(std::__ndk1::string);
    LootTable();
    ~LootTable();
    void* getRandomItems(Random&, LootTableContext&) const;
    void* getAvailableSlots(Container&, Random&);
    std::__ndk1::string getDir() const;
    // void deserialize(Json::Value);
    // void shuffleAndSplitItems(std::__ndk1::vector<ItemStack>&, int, Random&);
    void fill(Container&, Random&, LootTableContext&);
};


#endif //KEX_LOOTTABLE_HPP