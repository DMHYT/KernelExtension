#include <jni.h>

#include "module.hpp"


bool KEXBlocksModule::RenderConditions::WeightedRandomCondition::apply(BlockSource*, const Block&, const BlockPos& pos) {
    unsigned long long n = 1618033988ull;
    n ^= (unsigned long long) 1619 * pos.x;
    n ^= (unsigned long long) 31337 * pos.y;
    n ^= (unsigned long long) 6971 * pos.z;
    unsigned long long n1 = (n >> 32) ^ (n & 0xFFFFFFFFull);
    double fval1 = (n1 * (double) n1 * 60493 - 2140704);
    unsigned long long bits = *(unsigned long long*) &fval1;
    unsigned long long bits1 = (bits >> 32) ^ (bits & 0xFFFFFFFFull);
    int pos_factor = (((pos.x % 16) + 1619) * ((pos.y % 16) + 31337) * ((pos.z % 16) + 6971));
    unsigned long long result = bits1 + pos_factor;
    float resultf = (result & 0xFFFFFFull) / ((float) 0xFFFFFFull);
    resultf *= weightSum;
    int chosen = (int) resultf + 1;
    return chosen >= minValue && chosen <= maxValue;
}


extern "C" JNIEXPORT jlong JNICALL
Java_vsdum_kex_japi_internal_block_model_WeightedRandomRenderCondition_nativeNew
(JNIEnv*, jclass, jint min, jint max, jint sum)
{
    return (jlong) new KEXBlocksModule::RenderConditions::WeightedRandomCondition(min, max, sum);
}