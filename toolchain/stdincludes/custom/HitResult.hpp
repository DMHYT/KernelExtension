#include <commontypes.hpp>

#ifndef KEX_HITRESULT_HPP
#define KEX_HITRESULT_HPP


enum HitResultType: int {
    TILE = 0,
    ENTITY_OUT_OF_RANGE = 2,
    NO_HIT = 3
};

class HitResult {
    public:
    Vec3 startPos; // 12
    Vec3 rayDir; // 24
    HitResultType type; // 28
    unsigned char side; // 29 + 3
    BlockPos blockPos; // 44
    Vec3 pos; // 56
    char entityRefTraits[24]; // 80
    bool isHitLiquid; // 81
    unsigned char liquidSide; // 82 + 2
    BlockPos liquidBlockPos; // 96
    Vec3 liquidPos; // 108
    bool indirectHit; // 109 + 3
};


#endif //KEX_HITRESULT_HPP