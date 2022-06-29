#include <unordered_map>

#include <mod.h>

#include <ContainerManagerController.hpp>

#ifndef KEX_MODULES_MISC_SMITHING_HPP
#define KEX_MODULES_MISC_SMITHING_HPP


class KEXMiscSmithingModule : public Module {
    public:
    static std::unordered_map<int, std::unordered_map<int, int>> recipes;
    static void replaceRecipeResult(ItemInstance*, void*);
    static bool consumeInputs(ContainerManagerController*);
    static void consumeMaterials(ContainerManagerController*);
    KEXMiscSmithingModule(Module* parent): Module(parent, "kex.misc.smithing") {}
    virtual void initialize();
};


#endif //KEX_MODULES_MISC_SMITHING_HPP