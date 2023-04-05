#include "LootTableContext.hpp"

#ifndef KEX_LOOTITEMCONDITION_HPP
#define KEX_LOOTITEMCONDITION_HPP


class Random;

class LootItemCondition {
    public:
    virtual ~LootItemCondition() {};
    // _ZTV17LootItemCondition does not exist for some reason...
    // /*0*/ virtual ~LootItemCondition();
    // /*1*/ virtual bool applies(Random&, LootTableContext&) = 0;
};


#endif //KEX_LOOTITEMCONDITION_HPP