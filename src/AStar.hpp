/*********************************************************************************
 * FileName: AStar.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_ASTAR_HPP
#define PATH_ALGORITHM_ASTAR_HPP

#include "AbstractSolver.hpp"
#include <valarray>

class AStar : public AbstractSolver
{
public:

public:
    AStar();
    ~AStar() override = default;
    void run(int interval) override;
protected:
    void astar();
};


#endif //PATH_ALGORITHM_ASTAR_HPP
