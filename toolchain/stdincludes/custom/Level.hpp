#ifndef KEX_LEVEL_HPP
#define KEX_LEVEL_HPP


#ifndef KEX_BIOME_HPP
    class BiomeRegistry;
#endif
#ifndef KEX_HITRESULT_HPP
    class HitResult;
#endif
class Random;
class LevelStorage;
#ifndef KEX_LOOTTABLE_HPP
    class LootTables;
#endif
#ifndef KEX_TICKINGAREASMANAGER_HPP
    class TickingAreasManager;
#endif

enum GeneratorType {
    OLD, DEFAULT, SUPERFLAT
};

class LevelData {
    public:
    GeneratorType getGenerator() const;
};

class Level {
    public:
    bool isClientSide() const;
    Random* getRandom() const;
    LootTables* getLootTables();
    TickingAreasManager* getTickingAreasMgr();
    LevelStorage* getLevelStorage() const;
    LevelData* getLevelData() const;
    BiomeRegistry* getBiomeRegistry() const;
    HitResult* getHitResult();
};

class ServerLevel : public Level {
    public:
};


#endif //KEX_LEVEL_HPP