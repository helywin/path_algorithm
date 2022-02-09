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
#include <QDebug>
#include "Scene.hpp"

AStar::AStar() : AbstractSolver()
{
    const double sqrt2 = sqrt(2);
}

void AStar::run(int interval)
{
    mDuration = interval;
    mDuration = 5;
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
        q.pop();
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
    qInfo() << "完成";
    mScene->generatePath(mDestPos);
    mCallback();
}

