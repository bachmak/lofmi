# pragma once

#include "lofmi/common.h"
#include "lofmi/karnaugh/map.h"

namespace Lofmi
{
namespace Karnaugh
{
struct MapPoint
{
    int x = 0;
    int y = 0;

    bool operator==(const MapPoint& kmp) const;
    
    friend std::ostream& operator<<(std::ostream& os, const MapPoint& kmp);
};

class MapArea
{
public:
    using Point = MapPoint;
    using Area = MapArea;

public:
    MapArea(
        const Map& map,
        Point left_top = { -1, -1 },
        Point right_bottom = { -1, -1 }
    );

    bool operator==(const Area& area) const;
    bool operator<(const Area& area) const;

    void setLeftTopPoint(Point left_top);
    void setRightBottomPoint(Point right_bottom);
    void setWidth(int width);
    void setHeight(int height);
    void reset();

    int getAreaSize() const;
    int getLeft() const;
    int getTop() const;
    int getRight() const;
    int getBottom() const;
    int getHeight() const;
    int getWidth() const;
    Point operator[](size_t idx) const;

    bool includesPoint(Point point) const;

    friend std::ostream& operator<<(std::ostream& os, const Area& a);

private:
    bool pointIsOutOfMap(Point point) const;
    void validatePoint(Point point) const;
    int calculateDistance(int first_coord, int second_coord, int max) const;
    void updateSizes();

    bool includesPointAlongAxis(
        int point_coord, int area_first_coord, int area_second_coord, int max
    ) const;

    bool crossesMapBorder(int first_coord, int second_coord) const;

private:
    Point left_top, right_bottom;
    int area_size = 0;
    int height = 0;
    int width = 0;
    size_t map_height;
    size_t map_width;
};
} // namespace Karnaugh    
} // namespace Lofmi
