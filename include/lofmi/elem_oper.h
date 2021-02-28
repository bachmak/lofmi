#pragma once

#include "lofmi/common.h"

namespace Lofmi
{
class ElemOper
{
public:
    ElemOper(Bitset bitset, OperType type);
    friend std::ostream& operator<<(std::ostream& os, const ElemOper& eo);

private:
    Bitset bitset;
    std::string divider;
};
} // namespace Lofmi
