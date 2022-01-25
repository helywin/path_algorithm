/*********************************************************************************
 * FileName: DFSSolver.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_DFSSOLVER_HPP
#define PATH_ALGORITHM_DFSSOLVER_HPP

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

class Scene;

class DFSSolver : public AbstractSolver
{
public:
    DFSSolver();
    void setScene(Scene *scene);
    void setStart(int row, int col);
    void setDest(int row, int col);
    void reset();
    void tick() override;
    void run(int interval) override;
    void setCallback(Callback callback) override;
protected:
    void dfs(int row, int col);
private:
    Scene *mScene = nullptr;
    std::pair<int, int> mStartPos;
    std::pair<int, int> mDestPos;
    std::valarray<float> mCostTable;
    bool mFinish = false;
    Callback mCallback;
    int mDuration = 0;
    std::vector<std::array<int, 2>> mFuncSortTable;
};


#endif //PATH_ALGORITHM_DFSSOLVER_HPP
