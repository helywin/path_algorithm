/*********************************************************************************
 * FileName: Scene.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/24
 * Description: 
 * Others:
*********************************************************************************/

#include "Scene.hpp"
#include <cassert>

Scene::Scene(int width, int height) :
        mWidth(width),
        mHeight(height),
        mData(mWidth * mHeight),
        mCost(mWidth * mHeight)
{
    std::fill(begin(mCost), end(mCost), 1);
}

void Scene::setData(int row, int col, BlockType type, float cost)
{
    assert(row < mHeight && row >= 0);
    assert(col < mWidth && col >= 0);
    mData[row * mWidth + col] = type;
    mCost[row * mWidth + col] = cost;
}

std::pair<BlockType, float> Scene::getData(int row, int col) const
{
    assert(row < mHeight && row >= 0);
    assert(col < mWidth && col >= 0);
    return {mData[row * mWidth + col], mCost[row * mWidth + col]};
}

QSize Scene::size() const
{
    return {mWidth, mHeight};
}

Scene::Path &Scene::path()
{
    return mPath;
}

bool Scene::canPass(int row, int col) const
{
    if (row < mHeight && row >= 0 &&
        col < mWidth && col >= 0) {
        return mData[row * mWidth + col] == bt_empty ||
               mData[row * mWidth + col] == bt_startPos ||
               mData[row * mWidth + col] == bt_destPos;
    } else {
        return false;
    }
}

void Scene::setData(int row, int col, BlockType type)
{
    assert(row < mHeight && row >= 0);
    assert(col < mWidth && col >= 0);
    mData[row * mWidth + col] = type;
}
