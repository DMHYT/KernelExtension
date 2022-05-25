#ifndef KEX_LEVEL_HPP
#define KEX_LEVEL_HPP


class Random;
#ifndef KEX_LOOTTABLE_HPP
    class LootTables;
#endif

class Level {
    public:
    bool isClientSide() const;
    Random* getRandom() const;
    LootTables* getLootTables();
};

class ServerLevel : public Level {
    public:
};


#endif //KEX_LEVEL_HPP