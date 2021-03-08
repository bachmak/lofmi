#pragma once

#include "lofmi/common.h"
#include "lofmi/truth_table.h"
#include "lofmi/gray_code.h"

namespace Lofmi
{
class KarnaughMap
{
/*
Класс для представления минимизирующей карты Карно.
Карта Карно — графический способ представления булевых функций с целью их удобной и наглядной ручной минимизации.
Переменные по строкам и столбцам в карте Карно упорядочиваются по коду Грея.
*/
public:
    KarnaughMap(const TruthTable& tt);
    friend std::ostream& operator<<(std::ostream& os, const KarnaughMap& km);
    
private:
    std::vector<GrayCode> rows;
    std::vector<GrayCode> cols;
    BoolMatrix map;

    void FillGraySequence(std::vector<GrayCode>& sequence);
    void FillMap(const TruthTable& tt);
};
} // namespace Lofmi
