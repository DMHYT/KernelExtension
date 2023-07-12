#include <vector>

#include <mod.h>

#include <ItemState.hpp>


class KEXBlockStatesModule : public Module {
    public:
    static std::vector<ItemState*> vanillaStates;
    KEXBlockStatesModule(Module* parent): Module(parent, "kex.blocks.states") {}
    inline virtual void initialize() {}
};