#include "lofmi/gray_code.h"

namespace Lofmi
{
bool GrayCode::GrayBit(int gray_seq_num, int bit_pos)
{
    double lhs = std::abs(
        gray_seq_num % Pow2(2 + bit_pos) - (Pow2(2 + bit_pos) - 1) / 2.0
    );

    double rhs = (Pow2(2 + bit_pos) - 1) / 4.0;

    return lhs <= rhs;
}

GrayCode::GrayCode(size_t gray_seq_num) : 
    bits{ Bitset(BitsetSizeByIndex(gray_seq_num)) }
{
    for (size_t i = 0; i < bits.size(); i++)
    {
        bits[i] = GrayBit(gray_seq_num, i);
    }
}

std::ostream& operator<<(std::ostream& os, const GrayCode& gc)
{
    for (int i = gc.bits.size() - 1; i >= 0; i--)
    {
        os << gc.bits[i];
    }
    return os;
}

const Bitset& GrayCode::getCode() const
{
    return bits;
}
} // namespace Lofmi
