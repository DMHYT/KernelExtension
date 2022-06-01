#include <unordered_map>
#include <unordered_set>

#include <mod.h>

#include <LootTable.hpp>

#include <json/reader.h>

#ifndef KEX_MODULES_LOOT_HPP
#define KEX_MODULES_LOOT_HPP


class KEXLootModule : public Module {
    public:
    static Json::Reader* jsonReader;
    static std::string getLootTableName(LootTable* table);
    static std::unordered_map<std::string, std::string> cachedModifiedTables;
    static std::unordered_set<std::string> tablesWithDropCallbacks;
    KEXLootModule(Module* parent): Module(parent, "kernelex.loot") {};
    virtual void initialize();
};


#endif //KEX_MODULES_LOOT_HPP