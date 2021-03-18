#include "lofmi/karnaugh/map.h"

namespace Lofmi
{
namespace Karnaugh
{
Map::Map(const TruthTable& tt)
{
    size_t arg_count = tt.getX().empty() ? 0 : tt.getX()[0].size();

    if (arg_count < 2)
    {
        throw std::invalid_argument("Not enough arguments to build KMap");
    }

    size_t cols_count = Pow2(arg_count / 2);
    size_t rows_count = Pow2(arg_count - arg_count / 2);
    
    rows = GrayCode::GrayCodeSequence(rows_count);
    cols = GrayCode::GrayCodeSequence(cols_count);
    map = TruthTableToKarnaughMap(tt);
}

const BoolMatrix& Map::getMatrix() const
{
    return map;
}

const Bitset& Map::getCode(int x, int y) const
{
    if (x >= cols.size() || y >= rows.size() || x < 0 || y < 0)
    {
        throw std::out_of_range("Index is out of Karnaugh map");
    }

    return Concatenate(rows[y], cols[x]);
}

std::ostream& operator<<(std::ostream& os, const Map& km)
{
    if (km.rows.empty() || km.cols.empty())
    {
        return os;
    }

    size_t row_bits_size = km.rows.back().size();
    size_t col_bits_size = km.cols.back().size();

    os << "  " << std::setfill(' ') << std::setw(row_bits_size) << " " << "  ";

    for (size_t i = 0; i < km.cols.size(); i++)
    {
        os << "  " << std::setfill('0') << std::setw(col_bits_size)
           << km.cols[i] << "  ";
    }
    os << "\n\n";

    for (size_t i = 0; i < km.rows.size(); i++)
    {
        os << "  " << std::setfill('0') << std::setw(row_bits_size)
            << km.rows[i] << "  ";

        for (size_t j = 0; j < km.cols.size(); j++)
        {
            os << "  " << std::setfill(' ') << std::setw(col_bits_size) 
            << km.map[i][j] << "  "; 
        }

        os << "\n\n";
    }

    return os;
}

BoolMatrix Map::TruthTableToKarnaughMap(const TruthTable& tt) const
{
    BoolMatrix result(rows.size(), std::vector<bool>(cols.size()));

    size_t row_count = rows.back().size();
    size_t col_count = cols.back().size();

    for (size_t i = 0; i < rows.size(); i++)
    {
        for (size_t j = 0; j < cols.size(); j++)
        {
            Bitset row_bitset = rows[i];
            Bitset col_bitset = cols[j];

            row_bitset.resize(row_count, false);
            col_bitset.resize(col_count, false);
            auto conc_bitset = Concatenate(row_bitset, col_bitset);
            result[i][j] = tt.getValue(conc_bitset);
        }
    }

    return result;
}
} // namespace Karnaugh
} // namespace Lofmi
