#include <unordered_map>
#include <mod.h>
#include <LootTable.hpp>

#ifndef KEX_MODULES_LOOT_HPP
#define KEX_MODULES_LOOT_HPP


class KEXLootModule : public Module {
    public:
    static std::string getLootTableName(LootTable* table);
    static std::unordered_map<std::string, std::string> cachedModifiedTables;
    KEXLootModule(Module* parent): Module(parent, "kernelex.loot") {};
    virtual void initialize();
};


#endif //KEX_MODULES_LOOT_HPP