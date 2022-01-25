/*********************************************************************************
 * FileName: DFSSolver.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#include "DFSSolver.hpp"
#include "Scene.hpp"
#include <iostream>
#include <thread>
#include <chrono>

DFSSolver::DFSSolver()
{
    mFuncSortTable.push_back({1, 0});
    mFuncSortTable.push_back({0, 1});
    mFuncSortTable.push_back({1, 1});
    mFuncSortTable.push_back({-1, 0});
    mFuncSortTable.push_back({0, -1});
    mFuncSortTable.push_back({1, -1});
    mFuncSortTable.push_back({-1, 1});
    mFuncSortTable.push_back({-1, -1});
}

int sign(int i)
{
    if (i < 0) {
        return -1;
    } else if (i > 0) {
        return 1;
    } else {
        return 0;
    }
}

void DFSSolver::setScene(Scene *scene)
{
    mScene = scene;
}

void DFSSolver::tick()
{
    AbstractSolver::tick();
    mCallback();
}

void DFSSolver::run(int interval)
{
    mDuration = interval;
    dfs(mStartPos.first, mStartPos.second);
}

void DFSSolver::reset()
{
    mFinish = true;
}

void DFSSolver::setStart(int row, int col)
{
    mScene->setData(row, col, bt_startPos);
    mStartPos.first = row;
    mStartPos.second = col;
}

void DFSSolver::setDest(int row, int col)
{
    mScene->setData(row, col, bt_destPos);
    mDestPos.first = row;
    mDestPos.second = col;
}

void DFSSolver::setCallback(Callback callback)
{
    mCallback = callback;
}

void DFSSolver::dfs(int row, int col)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(mDuration));
    mCallback();
    if (mDestPos.first == row &&
        mDestPos.second == col) {
        std::cout << "finish" << std::endl;
        mFinish = true;
    }
    if (mFinish) {
        return;
    }
    mScene->setData(row, col, bt_traveled);
    mScene->path().emplace_back(row, col);
    std::array<int, 2> direction{};
    direction[0] = sign(mDestPos.first - row);
    direction[1] = sign(mDestPos.second - col);
    //根据当前方向优先选择最近的路线
    std::sort(mFuncSortTable.begin(), mFuncSortTable.end(),
              [&direction](const std::array<int, 2> &a,
                           const std::array<int, 2> &b) {
                  return (abs(direction[0] - a[0]) + abs(direction[1] - a[1])) <
                         (abs(direction[0] - b[0]) + abs(direction[1] - b[1]));
              });
    for (auto &e: mFuncSortTable) {
        if (mScene->canPass(row + e[0], col + e[1])) {
            dfs(row + e[0], col + e[1]);
        }
    }
    mScene->path().pop_back();
}

