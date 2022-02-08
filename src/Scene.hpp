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
#include <vector>
#include "Common.hpp"

class Scene;

class Vertex
{
private:
    std::valarray<Block> *data = nullptr;
    int mRow = -1;
    int mCol = -1;

    explicit Vertex(std::valarray<Block> &data, int row, int col) :
            data(&data),
            mRow(row), mCol(col)
    {}

    friend class Scene;

public:
    static int mWidth;
    static int mHeight;

    Vertex() = default;

    Block &block()
    {
        return (*data)[mRow * mWidth + mCol];
    }

    const Block &block() const
    {
        return (*data)[mRow * mWidth + mCol];
    }

    Vertex operator+(Direction dir)
    {
        auto next = Vertex{
                *data,
                mRow + DIRECTION_TABLE[dir].first,
                mCol + DIRECTION_TABLE[dir].second
        };
        double distance = this->block().distance + DISTANCE_TABLE[dir];
        if (distance < next.block().distance) {
            next.block().distance = distance;
            next.block().last = &block();
        }
        return next;
    }

    bool operator==(const Vertex &v) const
    {
        return mRow == v.mRow && mCol == v.mCol;
    }

    inline int row() const
    {
        return mCol;
    }

    inline int col() const
    {
        return mCol;
    }
    
    bool canPass() const {
        if (mRow < mHeight && mRow >= 0 &&
            mCol < mWidth && mCol >= 0) {
            return block().blockType == bt_empty ||
                   block().blockType == bt_startPos ||
                   block().blockType == bt_destPos;
        } else {
            return false;
        }
    }

    double distance(const Vertex &other) {
        return sqrt(pow(mRow - other.mRow, 2) + pow(mCol - other.mCol, 2));
    }
};

class Scene
{
public:
    enum State
    {
        empty,
        barrier,
        obstacle,
    };

    using Path = std::vector<std::pair<int, int>>;
public:
    Scene(int width, int height);
    Block &block(int row, int col);
    QSize size() const;
    Path &path();

    Vertex vertex(int row, int col)
    {
        return Vertex{mData, row, col};
    }

protected:
    int mWidth;
    int mHeight;
    std::valarray<Block> mData;
    Path mPath;
};


#endif //PATH_ALGORITHM_SCENE_HPP
