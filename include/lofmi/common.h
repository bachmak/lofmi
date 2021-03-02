#pragma once

#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <vector>
#include <iomanip>

namespace Lofmi
{
    using Bitset = boost::dynamic_bitset<>;
    using BoolMatrix = std::vector<std::vector<bool>>;
    enum class OperType
    {
        Conjunctive, Disjunctive
    };
} // namespace Lofmi
