#ifndef KEX_BLOCK_HPP
#define KEX_BLOCK_HPP


#ifndef KEX_BLOCKLEGACY_HPP
    class BlockLegacy;
#endif

#ifndef KEX_ITEMSTATE_HPP
    class ItemState;
#endif

class Block {
    public:
    void** vtable; // 4
    int data; // 8
    BlockLegacy* legacy; // 12
    unsigned int getRuntimeId() const;
    int getVariant() const;
    float getDestroySpeed() const;
    float getFriction() const;
    unsigned char getLight() const;
    unsigned char getLightEmission() const;
    template<typename T> T getState(const ItemState&) const;
    template<typename T> Block* setState(const ItemState&, T) const;
};

namespace BlockStatesRegistry {
    Block* getBlockByRuntimeId(int id);
}


#endif //KEX_BLOCK_HPP