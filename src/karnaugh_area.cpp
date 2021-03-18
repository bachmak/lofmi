#include "lofmi/karnaugh_area.h"

#include <stdexcept>
#include <tuple>

namespace Lofmi
{

bool KarnaughMapPoint::operator==(const KarnaughMapPoint& kmp) const
{
    return x == kmp.x && y == kmp.y;
}

std::ostream& operator<<(std::ostream& os, const KarnaughMapPoint& kmp)
{
    return os << '(' << kmp.x << ", " << kmp.y << ')';
}

KarnaughMapArea::KarnaughMapArea(const Map& m, Point lt, Point rb) :
    left_top{ lt },
    right_bottom{ rb },
    map_height{ m.getMatrix().size() },
    map_width{ m.getMatrix().size() ? m.getMatrix()[0].size() : 0 }
{
    validatePoint(left_top);
    validatePoint(right_bottom);
    updateSizes();
}

bool KarnaughMapArea::operator==(const Area& a) const
{
    return std::tuple(left_top, right_bottom, map_height, map_width) ==
           std::tuple(a.left_top, a.right_bottom, a.map_height, a.map_width);
}

bool KarnaughMapArea::operator<(const Area& a) const
{
    return area_size < a.area_size;
}

void KarnaughMapArea::setLeftTopPoint(Point lt)
{
    validatePoint(left_top);
    left_top = lt;
    updateSizes();
}

void KarnaughMapArea::setRightBottomPoint(Point rb)
{
    validatePoint(rb);
    right_bottom = rb;
    updateSizes();
}

void KarnaughMapArea::setHeight(int h)
{
    if (h > map_height)
    {
        throw std::invalid_argument("Invalid height");
    }

    right_bottom.y = (left_top.y + h - 1) % map_height;
    updateSizes();
}

void KarnaughMapArea::setWidth(int w)
{
    if (w > map_width)
    {
        throw std::invalid_argument("Invalid width");
    }

    right_bottom.x = (left_top.x + w - 1) % map_width;
    updateSizes();
}

void KarnaughMapArea::reset()
{
    left_top = { 0, 0 };
    right_bottom = { 0, 0 };
    height = width = area_size = 0;
}

int KarnaughMapArea::getAreaSize() const { return area_size; }

int KarnaughMapArea::getLeft() const { return left_top.x; }

int KarnaughMapArea::getTop() const { return left_top.y; }

int KarnaughMapArea::getRight() const { return right_bottom.x; }

int KarnaughMapArea::getBottom() const { return right_bottom.y; }

int KarnaughMapArea::getHeight() const { return height; }

int KarnaughMapArea::getWidth() const { return width; }

KarnaughMapPoint KarnaughMapArea::operator[](size_t idx) const
{
    if (idx > area_size)
    {
        throw std::out_of_range("Index is out of area");
    }

    int y_offset = idx / height;
    int x_offset = idx % height;

    Point result{ left_top.x + x_offset, left_top.y + y_offset };
    
    result.x %= map_width;
    result.y %= map_height;

    return result;
}

bool KarnaughMapArea::includesPoint(Point p) const
{
    return (
        includesPointAlongAxis(p.x, left_top.x, right_bottom.x, map_width) &&
        includesPointAlongAxis(p.y, left_top.y, right_bottom.y, map_height)
    );
}

std::ostream& operator<<(std::ostream& os, const KarnaughMapArea& a)
{
    return os << a.left_top << " → " << a.right_bottom;
}

bool KarnaughMapArea::pointIsOutOfMap(Point p) const
{
    return p.x >= static_cast<int>(map_width) || 
           p.y >= static_cast<int>(map_height);
}

void KarnaughMapArea::validatePoint(Point p) const
{
    if (pointIsOutOfMap(p))
    {
        throw std::runtime_error("Point is out of map");
    }
}

int KarnaughMapArea::calculateDistance(
    int first, int second, int max
) const
{
    if (first < 0 || second < 0)
    {
        return 0;
    }

    if (first <= second)
    {
        return second - first + 1;
    }
    return max - first + second + 1;
}

void KarnaughMapArea::updateSizes()
{
    height = calculateDistance(left_top.y, right_bottom.y, map_height);
    width = calculateDistance(left_top.x, right_bottom.x, map_width);
    area_size = height * width;
}

bool KarnaughMapArea::includesPointAlongAxis(
    int point_coord, int area_first_coord, int area_second_coord, int max
) const
{
    if (this->crossesMapBorder(area_first_coord, area_second_coord))
    {
        return point_coord >= area_first_coord ||
               point_coord <= area_second_coord;
    }
    return point_coord >= area_first_coord &&
           point_coord <= area_second_coord;
}

bool KarnaughMapArea::crossesMapBorder(
    int first_coord, int second_coord
) const
{
    return first_coord > second_coord;
}

} // namespace Lofmi
