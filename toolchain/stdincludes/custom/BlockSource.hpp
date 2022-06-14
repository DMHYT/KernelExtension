#ifndef KEX_BLOCKSOURCE_HPP
#define KEX_BLOCKSOURCE_HPP


#ifndef KEX_BLOCK_HPP
    class Block;
#endif
#ifndef KEX_BLOCKACTOR_HPP
    class BlockActor;
#endif
#ifndef KEX_BLOCKPOS_HPP
    class BlockPos;
#endif
#ifndef KEX_LEVEL_HPP
    class Level;
#endif

class BlockSource {
    public:
    Block* getBlock(BlockPos const&) const;
    BlockActor* getBlockEntity(BlockPos const&);
    Level* getLevel() const;
};


#endif //KEX_BLOCKSOURCE_HPP