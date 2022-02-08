/*********************************************************************************
 * FileName: Common.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_COMMON_HPP
#define PATH_ALGORITHM_COMMON_HPP

#include <cstdint>
#include <cfloat>

enum BlockType : uint8_t
{
    bt_empty,
    bt_boundary,
    bt_obstacle,
    bt_startPos,
    bt_destPos,
    bt_traveled,
};

struct Block
{
    BlockType blockType = bt_empty;
    double distance = DBL_MAX;
    Block *last = nullptr;

    bool operator<(const Block &v) const
    {
        return distance < v.distance;
    }

    bool operator>(const Block &v) const
    {
        return distance > v.distance;
    }
};

enum Direction
{
    d_start = 0,
    d_s = d_start,
    d_n,
    d_w,
    d_e,
    d_se,
    d_sw,
    d_ne,
    d_nw,
    d_count,
};

static const double DIAGONAL_LENGTH = 1.4142135623730951;

static const std::vector<double> DISTANCE_TABLE{
        1,
        1,
        1,
        1,
        DIAGONAL_LENGTH,
        DIAGONAL_LENGTH,
        DIAGONAL_LENGTH,
        DIAGONAL_LENGTH,
};

static const  std::vector<std::pair<int8_t, int8_t>> DIRECTION_TABLE{
        {-1, 0},
        {1,  0},
        {0,  -1},
        {0,  1},
        {-1, 1},
        {-1, -1},
        {1,  1},
        {1,  -1},
};

#endif //PATH_ALGORITHM_COMMON_HPP
