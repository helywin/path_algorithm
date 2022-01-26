/*********************************************************************************
 * FileName: BFSSolver.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_BREADTHFIRST_HPP
#define PATH_ALGORITHM_BREADTHFIRST_HPP

#include "AbstractSolver.hpp"
#include <valarray>

class BreadthFirst : public AbstractSolver
{
public:
    ~BreadthFirst() override = default;
    void tick() override;
    void run(int interval) override;
    void setCallback(Callback callback) override;
    void setScene(Scene *scene) override;
    void setStart(int row, int col) override;
    void setDest(int row, int col) override;
    void reset() override;
protected:
    void bfs(int row, int col);
private:
    Scene *mScene = nullptr;
    std::pair<int, int> mStartPos;
    std::pair<int, int> mDestPos;
    std::valarray<float> mCostTable;
    bool mFinish = false;
    Callback mCallback;
    int mDuration = 0;
};


#endif //PATH_ALGORITHM_BREADTHFIRST_HPP
