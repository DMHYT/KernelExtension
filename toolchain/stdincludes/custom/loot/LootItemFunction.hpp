#include <stl/memory>
#include <stl/vector>
#include <stl.h>

#include <ItemStackBase.hpp>
#include <ItemStack.hpp>
#include <ItemInstance.hpp>
#include "LootTableContext.hpp"

#ifndef KEX_LOOTITEMFUNCTION_HPP
#define KEX_LOOTITEMFUNCTION_HPP


class LootItemCondition {public:};
class Random;
class Trade;

class LootItemFunction {
    public:
    using ConditionsVec = stl::vector<stl::unique_ptr<LootItemCondition>>;
    ConditionsVec conditionsVector; // 16
    /*0*/ virtual ~LootItemFunction();
    /*1*/ virtual void apply(ItemStack&, Random&, LootTableContext&) = 0;
    /*2*/ virtual int apply(ItemStack&, Random&, const Trade&, LootTableContext&);
    /*3*/ virtual void apply(ItemInstance&, Random&, LootTableContext&) = 0;
    /*4*/ virtual int apply(ItemInstance&, Random&, const Trade&, LootTableContext&);
    LootItemFunction(ConditionsVec&);
};


#endif //KEX_LOOTITEMFUNCTION_HPP