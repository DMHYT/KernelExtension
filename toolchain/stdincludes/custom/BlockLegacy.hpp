#ifndef KEX_BLOCKLEGACY_HPP
#define KEX_BLOCKLEGACY_HPP


class BlockLegacy {
    public:
    char filler1[104]; // 104
    int tileEntityType; // 108
    char filler2[104]; // 212
    short id; // 214
    float getDestroySpeed() const;
};


#endif //KEX_BLOCKLEGACY_HPP