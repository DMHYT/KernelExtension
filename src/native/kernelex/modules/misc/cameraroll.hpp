#include <unordered_set>

#include <mod.h>

#ifndef KEX_MODULES_MISC_CAMERAROLL_HPP
#define KEX_MODULES_MISC_CAMERAROLL_HPP


class KEXMiscCameraRollModule : public Module {
    public:
    struct CameraRollModifier {
        float modifier;
        float lastModifier;
        float modifierToUse;
        float lastAlpha;
        float smoothing;
        bool enabled;
        bool interpolationEnabled;
        CameraRollModifier():
            modifier(0.0f), lastModifier(0.0f), lastAlpha(0.0f), modifierToUse(0.0f), smoothing(0.85f), enabled(false), interpolationEnabled(true) {}
        float interpolate();
    };
    static std::unordered_set<CameraRollModifier*> modifiers;
    static float apply(float);
    KEXMiscCameraRollModule(Module* parent): Module(parent, "kex.misc.cameraroll") {}
    virtual void initialize();
};


#endif //KEX_MODULES_MISC_CAMERAROLL_HPP