#pragma once
#include <cstdint>
namespace Prob {
  
    extern uint32_t Rand;
    void InitRand();
    inline float Random() {
        Rand ^= Rand << 13;
        Rand ^= Rand >> 17;
        Rand ^= Rand << 5;
        const float fMax = 4294967295.0f;
        return Rand * (1.0f / fMax);
    }

    inline int RandInt(int low, int high) {
        return low + int(Random() * (high - low + 1));
    }
}