#include <unordered_set>

#include <mod.h>

#ifndef KEX_MODULES_MISC_REACHDIST_HPP
#define KEX_MODULES_MISC_REACHDIST_HPP


class KEXMiscReachDistModule : public Module {
    public:
    class ReachDistModifier {
        public:
        float modifier = 0.0f;
        float multiplier = 1.0f;
        bool enabled = false;
        ReachDistModifier() {}
        inline void setModifier(float mod) {
            modifier = mod;
        }
        inline void setMultiplier(float mult) {
            multiplier = mult;
        }
        inline void toggle(bool on) {
            enabled = on;
        }
        inline float getModifier() const {
            return modifier;
        }
        inline float getMultiplier() const {
            return multiplier;
        }
        inline bool isActive() const {
            return enabled;
        }
    };
    static std::unordered_set<ReachDistModifier*> modifiers;
    static float last;
    static float apply(float);
    KEXMiscReachDistModule(Module* parent): Module(parent, "kex.misc.reachdist") {}
    virtual void initialize();
};


#endif //KEX_MODULES_MISC_REACHDIST_HPP