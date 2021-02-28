#include "lofmi/truth_table.h"
#include "lofmi/utils.h"

#include <cmath>
#include <stdexcept>
#include <utility>
#include <iomanip>

namespace Lofmi
{
    TruthTable::TruthTable(Bitset bits)
    {
        auto [is_power_of_2, power_of_2] = IsPowerOf2(bits.size());
        
        if (!is_power_of_2)
        {
            throw std::invalid_argument("Size of y(x) is not a power of 2");
        }

        y = std::move(bits);
        x = std::vector<Bitset>(y.size());

        for (size_t i = 0; i < x.size(); i++)
        {
            x[i] = Bitset(power_of_2 - 1, i);
        }
    }

    TruthTable::TruthTable(const std::vector<bool>& bits)
    {
        Bitset bitset(bits.size());

        for (size_t i = 0; i < bits.size(); i++)
        {
            bitset[i] = bits[i];
        }
        
        *this = TruthTable(std::move(bitset));
    }

    std::istream& operator>>(std::istream& is, TruthTable& tt)
    {
        Bitset bitset;
        is >> bitset;
        tt = TruthTable(std::move(bitset));
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const TruthTable& tt)
    {
        int cell_width = 8;
        if (tt.x.empty())
        {
            return os;
        }

        for (size_t i = 1; i <= tt.x[0].size(); i++)
        {
            os << std::setw(cell_width - 1) << 'x' << i;
        }
        os << std::setw(cell_width) << 'y' << "\n\n";

        for (size_t i = 0; i < tt.y.size(); i++)
        {
            for (size_t j = 0; j < tt.x[i].size(); j++)
            {
                os << std::setw(cell_width) << tt.x[i][j];
            }
            os << std::setw(cell_width) << tt.y[i] << "\n\n";
        }
        
        return os;
    }

    const std::vector<Bitset>& TruthTable::getX() const
    {
        return x;
    }

    const Bitset& TruthTable::getY() const
    {
        return y;
    }

    NormalForm TruthTable::buildCNF() const
    {
        return NormalForm(x, y, OperType::Conjunctive);
    }

    NormalForm TruthTable::buildDNF() const
    {
        return NormalForm(x, y, OperType::Disjunctive);
    }
} // namespace Lofmi
