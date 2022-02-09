/*********************************************************************************
 * FileName: Solver.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/24
 * Description: 
 * Others:
*********************************************************************************/

#include "AbstractSolver.hpp"

AbstractSolver::AbstractSolver()
{
    mDirectionTable = {
            d_ne,
            d_se,
            d_nw,
            d_sw,
            d_e,
            d_n,
            d_s,
            d_w,
    };
}

void AbstractSolver::setStart(int row, int col)
{
    mScene->block(row, col).blockSymbol = bs_startPos;
    mStartPos = mScene->vertex(row, col);
    mStartPos.block().distance = 0;
}

void AbstractSolver::setDest(int row, int col)
{
    mScene->block(row, col).blockSymbol = bs_destPos;
    mDestPos = mScene->vertex(row, col);
}

void AbstractSolver::setCallback(Callback callback)
{
    mCallback = callback;
}

void AbstractSolver::setScene(Scene *scene)
{
    mScene = scene;
}
