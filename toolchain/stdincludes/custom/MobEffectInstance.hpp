#ifndef KEX_MOBEFFECTINSTANCE_HPP
#define KEX_MOBEFFECTINSTANCE_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
class CompoundTag;
enum Difficulty: int {};

class MobEffectInstance {
    public:
    MobEffectInstance(unsigned int, int, int);
    MobEffectInstance(unsigned int, int, int, bool, bool, bool);
    MobEffectInstance(unsigned int, int, int, int, int, int, bool, bool, bool);
    MobEffectInstance(unsigned int, int);
    MobEffectInstance(unsigned int);
    MobEffectInstance();
    //getColorValue
    void* getSplashEffect() const;
    void* getLingerDuration() const;
    void _setVisibility();
    void* toString() const;
    bool isNoCounter() const;
    bool isAmbient() const;
    int getAmplifier() const;
    //areAllEffectsAmbient
    void* getDisplayName() const;
    void _tickDownDuration();
    void setNoCounter(bool);
    bool operator!=(MobEffectInstance const&) const;
    void* getDescriptionId() const;
    void* getSplashDuration() const;
    void setDifficultyDuration(Difficulty, int) const;
    void* applyEffects(Actor*) const;
    bool operator<(MobEffectInstance const&) const;
    void update(MobEffectInstance const&);
    bool isEffectVisible() const;
    void tick(Actor*);
    void* save() const;
    int getDifficultyDuration(Difficulty) const;
    void* getComponentName() const;
    void setDuration(int);
    void* removeEffects(Actor*) const;
    int getDuration() const;
    void load(CompoundTag const&);
    unsigned int getId() const;
    bool displaysOnScreenTextureAnimation() const;
};


#endif //KEX_MOBEFFECTINSTANCE_HPP