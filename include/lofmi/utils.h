#pragma once

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
        return std::pow(2, std::ceil(std::log2(val)));  
    }

} // namespace Lofmi
