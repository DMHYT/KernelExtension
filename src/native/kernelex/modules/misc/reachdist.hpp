#include <unordered_set>

#include <mod.h>

#ifndef KEX_MODULES_MISC_REACHDIST_HPP
#define KEX_MODULES_MISC_REACHDIST_HPP


class KEXMiscReachDistModule : public Module {
    public:
    struct ReachDistModifier {
        float modifier, multiplier;
        bool enabled;
        ReachDistModifier(): modifier(0.0f), multiplier(1.0f), enabled(false) {}
    };
    static std::unordered_set<ReachDistModifier*> modifiers;
    static float last;
    static float apply(float);
    KEXMiscReachDistModule(Module* parent): Module(parent, "kex.misc.reachdist") {}
    virtual void initialize();
};


#endif //KEX_MODULES_MISC_REACHDIST_HPP