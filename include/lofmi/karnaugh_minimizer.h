#pragma once

#include "lofmi/common.h"
#include "lofmi/utils.h"
#include "lofmi/karnaugh_map.h"
#include "lofmi/karnaugh_area.h"

namespace Lofmi
{
std::vector<KarnaughMapArea> findAreas(const KarnaughMap& map);

namespace Minimize
{
    using Map = KarnaughMap;
    using Area = KarnaughMapArea;
    using Point = KarnaughMapPoint;
    using AreasPtr = std::unique_ptr<std::vector<Area>>;

    // TODO: remove extra operators for debug   
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

    AreasPtr moveInsert(AreasPtr src, AreasPtr dst);
    std::pair<int, int> getXY(const Map& map);
} // namespace Minimize

} // namespace Lofmi
