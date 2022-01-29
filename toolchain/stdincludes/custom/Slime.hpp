#include <Mob.hpp>

#ifndef KEX_SLIME_HPP
#define KEX_SLIME_HPP


class Monster : public Mob {
    public:
};


class Slime : public Monster {
    public:
    // virtual void* getSquishSound();
    // virtual void setSlimeSize(int);
    // virtual void doPlayJumpSound();
    // virtual void doPlayLandSound();
    // virtual void playJumpSound();
    // virtual void playLandSound();
    // virtual float decreaseSquish();
    // virtual void createChild(int);
    bool justJumped();
    int getSquishValue() const;
    int getSlimeSize() const;
    int getTargetSquish() const;
    int getOldSquishValue() const;
    bool justLanded();
};

class LavaSlime : public Slime {
    public:
};


#endif //KEX_SLIME_HPP