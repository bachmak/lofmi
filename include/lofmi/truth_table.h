#pragma once

#include "lofmi/common.h"

#include <vector>

namespace Lofmi
{

class TruthTable
{
public:
    TruthTable() = default;
    TruthTable(Bitset y);
    TruthTable(const std::vector<bool>& bits);
    friend std::istream& operator>>(std::istream& is, TruthTable& tt);
    friend std::ostream& operator<<(std::ostream& os, const TruthTable& tt);

private:
    std::vector<Bitset> x;
    Bitset y;
};
} // namespace Lofmi