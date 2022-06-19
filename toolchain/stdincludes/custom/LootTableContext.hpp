#include <stl/string>

#include <enums.hpp>

#ifndef KEX_LOOTTABLECONTEXT_HPP
#define KEX_LOOTTABLECONTEXT_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
#ifndef KEX_ACTORDAMAGESOURCE_HPP
    class ActorDamageSource;
#endif
#ifndef KEX_LEVEL_HPP
    class Level;
#endif
#ifndef KEX_PLAYER_HPP
    class Player;
#endif
#ifndef KEX_LOOTTABLE_HPP
    class LootTable;
#endif

class LootTableContext {
    public:
    char filler[56];
    LootTableContext(float, Level*, Actor*, Player*, const ActorDamageSource*, float);
    Actor* getThisEntity() const;
    std::__ndk1::string getOriginalItemName() const;
    void removeVisitedTable(const LootTable*);
    Level* getLevel() const;
    float getExplosionRadius() const;
    float getLuck() const;
    Player* getKillerPlayer() const;
    void addVisitedTable(const LootTable*);
    Actor* getKillerPet() const;
    Actor* getKillerEntity() const;
    ActorDamageSource* getDeathSource() const;
    void setOriginalItemName(const std::__ndk1::string&);
    Actor* getEntity(ActorTarget) const;
    class Builder {
        public:
        char filler[36];
        Builder(Level*);
        void withExplosionRadius(float);
        void withThisEntity(Actor*);
        void withLuck(float);
        void withOriginalItemName(std::__ndk1::string&);
        void withKillerPlayer(Player*);
        LootTableContext create() const;
        void withDeathSource(const ActorDamageSource*);
    };
};


#endif //KEX_LOOTTABLECONTEXT_HPP