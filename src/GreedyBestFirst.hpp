/*********************************************************************************
 * FileName: DFSSolver.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_GREEDYBESTFIRST_HPP
#define PATH_ALGORITHM_GREEDYBESTFIRST_HPP

#include "AbstractSolver.hpp"
#include <utility>
#include <valarray>

enum Direction
{
    d_s,
    d_n,
    d_w,
    d_e,
    d_se,
    d_sw,
    d_ne,
    d_nw,
};

struct Vertex
{
    int row;
    int col;

    Vertex operator+(const Vertex &v) const
    {
        return {row + v.row, col + v.col};
    }

    bool operator==(const Vertex &v) const {
        return row == v.row && col == v.col;
    }
};

class Scene;

class GreedyBestFirst : public AbstractSolver
{
public:
    GreedyBestFirst();
    ~GreedyBestFirst() override = default;
    void setStart(int row, int col) override;
    void setDest(int row, int col) override;
    void reset() override;
    void tick() override;
    void run(int interval) override;
    void setScene(Scene *scene) override;
    void setCallback(Callback callback) override;
protected:
    void gbfs();
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


#endif //PATH_ALGORITHM_GREEDYBESTFIRST_HPP
