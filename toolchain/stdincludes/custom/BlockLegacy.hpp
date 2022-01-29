#ifndef KEX_BLOCKLEGACY_HPP
#define KEX_BLOCKLEGACY_HPP


class BlockLegacy {
    public:
    // char filler1[184]; // 184
    // float destroyTime; // 188
    // char filler2[24]; // 212
    // short id; // 214
    char filler[212]; // 212
    short id; // 214
    float getDestroySpeed() const;
};


#endif //KEX_BLOCKLEGACY_HPP