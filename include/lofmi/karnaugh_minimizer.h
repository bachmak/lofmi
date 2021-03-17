#pragma once

#include "lofmi/common.h"
#include "lofmi/utils.h"

namespace Lofmi
{
struct Loop
{
    // TODO: make fields private to maintain the invariant
    size_t top;
    size_t bottom;
    size_t left;
    size_t right;
    size_t area;
    size_t height;
    size_t width;

    inline bool operator==(const Loop& l) const
    {
        return std::vector<size_t>{ top, bottom, left, right, area } ==
            std::vector<size_t>{ l.top, l.bottom, l.left, l.right, l.area };
    }

    inline bool crossesMapXBorder() const
    {
        return top > bottom;
    }

    inline bool crossesMapYBorder() const
    {
        return left > right;
    }

    inline friend std::ostream& operator<<(std::ostream& os, const Loop& l)
    {
        return os << l.top << ' ' << l.bottom << ' '
                    << l.left << ' ' << l.right << ' ' << l.area;
    }

    inline friend std::istream& operator>>(std::istream& is, Loop& l)
    {
        return is >> l.top >> l.bottom >> l.left >> l.right >> l.area;
    }
};

class Minimizer
{
public:
    using Loops = std::vector<Loop>;
public:
    Minimizer(const BoolMatrix& map);
    Loops getMinimalForm() const;

private:
    const BoolMatrix& map;
    const size_t y_size;
    const size_t x_size;

private:
    struct Position
    {
        size_t top;
        size_t left;

        inline bool BelongsTo(const Loop& loop) const
        {
            return (
                loop.right - loop.width + 1 <= left &&
                loop.left + loop.width - 1 >= left &&
                loop.bottom - loop.height + 1 <= top &&
                loop.top + loop.height - 1 >= top
            );
        }

        inline bool IsBetweenTwoHalfsOf(const Loop& loop) const
        {
            bool result = false;

            if (loop.crossesMapXBorder())
            {
                result |= top < loop.top && top > loop.bottom;
            }
            if (loop.crossesMapYBorder())
            {
                result |= left < loop.left && left > loop.right;
            }

            return result;
        } 
    };

    enum class Direction
    {
        Right, Down
    };

private:
    Loops findAll() const;
    Loops findFromPosition(Position pos) const;
    Loops findInDirection(Position pos, size_t xy_step,
                          size_t& lim, Direction dir) const;
    void removeOverlaps(Loops& loops) const;
};
} // namespace Lofmi
