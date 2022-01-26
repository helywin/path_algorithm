/*********************************************************************************
 * FileName: DFSSolver.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#include "GreedyBestFirst.hpp"
#include "Scene.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <algorithm>

GreedyBestFirst::GreedyBestFirst()
{
    mDirection.push_back({1, 0});
    mDirection.push_back({0, 1});
    mDirection.push_back({-1, 0});
    mDirection.push_back({0, -1});
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

void GreedyBestFirst::setScene(Scene *scene)
{
    mScene = scene;
}

void GreedyBestFirst::tick()
{
    mCallback();
}

void GreedyBestFirst::run(int interval)
{
    mDuration = interval;
    gbfs();
}

void GreedyBestFirst::reset()
{
    mFinish = true;
}

void GreedyBestFirst::setStart(int row, int col)
{
    mScene->setData(row, col, bt_startPos);
    mStartPos.row = row;
    mStartPos.col = col;
}

void GreedyBestFirst::setDest(int row, int col)
{
    mScene->setData(row, col, bt_destPos);
    mDestPos.row = row;
    mDestPos.col = col;
}

void GreedyBestFirst::setCallback(Callback callback)
{
    mCallback = callback;
}

/*
procedure GBS(start, target) is:
mark start as visited
add start to queue
while queue is not empty do:
  current_node ← vertex of queue with min distance to target
  remove current_node from queue
  foreach neighbor n of current_node do:
    if n not in visited then:
      if n is target:
        return n
      else:
        mark n as visited
        add n to queue
return failure
 */

void GreedyBestFirst::gbfs()
{
    // 从小到大排列
    auto cmp = [this](const Vertex &a, const Vertex &b) {
        auto distance = [this](const Vertex &v) {
            return sqrt(pow(v.row - mDestPos.row, 2) + pow(v.col - mDestPos.col, 2));
        };
        return distance(a) > distance(b);
    };
//    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
    std::priority_queue<Vertex, std::vector<Vertex>, decltype(cmp)> q(cmp);
    q.push({mStartPos});

    while (!q.empty() && !mFinish) {
        Vertex v = q.top();
        q.pop();
        if (mScene->canPass(v.row, v.col)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(mDuration));
            mScene->setData(v.row, v.col, bt_traveled);
            mCallback();
        }
        bool stuck = true;
        for (const auto &d: mDirection) {
            auto next = v + d;
            if (mScene->canPass(next.row, next.col)) {
                if (next == mDestPos) {
                    mFinish = true;
                    break;
                } else {
                    q.push(next);
                }
                stuck = false;
            }
        }
    }
}

