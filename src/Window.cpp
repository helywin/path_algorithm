/*********************************************************************************
 * FileName: Window.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/24
 * Description: 
 * Others:
*********************************************************************************/

#include "Window.hpp"
#include "Scene.hpp"
#include "Render.hpp"
#include "DFSSolver.hpp"

class WindowPrivate
{
public:
    Q_DECLARE_PUBLIC(Window)
    Window *q_ptr;
    Scene mScene;
    Render mRender;
    DFSSolver mSolver;

    explicit WindowPrivate(Window *p);
    void init();
};

WindowPrivate::WindowPrivate(Window *p) :
        mScene(50, 30)
{
    mRender.setScene(&mScene);
}

void WindowPrivate::init()
{
    // 设置边界
    for (int j = 0; j < mScene.size().width(); ++j) {
        mScene.setData(0, j, BlockType::bt_boundary, 0);
    }
    for (int j = 0; j < mScene.size().width(); ++j) {
        mScene.setData(mScene.size().height() - 1, j, BlockType::bt_boundary, 0);
    }

    for (int i = 0; i < mScene.size().height(); ++i) {
        mScene.setData(i, 0, BlockType::bt_boundary, 0);
    }
    for (int i = 0; i < mScene.size().height(); ++i) {
        mScene.setData(i, mScene.size().width() - 1, BlockType::bt_boundary, 0);
    }
    // 设置障碍
    for (int j = 10; j < 20; ++j) {
        mScene.setData(15, j, BlockType::bt_obstacle, 0);
    }
    for (int i = 1; i < 16; ++i) {
        mScene.setData(i, 19, BlockType::bt_obstacle, 0);
    }
    for (int i = 15; i < 29; ++i) {
        mScene.setData(i, 30, BlockType::bt_obstacle, 0);
    }
    for (int i = 1; i < 16; ++i) {
        mScene.setData(i, 40, BlockType::bt_obstacle, 0);
    }
    // 设置起始终止点
    mSolver.setScene(&mScene);
    mSolver.setStart(5, 5);
    mSolver.setDest(24, 44);
}

Window::Window(QWidget *parent) :
        QWidget(parent),
        d_ptr(new WindowPrivate(this))
{
    Q_D(Window);
    d->init();
    resize(d->mScene.size() * d->mRender.blockWidth());
}

QSize Window::sizeHint() const
{
    Q_D(const Window);
    return d->mScene.size() * d->mRender.blockWidth();
}

Window::~Window()
{

}

void Window::paintEvent(QPaintEvent *event)
{
    Q_D(Window);
    d->mRender.paint(this);
}
