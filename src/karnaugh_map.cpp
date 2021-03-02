#include "lofmi/karnaugh_map.h"

namespace Lofmi
{
KarnaughMap::KarnaughMap(const TruthTable& tt)
{
    size_t arg_count = tt.getX().empty() ? 0 : tt.getX()[0].size();

    if (arg_count < 2)
    {
        throw std::invalid_argument("Not enough arguments to build KMap");
    }

    size_t cols_count = Pow2(arg_count / 2);
    size_t rows_count = Pow2(arg_count - arg_count / 2);
    
    rows = std::vector<GrayCode>(rows_count);
    cols = std::vector<GrayCode>(cols_count);
    map = BoolMatrix(rows.size(), std::vector<bool>(cols.size()));

    FillGraySequence(rows);
    FillGraySequence(cols);
    FillMap(tt);
}

std::ostream& operator<<(std::ostream& os, const KarnaughMap& km)
{
    if (km.rows.empty() || km.cols.empty())
    {
        return os;
    }

    size_t row_bits_size = km.rows.back().getCode().size();
    size_t col_bits_size = km.cols.back().getCode().size();

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

void KarnaughMap::FillGraySequence(std::vector<GrayCode>& sequence)
{
    for (size_t i = 0; i < sequence.size(); i++)
    {
        sequence[i] = GrayCode(i);
    }
}

void KarnaughMap::FillMap(const TruthTable& tt)
{
    size_t row_count = rows.back().getCode().size();
    size_t col_count = cols.back().getCode().size();

    for (size_t i = 0; i < rows.size(); i++)
    {
        for (size_t j = 0; j < cols.size(); j++)
        {
            Bitset row_bitset = rows[i].getCode();
            Bitset col_bitset = cols[j].getCode();

            row_bitset.resize(row_count, false);
            col_bitset.resize(col_count, false);
            auto conc_bitset = Concatenate(row_bitset, col_bitset);
            map[i][j] = tt.getValue(conc_bitset);
        }
    }
}

} // namespace Lofmi
