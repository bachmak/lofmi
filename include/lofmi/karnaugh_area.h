# pragma once

#include "lofmi/common.h"
#include "lofmi/karnaugh_map.h"

namespace Lofmi
{

struct KarnaughMapPoint
{
    int x = 0;
    int y = 0;

    bool operator==(const KarnaughMapPoint& kmp) const;
    
    friend std::ostream& operator<<(
        std::ostream& os, const KarnaughMapPoint& kmp
    );
};

class KarnaughMapArea
{
public:
    using Map = KarnaughMap;
    using Point = KarnaughMapPoint;
    using Area = KarnaughMapArea;

public:
    KarnaughMapArea(
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
    
} // namespace Lofmi
