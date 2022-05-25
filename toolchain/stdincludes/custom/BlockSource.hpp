#ifndef KEX_BLOCKSOURCE_HPP
#define KEX_BLOCKSOURCE_HPP


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
    BlockActor* getBlockEntity(BlockPos const&);
    Level* getLevel() const;
};


#endif //KEX_BLOCKSOURCE_HPP