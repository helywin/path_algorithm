/*********************************************************************************
 * FileName: BFSSolver.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_DIJKSTRA_HPP
#define PATH_ALGORITHM_DIJKSTRA_HPP

#include "AbstractSolver.hpp"
#include <valarray>


class Dijkstra : public AbstractSolver
{
public:
    struct Vertex
    {
        int row;
        int col;
        double distance = 0;

        Vertex operator+(const Vertex &v) const
        {
            return {row + v.row, col + v.col, distance + v.distance};
        }

        bool operator==(const Vertex &v) const
        {
            return row == v.row && col == v.col;
        }

        bool operator<(const Vertex &v) const
        {
            return distance < v.distance;
        }

        bool operator>(const Vertex &v) const
        {
            return distance > v.distance;
        }
    };
public:
    Dijkstra();
    ~Dijkstra() override = default;
    void run(int interval) override;
    void setCallback(Callback callback) override;
    void setScene(Scene *scene) override;
    void setStart(int row, int col) override;
    void setDest(int row, int col) override;
protected:
    void dijkstra();
private:
    Scene *mScene = nullptr;
    Vertex mStartPos;
    Vertex mDestPos;
    std::valarray<float> mCostTable;
    bool mFinish = false;
    Callback mCallback;
    int mDuration = 0;
    std::vector<Vertex> mDirection;
};


#endif //PATH_ALGORITHM_DIJKSTRA_HPP
