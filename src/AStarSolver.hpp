/*********************************************************************************
 * FileName: AStarSolver.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_ASTARSOLVER_HPP
#define PATH_ALGORITHM_ASTARSOLVER_HPP

#include "AbstractSolver.hpp"

class AStarSolver : public AbstractSolver
{
public:
    ~AStarSolver() override = default;
    void tick() override;
    void run(int interval) override;
    void setCallback(Callback callback) override;
    void setScene(Scene *scene) override;
    void setStart(int row, int col) override;
    void setDest(int row, int col) override;
    void reset() override;
};


#endif //PATH_ALGORITHM_ASTARSOLVER_HPP
