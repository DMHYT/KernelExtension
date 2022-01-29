#ifndef KEX_MOBEFFECT_HPP
#define KEX_MOBEFFECT_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
class AttributeBuff;
class AttributeModifier;
#ifndef KEX_MOBEFFECTINSTANCE_HPP
    class MobEffectInstance;
#endif
class ResourcePackManager;

class MobEffect {
    public:
    // virtual MobEffectInstance* applyEffects(Actor*, int, int) const;
    // virtual void removeEffects(Actor*);
    // virtual MobEffectInstance* applyInstantaneousEffect(Actor*, Actor*, Actor*, int, float) const;
    // virtual bool isInstantaneous() const;
    // virtual float getAttributeModifierValue(int, AttributeModifier const&) const;
    static void shutdownEffects();
    void* _createTemporalBuff(AttributeBuff const&, int, int) const;
    void clearTemporalBuffs();
    void* getComponentName() const;
    void* getColor() const;
    void* getIcon() const;
    bool isVisible() const;
    //addAttributeModifier
    void clearAttributeModifiers();
    //setDurationAmplifier
    //addAttributeBuff
    void* getDescriptionId() const;
    bool isDisabled() const;
    void* viewAttributeModifiers() const;
    unsigned int getId() const;
    void* createInstantBuff(AttributeBuff const&, int, float) const;
    //setValueAmplifier
    void* getDurationModifier() const;
    void* getIconName() const;
    bool hasIcon() const;
    void* formatDuration(MobEffectInstance const*);
    void initEffects(ResourcePackManager*);
    void* _createAttributeModifier(AttributeModifier const&, int) const;
    //getByName
    bool isHarmful() const;
    void* getResourceName() const;
    static MobEffect* getById(int);
};


#endif //KEX_MOBEFFECT_HPP