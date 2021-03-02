#pragma once

#include "lofmi/common.h"

#include <utility>
#include <cmath>

namespace Lofmi
{
    template <typename T>
    inline std::pair<bool, int> IsPowerOf2(T val)
    {
        int power_of_2 = 0;
        double fract_part = std::frexp(val, &power_of_2);
        return { fract_part == 0.5, power_of_2 };
    }

    template <typename T>
    inline int NextPowerOf2(T val)
    {
        return static_cast<int>(std::pow(2, std::ceil(std::log2(val))));  
    }

    template <typename T>
    inline size_t BitsetSizeByIndex(T val)
    {
        return static_cast<size_t>(std::log2(NextPowerOf2(val + 1)));
    }

    template <typename T>
    inline int Pow2(T val)
    {
        return static_cast<int>(std::pow(2, val));
    }

    inline bool operator<(const Bitset& lhs, const Bitset& rhs)
    {
        return lhs.to_ulong() < rhs.to_ulong();
    }

} // namespace Lofmi
