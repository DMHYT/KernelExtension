#ifndef KEX_BLOCK_HPP
#define KEX_BLOCK_HPP


#ifndef KEX_BLOCKLEGACY_HPP
    class BlockLegacy;
#endif

class Block {
    public:
    void** vtable; // 4
    int data; // 8
    BlockLegacy* legacy; // 12
    unsigned int getRuntimeId() const;
    int getVariant() const;
};


#endif //KEX_BLOCK_HPP