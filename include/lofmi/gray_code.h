#pragma once

#include "lofmi/common.h"
#include "lofmi/utils.h"

namespace Lofmi
{
/*
Класс для представления кодовых комбинаций, составляемых по коду Грея.
*/
class GrayCode
{
public:
    GrayCode() = default;
    GrayCode(size_t gray_seq_number);                                                   // конструктор по десятичному числу
    friend std::ostream& operator<<(std::ostream& os, const GrayCode& gc);
    const Bitset& getCode() const;
    
private:
    Bitset bits;
    
    bool GrayBit(int gray_seq_num, int bit_pos);                                        // метод определения значения бита в коде Грея по последовательному номеру кода и позиции бита 
};
} // namespace Lofmi
