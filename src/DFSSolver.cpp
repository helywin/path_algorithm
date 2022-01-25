/*********************************************************************************
 * FileName: DFSSolver.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/25
 * Description: 
 * Others:
*********************************************************************************/

#include "DFSSolver.hpp"
#include "Scene.hpp"

void DFSSolver::setScene(Scene *scene)
{
    mScene = scene;
}

void DFSSolver::tick()
{
    AbstractSolver::tick();
}

void DFSSolver::run()
{
    AbstractSolver::run();
}

void DFSSolver::reset()
{
    mFinish = true;
}

void DFSSolver::setStart(int row, int col)
{
    mScene->setData(row, col, bt_startPos, 0);
}

void DFSSolver::setDest(int row, int col)
{
    mScene->setData(row, col, bt_destPos, 0);
}

