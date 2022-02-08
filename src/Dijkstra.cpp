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

void Dijkstra::run(int interval)
{
    mDuration = interval;
    dijkstra();
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
        return a.block().distance > b.block().distance;
    };
//    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
    std::priority_queue<Vertex, std::vector<Vertex>, decltype(cmp)> q(cmp);
    q.push({mStartPos});

    while (!q.empty() && !mFinish) {
        Vertex v = q.top();
        q.pop();
        if (v.canPass()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(mDuration));
            v.block().blockType = bt_traveled;
            mCallback();
        } else {
            continue;
        }
        bool stuck = true;
        for (auto i : mDirectionTable) {
            auto next = v + i;
            if (next.canPass()) {
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