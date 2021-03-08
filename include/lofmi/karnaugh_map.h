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
    std::vector<Bitset> rows;
    std::vector<Bitset> cols;
    BoolMatrix map;

    BoolMatrix TruthTableToKarnaughMap(const TruthTable& tt) const;
};
} // namespace Lofmi
