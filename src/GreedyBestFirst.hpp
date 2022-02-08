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

class Scene;

class GreedyBestFirst : public AbstractSolver
{
public:
    GreedyBestFirst();
    ~GreedyBestFirst() override = default;
    void run(int interval) override;
protected:
    void gbfs();
};


#endif //PATH_ALGORITHM_GREEDYBESTFIRST_HPP
