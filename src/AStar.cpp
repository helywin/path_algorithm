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

AStar::AStar()
{
    const double sqrt2 = sqrt(2);
    mDirection.push_back({1, 1, sqrt2});
    mDirection.push_back({-1, 1, sqrt2});
    mDirection.push_back({1, -1, sqrt2});
    mDirection.push_back({-1, -1, sqrt2});
    mDirection.push_back({1, 0, 1});
    mDirection.push_back({0, 1, 1});
    mDirection.push_back({-1, 0, 1});
    mDirection.push_back({0, -1, 1});
}

void AStar::setScene(Scene *scene)
{
    mScene = scene;
}

void AStar::run(int interval)
{
    mDuration = interval;
    astar();
}

void AStar::setStart(int row, int col)
{
    mScene->setData(row, col, bt_startPos);
    mStartPos.row = row;
    mStartPos.col = col;
}

void AStar::setDest(int row, int col)
{
    mScene->setData(row, col, bt_destPos);
    mDestPos.row = row;
    mDestPos.col = col;
}

void AStar::setCallback(Callback callback)
{
    mCallback = callback;
}


void AStar::astar()
{
// 从小到大排列
    auto cmp = [this](const Vertex &a, const Vertex &b) {
        auto distance = [this](const Vertex &v) {
            return sqrt(pow(v.row - mDestPos.row, 2) + pow(v.col - mDestPos.col, 2));
        };
        return distance(a) + a.distance > distance(b) + b.distance;
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
        if (mScene->canPass(v.row, v.col)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(mDuration));
            mScene->setData(v.row, v.col, bt_traveled);
            mCallback();
        } else {
            continue;
        }
        for (const auto &d: mDirection) {
            auto next = v + d;
            if (mScene->canPass(next.row, next.col)) {
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

