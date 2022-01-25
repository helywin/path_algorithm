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

enum BlockType : uint8_t
{
    bt_empty,
    bt_boundary,
    bt_obstacle,
    bt_startPos,
    bt_destPos,
    bt_traveled,
};

#endif //PATH_ALGORITHM_COMMON_HPP
