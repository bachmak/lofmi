#pragma once

#include "lofmi/common.h"
#include "lofmi/truth_table.h"
#include "lofmi/gray_code.h"

namespace Lofmi
{
namespace Karnaugh
{  
/*
Класс для представления минимизирующей карты Карно.
Карта Карно — графический способ представления булевых функций с целью их удобной и наглядной ручной минимизации.
Переменные по строкам и столбцам в карте Карно упорядочиваются по коду Грея.
*/
class Map
{
public:
    Map(const TruthTable& tt);
    const BoolMatrix& getMatrix() const;
    const Bitset& getCode(int x, int y) const;
    friend std::ostream& operator<<(std::ostream& os, const Map& km);

private:
    std::vector<Bitset> rows;
    std::vector<Bitset> cols;
    BoolMatrix map;

private:
    BoolMatrix TruthTableToKarnaughMap(const TruthTable& tt) const;
};
} // namespace Karnaugh
} // namespace Lofmi
