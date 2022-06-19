#include <stl/vector>
#include <stl.h>

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <mod.h>

#include <ActorDamageSource.hpp>

#ifndef KEX_MODULES_DAMAGE_HPP
#define KEX_MODULES_DAMAGE_HPP


class KEXDamageModule : public Module {
    public:
    static std::unordered_map<int, std::string> causeToCauseName;
    static std::unordered_map<std::string, int> causeNameToCause;
    static std::unordered_set<int> fireCauses;
    static std::unordered_set<int> customTranslationCallbacks;
    static int nextCustomCauseId;
    KEXDamageModule(Module* parent): Module(parent, "kex.damage") {}
    virtual void initialize();
};


#endif //KEX_MODULES_DAMAGE_HPP