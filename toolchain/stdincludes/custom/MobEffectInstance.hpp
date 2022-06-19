#include <stl/string>
#include <stl.h>

#include <enums.hpp>

#ifndef KEX_MOBEFFECTINSTANCE_HPP
#define KEX_MOBEFFECTINSTANCE_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
class CompoundTag;

class MobEffectInstance {
    public:
    unsigned int id; // 4
    int durationPeaceful; // 8
    int durationEasy; // 12
    int durationNormal; // 16
    int durationHard; // 20
    int amplifier; // 24
    bool _displaysOnScreenTextureAnimation; // 25
    bool _isAmbient; // 26
    bool _isNoCounter; // 27
    bool _isEffectVisible; // 28
    char filler[12]; // 40
    MobEffectInstance(unsigned int id, int duration, int amplifier);
    MobEffectInstance(unsigned int id, int duration, int amplifier, 
                      bool isAmbient, bool isVisible, bool displaysOnScreenTextureAnimation);
    MobEffectInstance(unsigned int id, int durationPeaceful, 
                      int durationEasy, int durationNormal, int durationHard, int amplifier,
                      bool isAmbient, bool isVisible, bool displaysOnScreenTextureAnimation);
    MobEffectInstance(unsigned int id, int duration);
    MobEffectInstance(unsigned int id);
    MobEffectInstance();
    //getColorValue
    void* getSplashEffect() const;
    int getLingerDuration() const;
    void _setVisibility();
    void* toString() const;
    bool isNoCounter() const;
    bool isAmbient() const;
    int getAmplifier() const;
    //areAllEffectsAmbient
    stl::string getDisplayName() const;
    void _tickDownDuration();
    void setNoCounter(bool);
    bool operator!=(const MobEffectInstance&) const;
    stl::string getDescriptionId() const;
    int getSplashDuration() const;
    void setDifficulityDuration(Difficulty, int);
    void* applyEffects(Actor*) const;
    bool operator<(const MobEffectInstance&) const;
    void update(const MobEffectInstance&);
    bool isEffectVisible() const;
    void tick(Actor*);
    void* save() const;
    int getDifficulityDuration(Difficulty) const;
    bool hasDifficulityDuration(Difficulty) const;
    void* getComponentName() const;
    void setDuration(int);
    void* removeEffects(Actor*) const;
    int getDuration() const;
    void load(const CompoundTag&);
    int getId() const;
    bool displaysOnScreenTextureAnimation() const;
};


#endif //KEX_MOBEFFECTINSTANCE_HPP