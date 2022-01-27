/*********************************************************************************
 * FileName: BFSSolver.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description:
 * Others:
*********************************************************************************/

#include "Dijkstra.hpp"
#include <queue>
#include <algorithm>
#include <thread>
#include <chrono>
#include "Scene.hpp"

Dijkstra::Dijkstra()
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

void Dijkstra::tick()
{

}

void Dijkstra::run(int interval)
{
    mDuration = interval;
    dijkstra();
}

void Dijkstra::reset()
{
    mFinish = true;
}

void Dijkstra::setStart(int row, int col)
{
    mScene->setData(row, col, bt_startPos);
    mStartPos.row = row;
    mStartPos.col = col;
}

void Dijkstra::setDest(int row, int col)
{
    mScene->setData(row, col, bt_destPos);
    mDestPos.row = row;
    mDestPos.col = col;
}

//  function Dijkstra(Graph, source):
//      dist[source] ← 0                           // Initialization
//
//      create vertex priority queue Q
//
//      for each vertex v in Graph.Vertices:
//          if v ≠ source
//              dist[v] ← INFINITY                 // Unknown distance from source to v
//              prev[v] ← UNDEFINED                // Predecessor of v
//
//         Q.add_with_priority(v, dist[v])
//
//
//     while Q is not empty:                      // The main loop
//         u ← Q.extract_min()                    // Remove and return best vertex
//         for each neighbor v of u:              // only v that are still in Q
//             alt ← dist[u] + Graph.Edges(u, v)
//             if alt < dist[v]
//                 dist[v] ← alt
//                 prev[v] ← u
//                 Q.decrease_priority(v, alt)
//
//     return dist, prev


void Dijkstra::dijkstra()
{
// 从小到大排列
    auto cmp = [this](const Vertex &a, const Vertex &b) {
        return a.distance > b.distance;
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
        } else {
            continue;
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

void Dijkstra::setCallback(Callback callback)
{
    mCallback = callback;
}

void Dijkstra::setScene(Scene *scene)
{
    mScene = scene;
}
