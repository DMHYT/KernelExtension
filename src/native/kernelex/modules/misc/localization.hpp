#include <mod.h>

#ifndef KEX_MODULES_MISC_LOCALIZATION_HPP
#define KEX_MODULES_MISC_LOCALIZATION_HPP


class KEXMiscLocalizationModule : public Module {
    public:
    KEXMiscLocalizationModule(Module* parent): Module(parent, "kex.misc.localization") {}
    virtual void initialize();
};


#endif //KEX_MODULES_MISC_LOCALIZATION_HPP