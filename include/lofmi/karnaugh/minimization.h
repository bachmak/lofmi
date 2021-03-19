#pragma once

#include "lofmi/common.h"
#include "lofmi/utils.h"
#include "lofmi/karnaugh/map.h"
#include "lofmi/karnaugh/area.h"

namespace Lofmi
{
namespace Karnaugh
{
namespace Minimization
{
using Point = MapPoint;
using Area = MapArea;
using Areas = std::vector<Area>;

class AreasFinder
{
public:
    AreasFinder(const Map& m);
    Areas findAreas() const;

private:
    const Map& map;
    const int x_size;
    const int y_size;

private:
    enum class Direction
    {
        Right, Down
    };

private:    
    Areas findAllPossibleAreas() const;
    Areas findAreasFromPoint(Point point) const;
    Areas findAreasInDirectionAndUpdateLimit(
        Point point, int xy_step, int& limit, Direction dir
    ) const;

    static void removeOverlappingAreas(Areas& areas);
    static void resetIfCoveredByOther(Area& ref_area, const Areas& areas);
    static void moveInsert(Areas src, Areas& dst);
};

class 
} // namespace Minimize
} // namespace Karnaugh
} // namespace Lofmi
