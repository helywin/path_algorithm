/*********************************************************************************
 * FileName: AStarSolver.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#include "AStar.hpp"
#include <algorithm>
#include <queue>
#include <cmath>
#include <thread>
#include <chrono>
#include "Scene.hpp"

AStar::AStar() : AbstractSolver()
{
    const double sqrt2 = sqrt(2);
}

void AStar::run(int interval)
{
    mDuration = interval;
    astar();
}

void AStar::astar()
{
// 从小到大排列
    auto cmp = [this](const Vertex &a, const Vertex &b) {
        auto distance = [this](const Vertex &v) {
            return mDestPos.distance(v);
        };
        return distance(a) + a.block().distance > distance(b) + b.block().distance;
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
        if (v.canPass()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(mDuration));
            v.block().blockType = bt_traveled;
            mCallback();
        } else {
            continue;
        }
        for (auto i : mDirectionTable) {
            auto next = v + i;
            if (next.canPass()) {
                if (next == mDestPos) {
                    mFinish = true;
                    break;
                } else {
                    q.push(next);
                }
            }
        }
    }
}

