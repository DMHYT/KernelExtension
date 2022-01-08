#ifndef KEX_BLOCK_HPP
#define KEX_BLOCK_HPP


#ifndef KEX_BLOCKLEGACY_HPP
    class BlockLegacy;
#endif

class Block {
    public:
    char filler1[4]; // 4
    int data; // 8
    BlockLegacy* legacy; // 12
};


#endif //KEX_BLOCK_HPP