#ifndef KEX_PLAYER_HPP
#define KEX_PLAYER_HPP


#ifndef KEX_MOB_HPP
    class Mob { public: };
#endif

class Player : public Mob {
    public:
};

class LocalPlayer : public Player {
    public:
};
class ServerPlayer : public Player {
    public:
};


#endif //KEX_PLAYER_HPP