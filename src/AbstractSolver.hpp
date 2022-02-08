/*********************************************************************************
 * FileName: Solver.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/24
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_ABSTRACTSOLVER_HPP
#define PATH_ALGORITHM_ABSTRACTSOLVER_HPP

#include <functional>
#include "Common.hpp"
#include "Scene.hpp"

using Callback = std::function<void()>;

class AbstractSolver
{
public:
    AbstractSolver();
    virtual ~AbstractSolver() = default;
    virtual void run(int interval) {}
    virtual void setCallback(Callback callback);
    virtual void setScene(Scene *scene);
    virtual void setStart(int row, int col);
    virtual void setDest(int row, int col);
protected:
    Scene *mScene = nullptr;
    Vertex mStartPos;
    Vertex mDestPos;
    bool mFinish = false;
    Callback mCallback;
    int mDuration = 0;
    std::vector<Direction> mDirectionTable;
};


#endif //PATH_ALGORITHM_ABSTRACTSOLVER_HPP
