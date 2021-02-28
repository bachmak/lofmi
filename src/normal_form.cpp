#include "lofmi/normal_form.h"

namespace Lofmi
{
    NormalForm::NormalForm(std::vector<Bitset> x, Bitset y, OperType type)
    {
        switch (type)
        {
        case OperType::Conjunctive:
            divider = " & ";
            y.flip();
            break;
        
        case OperType::Disjunctive:
            divider = " V ";
            break;
        }

        for (size_t i = 0; i < y.size(); i++)
        {
            if (y[i])
            {
                elem_opers.push_back({ x[i], type });
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const NormalForm& nf)
    {
        for (size_t i = 0; i < nf.elem_opers.size(); i++)
        {
            os << (i == 0 ? "" : nf.divider) << nf.elem_opers[i];
        }
        
        return os;
    }
} // namespace Lofmi
