#pragma once

#include "lofmi/common.h"
#include "lofmi/utils.h"

namespace Lofmi
{
/*
Класс со статическими методами для построения чисел и последовательностей чисел по коду Грея
*/

class GrayCode
{
public:
    GrayCode() = delete;
    static Bitset GrayCodeValue(size_t dec_seq_number);
    static std::vector<Bitset> GrayCodeSequence(size_t seq_size);

private:
    static bool GrayCodeBit(int gray_seq_num, int bit_pos);                                        // метод определения значения бита в коде Грея по последовательному номеру кода и позиции бита 
};
} // namespace Lofmi
