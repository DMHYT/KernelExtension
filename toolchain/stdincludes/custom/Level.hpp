#ifndef KEX_LEVEL_HPP
#define KEX_LEVEL_HPP


class Random;
class LevelStorage;
#ifndef KEX_LOOTTABLE_HPP
    class LootTables;
#endif
#ifndef KEX_TICKINGAREASMANAGER_HPP
    class TickingAreasManager;
#endif

class Level {
    public:
    bool isClientSide() const;
    Random* getRandom() const;
    LootTables* getLootTables();
    TickingAreasManager* getTickingAreasMgr();
    LevelStorage* getLevelStorage() const;
};

class ServerLevel : public Level {
    public:
};


#endif //KEX_LEVEL_HPP