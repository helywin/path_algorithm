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
    Dijkstra();
    ~Dijkstra() override = default;
    void run(int interval) override;
protected:
    void dijkstra();
};


#endif //PATH_ALGORITHM_DIJKSTRA_HPP
