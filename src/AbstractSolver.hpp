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


class AbstractSolver
{
public:
    virtual void tick();
    virtual void run();
};


#endif //PATH_ALGORITHM_ABSTRACTSOLVER_HPP