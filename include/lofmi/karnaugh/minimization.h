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
using Area = MapArea;
using Point = MapPoint;
using AreasPtr = std::unique_ptr<std::vector<Area>>;

// TODO: remove extra operators for debug   

std::vector<MapArea> findAreas(const Map& map);

inline std::ostream& operator<<(std::ostream& os, const AreasPtr& areas)
{
    for (const auto& area : *areas)
    {
        os << area << std::endl;
    }

    return os;
}

enum class Direction
{
    Right, Down
};

AreasPtr findAllAreas(const Map& map);

AreasPtr removeOverlappingAreas(AreasPtr areas);

AreasPtr findAreasFromPoint(const Map& map, Point point);

AreasPtr findAreasInDirectionAndUpdateLimit(
    const Map& map, Point point, int xy_step, int& limit, Direction dir
);

void resetIfCoveredByOther(Area& ref_area, const AreasPtr& areas);

AreasPtr moveInsert(AreasPtr src, AreasPtr dst);

std::pair<int, int> getXY(const Map& map);

} // namespace Karnaugh
} // namespace Minimize
} // namespace Lofmi
