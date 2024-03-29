#include <unordered_map>
#include <unordered_set>

#include <mod.h>

#include <loot/LootItemCondition.hpp>
#include <loot/LootItemFunction.hpp>
#include <loot/LootTable.hpp>

#include <json/reader.h>

#ifndef KEX_MODULES_LOOT_HPP
#define KEX_MODULES_LOOT_HPP


class KEXLootModule : public Module {
    public:
    class CustomLootCondition : public LootItemCondition {
        public:
        virtual bool applies(Random&, LootTableContext&);
        std::string conditionName; // 16
        Json::Value json; // 32
        CustomLootCondition(const std::string& _conditionName, const Json::Value& _json):
            LootItemCondition(), conditionName(_conditionName), json(_json) {}
    };
    class CustomLootFunction : public LootItemFunction {
        public:
        std::string functionName; // 28
        Json::Value json; // 44
        virtual void apply(ItemStack&, Random&, LootTableContext&);
        virtual void apply(ItemInstance&, Random&, LootTableContext&);
        CustomLootFunction(const ConditionsVec& conditions, const std::string& _functionName, const Json::Value& _json):
            LootItemFunction(const_cast<ConditionsVec&>(conditions)), functionName(_functionName), json(_json) {}
    };
    static Json::Reader* jsonReader;
    static std::string getLootTableName(LootTable* table);
    static std::unordered_map<std::string, std::string> cachedModifiedTables;
    static std::unordered_set<std::string> tablesWithDropCallbacks;
    static std::unordered_set<std::string> vanillaLootConditions;
    static std::unordered_set<std::string> customLootConditions;
    static std::unordered_set<std::string> vanillaLootFunctions;
    static std::unordered_set<std::string> customLootFunctions;
    KEXLootModule(Module* parent): Module(parent, "kex.loot") {};
    virtual void initialize();
};


#endif //KEX_MODULES_LOOT_HPP