#ifndef KEX_GAMEMODE_HPP
#define KEX_GAMEMODE_HPP


#ifndef KEX_PLAYER_HPP
    class Player;
#endif

class GameMode {
    public:
    char filler1[4];
    Player* player;
};


#endif //KEX_GAMEMODE_HPP