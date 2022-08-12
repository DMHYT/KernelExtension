#include <commontypes.hpp>

#ifndef KEX_LEVELCHUNK_HPP
#define KEX_LEVELCHUNK_HPP


class BlockActor;

class LevelChunk {
    public:
    const ChunkPos& getPosition() const;
    void _placeBlockEntity(stl::shared_ptr<BlockActor>);
};


#endif //KEX_LEVELCHUNK_HPP