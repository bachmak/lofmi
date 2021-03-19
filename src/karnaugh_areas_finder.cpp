#include "lofmi/karnaugh/minimization.h"

#include <ranges>

namespace Lofmi
{
namespace Karnaugh
{
namespace Minimization
{
AreasFinder::AreasFinder(const Map& m) :
    map{ m },
    y_size{ static_cast<int>(m.getMatrix().size()) },
    x_size{ 
        m.getMatrix().size() ? static_cast<int>(m.getMatrix()[0].size()) : 0
    } {}

Areas AreasFinder::findAreas() const
{
    Areas areas = findAllPossibleAreas();
    removeOverlappingAreas(areas);
    return areas;
}

Areas AreasFinder::findAllPossibleAreas() const
{
    Areas result;

    for (int y_step = 0; y_step < y_size; y_step++)
    {
        for (int x_step = 0; x_step < x_size; x_step++)
        {
            Areas areas = findAreasFromPoint(Point{ x_step, y_step });
            moveInsert(std::move(areas), result);
        }
    }
         
    return std::move(result);
}

Areas AreasFinder::findAreasFromPoint(Point point) const
{
    Areas result;

    int x_lim = x_size;
    int y_lim = y_size;

    for (int xy_step = 0; xy_step < std::min(x_lim, y_lim); xy_step++)
    {
        Areas x_limited_areas = findAreasInDirectionAndUpdateLimit(
            point, xy_step, x_lim, Direction::Right
        );

        Areas y_limited_areas = findAreasInDirectionAndUpdateLimit(
            point, xy_step, y_lim, Direction::Down
        );

        moveInsert(std::move(x_limited_areas), result);
        moveInsert(std::move(y_limited_areas), result);
    }

    return std::move(result);
}

Areas AreasFinder::findAreasInDirectionAndUpdateLimit(
    Point point, int xy_step, int& lim, Direction dir
) const
{
    Areas result;

    for (int step_count = 0; step_count < lim; step_count++)
    {
        int y_idx = point.y + xy_step;
        int x_idx = point.x + xy_step;

        switch (dir)
        {
        case Direction::Right:
            x_idx += step_count;
            break;
        
        case Direction::Down:
            y_idx += step_count;
        }

        x_idx %= x_size;
        y_idx %= y_size;

        if (step_count == 0 && !map.getMatrix()[y_idx][x_idx])
        {
            lim = 0;
        }
        else if (step_count == lim - 1 || !map.getMatrix()[y_idx][x_idx])
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

            result.push_back(std::move(area));
        }
    }
    
    return std::move(result);
}

void AreasFinder::removeOverlappingAreas(Areas& areas)
{
    auto it = std::max_element(areas.begin(), areas.end());
    int max_area_size = it->getAreaSize();

    for (int area_size = 1; area_size <= max_area_size; area_size *= 2)
    {
        auto has_same_area_size = std::views::filter(
            [area_size](const Area& a)
            { return a.getAreaSize() == area_size; }
        );

        for (Area& ref_area : areas | has_same_area_size)
        {
            resetIfCoveredByOther(ref_area, areas);
        }
    }

    auto non_zero_border = std::remove_if(
        areas.begin(), areas.end(),
        [](const Area& a) { return a.getAreaSize() == 0; }
    );

    areas.erase(non_zero_border, areas.end());
}

void AreasFinder::resetIfCoveredByOther(Area& ref_area, const Areas& areas)
{
    for (int i = 0; i < ref_area.getAreaSize(); i++)
    {    
        auto differs_from_ref_area = std::views::filter(
            [&ref_area](const Area& a) { return &ref_area != &a; }
        );

        auto has_non_zero_area_size = std::views::filter(
            [](const Area& a) { return a.getAreaSize() != 0; }
        );

        for (const Area& area : areas | 
            differs_from_ref_area |
            has_non_zero_area_size)
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

void AreasFinder::moveInsert(Areas src, Areas& dst)
{
    dst.insert(
        dst.end(),
        std::make_move_iterator(src.begin()),
        std::make_move_iterator(src.end())
    );
}
} // namespace Karnaugh
} // namespace Minimization
} // namespace Lofmi
