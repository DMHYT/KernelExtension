#include <stl/string>

#include <enums.hpp>

#ifndef KEX_ACTORDAMAGESOURCE_HPP
#define KEX_ACTORDAMAGESOURCE_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
    class BlockSource;
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
    // virtual ActorUniqueID getEntityUniqueID() const;
    // virtual ActorType getEntityType() const;
    // virtual int getEntityCategories() const;
    // virtual bool getDamagingEntityIsCreative() const;
    // virtual bool getDamagingEntityIsWorldBuilder() const;
    // virtual ActorUniqueID getDamagingEntityUniqueID() const;
    // virtual ActorType getDamagingEntityType() const;
    // virtual int getDamagingEntityCategories() const;
    // virtual ActorDamageSource* clone() const;
    ActorDamageSource(const std::__ndk1::string&);
    ActorDamageSource(ActorDamageCause);
    ActorDamageCause getCause() const;
    void setCause(ActorDamageCause);
    static ActorDamageCause lookupCause(const std::__ndk1::string&);
    static std::__ndk1::string lookupCauseName(ActorDamageCause);
};

class ActorDamageByActorSource : public ActorDamageSource {
    public:
    BlockSource* blockSource; // 12
    bool entityIsWorldBuilder; // 13
    bool entityIsCreative; // 14 + 2
    ActorUniqueID entityUid; // 24
    ActorType entityType; // 28
    int entityCategory; // 32
    std::__ndk1::string someStringFromEntity; // 44
    // virtual bool isEntitySource() const;
    // virtual std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>> getDeathMessage(std::__ndk1::string, Actor*) const;
    // virtual bool getIsCreative() const;
    // virtual bool getIsWorldBuilder() const;
    // virtual ActorUniqueID getEntityUniqueID() const;
    // virtual ActorType getEntityType() const;
    // virtual int getEntityCategories() const;
    // virtual ActorUniqueID getDamagingEntityUniqueID() const;
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
    int damagingEntityCategories; // 64
    std::__ndk1::string someStringFromDamagingEntity; // 76
    // virtual bool isChildEntitySource() const;
    // virtual std::__ndk1::pair<std::__ndk1::string, std::__ndk1::vector<std::__ndk1::string>> getDeathMessage(std::__ndk1::string, Actor*) const;
    // virtual bool getDamagingEntityIsCreative() const;
    // virtual bool getDamagingEntityIsWorldBuilder() const;
    // virtual ActorUniqueID getDamagingEntityUniqueID() const;
    // virtual ActorType getDamagingEntityType() const;
    // virtual int getDamagingEntityCategories() const;
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
    ActorDamageByBlockSource(const Block&, ActorDamageCause);
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