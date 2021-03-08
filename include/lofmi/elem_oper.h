#pragma once

#include "lofmi/common.h"

namespace Lofmi
{
/*  
Класс для представления элементарной операции (конъюнкции или дизъюнкции),
используемой для составления нормальной формы (КНФ или ДНФ) логической функции
*/
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
