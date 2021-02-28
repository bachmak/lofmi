#pragma once

#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <vector>

namespace Lofmi
{
    using Bitset = boost::dynamic_bitset<>;

    enum class OperType
    {
        Conjunctive, Disjunctive
    };
} // namespace Lofmi
