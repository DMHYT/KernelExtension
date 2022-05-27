#include <mod.h>

#ifndef KEX_MODULES_TOOLS_SUBMODULES_INTERACTIONS_HPP
#define KEX_MODULES_TOOLS_SUBMODULES_INTERACTIONS_HPP


class KEXToolInteractionsModule : public Module {
    public:
    KEXToolInteractionsModule(Module* parent): Module(parent, "kex.tools.interactions") {};
    virtual void initialize();
};


#endif //KEX_MODULES_TOOLS_SUBMODULES_INTERACTIONS_HPP