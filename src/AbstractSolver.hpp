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

using Callback = std::function<void()>;
class Scene;

class AbstractSolver
{
public:
    virtual ~AbstractSolver() = default;
    virtual void tick() = 0;
    virtual void run(int interval) = 0;
    virtual void setCallback(Callback callback) = 0;
    virtual void setScene(Scene *scene) = 0;
    virtual void setStart(int row, int col) = 0;
    virtual void setDest(int row, int col) = 0;
    virtual void reset() = 0;
};


#endif //PATH_ALGORITHM_ABSTRACTSOLVER_HPP
