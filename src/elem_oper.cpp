#include "lofmi/elem_oper.h"

namespace Lofmi
{
    ElemOper::ElemOper(Bitset bitset, OperType type)
    {
        switch (type)
        {
        case OperType::Conjunctive:
            divider = " V ";
            bitset.flip();
            break;
        
        case OperType::Disjunctive:
            divider = " & ";
        }

        this->bitset = std::move(bitset);
    }

    std::ostream& operator<<(std::ostream& os, const ElemOper& eo)
    {
        os << '(';

        for (size_t i = 0; i < eo.bitset.size(); i++)
        {
            os << (i == 0 ? "" : eo.divider)
               << (eo.bitset[i] ? "" : "~")
               << 'x' << i;
        }
        
        return os << ')';
    }
} // namespace Lofmi
