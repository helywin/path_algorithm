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

class Scene;

class DFSSolver : AbstractSolver
{
public:
    void setScene(Scene *scene);
    void setStart(int row, int col);
    void setDest(int row, int col);
    void reset();

protected:
    void tick() override;
    void run() override;

private:
    Scene *mScene = nullptr;
    std::pair<int, int> mStartPos;
    std::pair<int, int> mDestPos;
    bool mFinish = false;
};


#endif //PATH_ALGORITHM_DFSSOLVER_HPP
