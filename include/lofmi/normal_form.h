#pragma once

#include "lofmi/common.h"
#include "lofmi/elem_oper.h"

namespace Lofmi
{
class NormalForm
{
public:
    NormalForm(std::vector<Bitset> x, Bitset y, OperType type);
    friend std::ostream& operator<<(std::ostream& os, const NormalForm& nf);

private:
    std::vector<ElemOper> elem_opers;
    std::string divider;
};
} // namespace Lofmi
