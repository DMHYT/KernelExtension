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
#ifndef KEX_DIMENSION_HPP
    class Dimension;
#endif
#ifndef KEX_LEVEL_HPP
    class Level;
#endif

class BlockSource {
    public:
    Block* getBlock(const BlockPos&) const;
    BlockActor* getBlockEntity(const BlockPos&);
    Level* getLevel() const;
    Dimension* getDimension() const;
    void fireBlockEntityChanged(BlockActor&);
};


#endif //KEX_BLOCKSOURCE_HPP