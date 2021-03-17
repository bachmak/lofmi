#pragma once

#include "lofmi/common.h"
#include "lofmi/truth_table.h"
#include "lofmi/gray_code.h"

namespace Lofmi
{
/*
Класс для представления минимизирующей карты Карно.
Карта Карно — графический способ представления булевых функций с целью их удобной и наглядной ручной минимизации.
Переменные по строкам и столбцам в карте Карно упорядочиваются по коду Грея.
*/
class KarnaughMap
{
public:
    KarnaughMap(const TruthTable& tt);
    const BoolMatrix& getMatrix() const;
    friend std::ostream& operator<<(std::ostream& os, const KarnaughMap& km);

private:
    std::vector<Bitset> rows;
    std::vector<Bitset> cols;
    BoolMatrix map;

private:
    BoolMatrix TruthTableToKarnaughMap(const TruthTable& tt) const;
};
} // namespace Lofmi
