#pragma once

#include "lofmi/common.h"
#include "lofmi/normal_form.h"

#include <map>

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
    const std::vector<Bitset>& getX() const;
    const Bitset& getY() const;
    bool getValue(const Bitset& x) const;
    NormalForm buildDNF() const;
    NormalForm buildCNF() const;

private:
    std::vector<Bitset> x;
    Bitset y;
    std::map<Bitset, bool> table;
};
} // namespace Lofmi
