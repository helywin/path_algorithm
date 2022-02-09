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
#include <QDebug>

GreedyBestFirst::GreedyBestFirst()
{
}

void GreedyBestFirst::run(int interval)
{
    mDuration = interval;
    gbfs();
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
            return sqrt(pow(v.row() - mDestPos.row(), 2) + pow(v.col() - mDestPos.col(), 2));
        };
        return distance(a) > distance(b);
    };
//    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
    std::priority_queue<Vertex, std::vector<Vertex>, decltype(cmp)> q(cmp);
    q.push({mStartPos});
    Vertex v{};
    auto &path = mScene->path();
    while (!q.empty() && !mFinish) {
        v = q.top();
//        for (auto it = path.rbegin(); it != path.rend();) {
//            if (!cmp(Vertex{it->first, it->second}, v)) {
//                ++it;
//                path.pop_back();
//            } else {
//                break;
//            }
//        }
        q.pop();
//        path.emplace_back(v.row, v.col);
        if (v.canTravel()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(mDuration));
            v.setTravelled();
            mCallback();
        } else {
            continue;
        }
        for (auto i : mDirectionTable) {
            auto next = v.move(i);
            if (next.canTravel()) {
                if (next == mDestPos) {
                    mFinish = true;
                    break;
                } else {
                    q.push(next);
                }
            }
        }
    }
    mScene->generatePath(mDestPos);
    mCallback();
}

