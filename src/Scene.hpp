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
#include <iostream>
#include "Common.hpp"

class Scene;

class Vertex
{
private:
    std::valarray<Block> *data = nullptr;
    int mRow = -1;
    int mCol = -1;
    bool mUpdated = false;

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

    void setTravelled()
    {
        block().blockType = bt_traveled;
    }

    const Block &block() const
    {
        return (*data)[mRow * mWidth + mCol];
    }

    bool valid() const
    {
        return mRow < mHeight && mRow >= 0 &&
               mCol < mWidth && mCol >= 0;
    }

    Vertex move(Direction dir)
    {
        auto next = Vertex{
                *data,
                mRow + DIRECTION_TABLE[dir].first,
                mCol + DIRECTION_TABLE[dir].second
        };
        if (next.block().blockType == bt_obstacle ||
            next.block().blockType == bt_boundary) {
            next.block().last = {row(), col()};
            return next;
        }
        double distance = block().distance + DISTANCE_TABLE[dir];
        if (distance < next.block().distance) {
            next.block().distance = distance;
            next.block().last = {row(), col()};
        }
        return next;
    }

    bool operator==(const Vertex &v) const
    {
        return mRow == v.mRow && mCol == v.mCol;
    }

    Vertex &operator=(const Vertex &v)
    {
        if (&v != this) {
            mRow = v.mRow;
            mCol = v.mCol;
            mUpdated = v.mUpdated;
            data = v.data;
        }
        return *this;
    }

    inline int row() const
    {
        return mRow;
    }

    inline int col() const
    {
        return mCol;
    }

    bool canTravel() const
    {
        return valid() && block().blockType == bt_empty;
    }

    double distance(const Vertex &other)
    {
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

    void generatePath(const Vertex &dest);

    const Path &path() const
    {
        return mPath;
    }

protected:
    int mWidth;
    int mHeight;
    std::valarray<Block> mData;
    Path mPath;
};


#endif //PATH_ALGORITHM_SCENE_HPP
