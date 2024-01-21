#include <commontypes.hpp>

#ifndef KEX_LEVELCHUNK_HPP
#define KEX_LEVELCHUNK_HPP


#ifndef KEX_BIOME_HPP
    class Biome;
#endif
#ifndef KEX_DIMENSION_HPP
    class Dimension;
#endif

class LevelChunk {
    public:
    char filler[5432];
    LevelChunk(Dimension&, const ChunkPos&, bool);
    ~LevelChunk();
    const ChunkPos& getPosition() const;
    Biome* getBiome(const ChunkBlockPos&) const;
};


#endif //KEX_LEVELCHUNK_HPP