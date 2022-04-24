#include <stl/string>

#ifndef KEX_ACTORDAMAGESOURCE_HPP
#define KEX_ACTORDAMAGESOURCE_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
    enum ActorCategory: int {};
    enum ActorType: int {};
    class BlockSource;
#endif
#ifndef KEX_MOB_HPP
    enum ActorDamageCause: int {};
#endif
#ifndef KEX_ACTORUNIQUEID_HPP
    class ActorUniqueID {public:};
#endif
#ifndef KEX_BLOCK_HPP
    class Block;
#endif

class ActorDamageSource {
    public:
    void** vtable; // 4
    ActorDamageCause cause; // 8
    // virtual bool isEntitySource() const;
    // virtual bool isChildEntitySource() const;
    // virtual bool isBlockSource() const;
    // virtual bool isFire() const;
    // virtual std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>> getDeathMessage(std::__ndk1::string, Actor*) const;
    // virtual bool getIsCreative() const;
    // virtual bool getIsWorldBuilder() const;
    // virtual ActorUniqueID* getEntityUniqueID() const;
    // virtual ActorType getEntityType() const;
    // virtual ActorCategory getEntityCategories() const;
    // virtual bool getDamagingEntityIsCreative() const;
    // virtual bool getDamagingEntityIsWorldBuilder() const;
    // virtual ActorUniqueID* getDamagingEntityUniqueID() const;
    // virtual ActorType getDamagingEntityType() const;
    // virtual ActorCategory getDamagingEntityCategories() const;
    // virtual ActorDamageSource* clone() const;
    ActorDamageSource(std::__ndk1::string const&);
    ActorDamageSource(ActorDamageCause);
    ActorDamageCause getCause() const;
    void setCause(ActorDamageCause);
    static ActorDamageCause lookupCause(std::__ndk1::string const&);
    static std::__ndk1::string lookupCauseName(ActorDamageCause);
};

class ActorDamageByActorSource : public ActorDamageSource {
    public:
    char something[4]; // 12
    bool entityIsWorldBuilder; // 13
    bool entityIsCreative; // 14 + 2
    ActorUniqueID entityUid; // 24
    ActorType entityType; // 28
    ActorCategory entityCategory; // 32
    std::__ndk1::string someStringFromEntity; // 44
    // virtual bool isEntitySource() const;
    // virtual std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>> getDeathMessage(std::__ndk1::string, Actor*) const;
    // virtual bool getIsCreative() const;
    // virtual bool getIsWorldBuilder() const;
    // virtual ActorUniqueID* getEntityUniqueID() const;
    // virtual ActorType getEntityType() const;
    // virtual ActorCategory getEntityCategories() const;
    // virtual ActorUniqueID* getDamagingEntityUniqueID() const;
    // virtual ActorType getDamagingEntityType() const;
    // virtual ActorDamageByActorSource* clone() const;
    ActorDamageByActorSource(Actor&, ActorDamageCause);
    ActorDamageByActorSource(BlockSource&, ActorDamageCause);
};

class ActorDamageByChildActorSource : public ActorDamageByActorSource {
    public:
    bool damagingEntityIsWorldBuilder; // 45
    bool damagingEntityIsCreative; // 46 + 2
    ActorUniqueID damagingEntityUid; // 56
    ActorType damagingEntityType; // 60
    ActorCategory damagingEntityCategory; // 64
    std::__ndk1::string someStringFromDamagingEntity; // 76
    // virtual bool isChildEntitySource() const;
    // virtual std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>> getDeathMessage(std::__ndk1::string, Actor*) const;
    // virtual bool getDamagingEntityIsCreative() const;
    // virtual bool getDamagingEntityIsWorldBuilder() const;
    // virtual ActorUniqueID* getDamagingEntityUniqueID() const;
    // virtual ActorType getDamagingEntityType() const;
    // virtual ActorCategory getDamagingEntityCategories() const;
    // virtual ActorDamageByChildActorSource* clone() const;
    ActorDamageByChildActorSource(Actor&, Actor&, ActorDamageCause);
    ActorDamageByChildActorSource(BlockSource&, ActorDamageCause);
};

class ActorDamageByBlockSource : public ActorDamageSource {
    public:
    Block* block; // 12
    // virtual bool isBlockSource() const;
    // virtual std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>> getDeathMessage(std::__ndk1::string, Actor*) const;
    // virtual ActorDamageByBlockSource* clone() const;
    ActorDamageByBlockSource(ActorDamageCause);
    ActorDamageByBlockSource(Block const&, ActorDamageCause);
    Block* getBlock() const;
};

class RemovedActorDamageByType : public ActorDamageSource {
    public:
    ActorType actorType; // 12
    // virtual std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>> getDeathMessage(std::__ndk1::string, Actor*) const;
    // virtual ActorType getEntityType() const;
    // virtual RemovedActorDamageByType* clone() const;
    RemovedActorDamageByType(ActorDamageCause, ActorType);
};


#endif //KEX_ACTORDAMAGESOURCE_HPP