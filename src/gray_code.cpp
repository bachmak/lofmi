#include "lofmi/gray_code.h"

namespace Lofmi
{
// метод определения значения бита в коде Грея по последовательному номеру кода и позиции бита
bool GrayCode::GrayCodeBit(int gray_seq_num, int bit_pos)
{
    double lhs = std::abs(
        gray_seq_num % Pow2(2 + bit_pos) - (Pow2(2 + bit_pos) - 1) / 2.0
    );

    double rhs = (Pow2(2 + bit_pos) - 1) / 4.0;

    return lhs <= rhs;
}

Bitset GrayCode::GrayCodeValue(size_t dec_seq_number)
{
    Bitset result(BitsetSizeByIndex(dec_seq_number));
    
    for (size_t i = 0; i < result.size(); i++)
    {
        result[i] = GrayCodeBit(dec_seq_number, i);
    }

    return result;
}

std::vector<Bitset> GrayCode::GrayCodeSequence(size_t seq_size)
{
    std::vector<Bitset> result(seq_size);

    for (size_t i = 0; i < result.size(); i++)
    {
        result[i] = GrayCodeValue(i);
    }
    
    return result;
}
} // namespace Lofmi
