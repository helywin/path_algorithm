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

int Vertex::mWidth = 0;
int Vertex::mHeight = 0;

Scene::Scene(int width, int height) :
        mWidth(width),
        mHeight(height),
        mData(mWidth * mHeight)
{
    std::fill(begin(mData), end(mData), Block{});
    Vertex::mWidth = width;
    Vertex::mHeight = height;
}

QSize Scene::size() const
{
    return {mWidth, mHeight};
}

Scene::Path &Scene::path()
{
    return mPath;
}

Block &Scene::block(int row, int col)
{
    assert(row < mHeight && row >= 0);
    assert(col < mWidth && col >= 0);
    return mData[row * mWidth + col];
}

