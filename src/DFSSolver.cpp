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
    if (mScene->canPass(row + 1, col + 1)) {
        dfs(row + 1, col + 1);
    }
    if (mScene->canPass(row + 1, col)) {
        dfs(row + 1, col);
    }
    if (mScene->canPass(row, col + 1)) {
        dfs(row, col + 1);
    }
    if (mScene->canPass(row - 1, col)) {
        dfs(row - 1, col);
    }
    if (mScene->canPass(row, col - 1)) {
        dfs(row, col - 1);
    }
    if (mScene->canPass(row + 1, col - 1)) {
        dfs(row + 1, col - 1);
    }
    if (mScene->canPass(row - 1, col + 1)) {
        dfs(row - 1, col + 1);
    }
    if (mScene->canPass(row - 1, col - 1)) {
        dfs(row - 1, col - 1);
    }
    mScene->path().pop_back();
}

