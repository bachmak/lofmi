#pragma once

#include "lofmi/common.h"
#include "lofmi/utils.h"

namespace Lofmi
{
class GrayCode
{
public:
    GrayCode(size_t gray_seq_number);
    friend std::ostream& operator<<(std::ostream& os, const GrayCode& gc);

private:
    Bitset bits;
    
    static bool GrayBit(int gray_seq_num, int bit_pos);
};
} // namespace Lofmi
