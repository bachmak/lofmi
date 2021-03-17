#include "lofmi/karnaugh_minimizer.h"

#include <ranges>

namespace Lofmi
{
Minimizer::Minimizer(const BoolMatrix& m) :
    map{ m },
    y_size{ m.size() },
    x_size{ m.empty() ? 0 : m[0].size() } {} 

Minimizer::Loops Minimizer::getMinimalForm() const
{
    Loops all_loops = findAll();
    removeOverlaps(all_loops);
    return all_loops;
}

Minimizer::Loops Minimizer::findAll() const
{
    Loops result;

    for (size_t top_pos = 0; top_pos < y_size; top_pos++)
    {
        for (size_t left_pos = 0; left_pos < x_size; left_pos++)
        {
            Loops loops = findFromPosition({ top_pos, left_pos });
            result.insert(result.end(), loops.begin(), loops.end());
        }
    }

    return result;
}

Minimizer::Loops Minimizer::findFromPosition(Position pos) const
{
    Loops result;
    size_t x_lim = x_size;
    size_t y_lim = y_size;

    for (size_t xy_step = 0; xy_step < std::min(x_lim, y_lim); xy_step++)
    {
        Loops loops = findInDirection(pos, xy_step, x_lim, Direction::Right);
        result.insert(result.end(), loops.begin(), loops.end());

        loops = findInDirection(pos, xy_step, y_lim, Direction::Down);
        result.insert(result.end(), loops.begin(), loops.end());
    }

    return result;
}

Minimizer::Loops Minimizer::findInDirection(Position pos,
                                            size_t xy_step,
                                            size_t& lim,
                                            Direction dir) const
{
    Loops result;

    for (size_t step_count = 0; step_count < lim; step_count++)
    {
        size_t y_idx = pos.top + xy_step;
        size_t x_idx = pos.left + xy_step;

        if (dir == Direction::Right)
        {
            x_idx += step_count;
        }
        else
        {
            y_idx += step_count;
        }

        y_idx %= y_size;
        x_idx %= x_size;

        if (!map[y_idx][x_idx] && step_count == 0)
        {
            lim = 0;
        }
        else if (!map[y_idx][x_idx] || step_count == lim - 1)
        {
            lim = NextPowerOf2(xy_step + step_count);

            Loop loop;
            loop.area = lim * NextPowerOf2(xy_step + 1);
            loop.top = pos.top;
            loop.left = pos.left;

            if (dir == Direction::Right)
            {
                loop.bottom = (pos.top - 1 + NextPowerOf2(xy_step + 1)) % y_size;
                loop.right = (pos.left + lim - 1) % x_size;
            }
            else
            {
                loop.bottom = (pos.top + lim - 1) % y_size;
                loop.right = (pos.left - 1 + NextPowerOf2(xy_step + 1)) % x_size;
            }

            loop.height = (loop.bottom - loop.top + y_size) % y_size + 1;
            loop.width = (loop.right - loop.left + x_size) % x_size + 1;

            result.push_back(loop);
        }
    }
    
    return result;
}

void Minimizer::removeOverlaps(Loops& loops) const
{
    auto it = std::max_element(
        loops.begin(), loops.end(),
        [](const Loop& lhs, const Loop& rhs) {
            return lhs.area < rhs.area;
        }
    );

    int max_area = it->area;

    auto non_zero_area = [](Loop& loop) { return loop.area != 0; };

    for (size_t area = 1; area <= max_area; area *= 2)
    {
        auto same_area = [area](Loop& loop) { return loop.area == area; };

        for (Loop& ref_loop : loops |
             std::ranges::views::filter(non_zero_area) |
             std::ranges::views::filter(same_area))
             // TODO: consider removing non_zero_area lambda
        {
            /////////////////////////////////////////////////

            // TODO: enclose in a function

            auto other_loop = [&ref_loop](Loop& loop) { return &ref_loop != &loop; };

            size_t y_step = 0;
            for ( ; y_step < ref_loop.height; y_step++)
            {
                size_t y_pos = (ref_loop.top + y_step) % y_size;

                size_t x_step = 0;
                for ( ; x_step < ref_loop.width; x_step++)
                {
                    size_t x_pos = (ref_loop.left + x_step) % x_size;

                    bool is_sub_area = false;
                    for (Loop& loop : loops |
                         std::views::filter(non_zero_area) |
                         std::views::filter(other_loop))
                    {
                        Position position{ y_pos, x_pos };
                        if (position.BelongsTo(loop))
                        {
                            if (position.IsBetweenTwoHalfsOf(loop))
                            {
                                continue;
                            }
                            else
                            {
                                is_sub_area = true;
                                break;
                            }
                            
                        }
                    }

                    if (!is_sub_area)
                    {
                        break;
                    }
                }

                if (x_step != ref_loop.width)
                {
                    break;
                }
            }

            if (y_step == ref_loop.height)
            {
                // TODO: make reset method for Loop class
                ref_loop.area = 0;
            }
        }
    }

    auto border = std::remove_if(
        loops.begin(), loops.end(),
        [](const Loop& loop) { return loop.area == 0; }
    );

    loops.erase(border, loops.end());
}
} // namespace Lofmi
