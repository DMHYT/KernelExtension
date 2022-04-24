#ifndef KEX_ACTORTESTS_HPP
#define KEX_ACTORTESTS_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif

class ActorHasEquipmentTest {
    public:
    char filler[12]; // 12
    int id; // 16
};

class FilterContext {
    public:
    char filler[4]; // 4
    Actor* actor;
};


#endif //KEX_ACTORTESTS_HPP