/*********************************************************************************
 * FileName: Scene.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/24
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_SCENE_HPP
#define PATH_ALGORITHM_SCENE_HPP

#include <utility>
#include <QSize>
#include <valarray>
#include "Common.hpp"

class Scene
{
public:
    enum State
    {
        empty,
        barrier,
        obstacle,
    };

public:
    Scene(int width, int height);
    void setData(int row, int col, BlockType type, float cost);
    std::pair<BlockType, float> getData(int row, int col) const;
    QSize size() const;

protected:
    int mWidth;
    int mHeight;
    std::valarray<BlockType> mData;
    std::valarray<float> mCost;
};


#endif //PATH_ALGORITHM_SCENE_HPP
