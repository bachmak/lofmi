#include "lofmi/karnaugh_minimizer.h"

#include <ranges>

namespace Lofmi
{

std::vector<KarnaughMapArea> findAreas(const KarnaughMap& map)
{
    auto areas = Minimize::findAllAreas(map);
    areas = Minimize::removeOverlappingAreas(std::move(areas));
    return *areas;
}

namespace Minimize
{
// TODO: consider moving functions into class to have access to the map

AreasPtr findAllAreas(const Map& map)
{
    AreasPtr result = std::make_unique<std::vector<Area>>();
    auto [x_size, y_size] = getXY(map);

    for (int y_step = 0; y_step < y_size; y_step++)
    {
        for (int x_step = 0; x_step < x_size; x_step++)
        {
            auto areas = findAreasFromPoint(map, Point{ x_step, y_step });
            result = moveInsert(std::move(areas), std::move(result));
        }
    }
         
    return std::move(result);
}

AreasPtr findAreasFromPoint(const Map& map, Point point)
{
    AreasPtr result = std::make_unique<std::vector<Area>>();

    auto [x_lim, y_lim] = getXY(map);

    for (int xy_step = 0; xy_step < std::min(x_lim, y_lim); xy_step++)
    {
        result = moveInsert(
            findAreasInDirectionAndUpdateLimit(
                map, point, xy_step, x_lim, Direction::Right
            ),
            std::move(result)
        );

        result = moveInsert(
            findAreasInDirectionAndUpdateLimit(
                map, point, xy_step, y_lim, Direction::Down
            ),
            std::move(result)
        );
    }

    return std::move(result);
}

AreasPtr findAreasInDirectionAndUpdateLimit(
    const Map& map, Point point, int xy_step, int& lim, Direction dir
)
{
    AreasPtr result = std::make_unique<std::vector<Area>>();
    auto [x_size, y_size] = getXY(map);

    for (int step_count = 0; step_count < lim; step_count++)
    {
        int y_idx = point.y + xy_step;
        int x_idx = point.x + xy_step;

        if (dir == Direction::Right)
        {
            x_idx += step_count;
        }
        else
        {
            y_idx += step_count;
        }
        
        x_idx %= x_size;
        y_idx %= y_size;

        if (!map.getMatrix()[y_idx][x_idx] && step_count == 0)
        {
            lim = 0;
        }
        else if (!map.getMatrix()[y_idx][x_idx] || step_count == lim - 1)
        {
            lim = NextPowerOf2(xy_step + step_count);

            Area area(map);

            area.setLeftTopPoint({ point.x, point.y });

            if (dir == Direction::Right)
            {
                area.setHeight(NextPowerOf2(xy_step + 1));
                area.setWidth(lim);
            }
            else
            {
                area.setHeight(lim);
                area.setWidth(NextPowerOf2(xy_step + 1));
            }

            result->push_back(area);
        }
    }
    
    return std::move(result);
}

AreasPtr removeOverlappingAreas(AreasPtr areas)
{
    auto it = std::max_element(areas->begin(), areas->end());
    int max_area_size = it->getAreaSize();

    for (int area_size = 1; area_size <= max_area_size; area_size *= 2)
    {
        auto has_same_area_size = std::views::filter(
            [area_size](const Area& a)
            { return a.getAreaSize() == area_size; }
        );

        for (Area& ref_area : *areas | has_same_area_size)
        {
            resetIfCoveredByOther(ref_area, areas);
        }
    }

    auto non_zero_border = std::remove_if(
        areas->begin(), areas->end(),
        [](const Area& a) { return a.getAreaSize() == 0; }
    );

    areas->erase(non_zero_border, areas->end());
    return std::move(areas);
}

void resetIfCoveredByOther(Area& ref_area, const AreasPtr& areas)
{
    for (int i = 0; i < ref_area.getAreaSize(); i++)
    {    
        auto differs_from_ref_area = std::views::filter(
            [&ref_area](const Area& a) { return &ref_area != &a; }
        );

        auto non_zero_area_size = std::views::filter(
            [](const Area& a) { return a.getAreaSize() != 0; }
        );

        for (Area& area : *areas | 
            differs_from_ref_area |
            non_zero_area_size)
        {
            if (area.includesPoint(ref_area[i]))
            {
                ref_area.reset();
                break;
            }
        }

        if (ref_area.getAreaSize() == 0)
        {
            break;
        }
    }
}

AreasPtr moveInsert(AreasPtr src, AreasPtr dst)
{
    dst->insert(
        dst->end(),
        std::make_move_iterator(src->begin()),
        std::make_move_iterator(src->end())
    );

    return std::move(dst);
}

std::pair<int, int> getXY(const Map& map)
{
    int y = static_cast<int>(map.getMatrix().size());
    int x = y ? static_cast<int>(map.getMatrix()[0].size()) : 0;
    return { x, y };
}

} // namespace Minimize

} // namespace Lofmi
