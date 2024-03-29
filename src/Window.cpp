/*********************************************************************************
 * FileName: Window.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/24
 * Description: 
 * Others:
*********************************************************************************/

#include "Window.hpp"
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <memory>
#include "Scene.hpp"
#include "Render.hpp"
#include "GreedyBestFirst.hpp"
#include "Dijkstra.hpp"
#include "AStar.hpp"
#include "WidgetCom.hpp"

class WindowPrivate
{
public:
    Q_DECLARE_PUBLIC(Window)
    Window *q_ptr;
    QHBoxLayout *mLayout;
    QVBoxLayout *mButtonLayout;
    QPushButton *mDFS;
    QWidget *mView;
    Scene mScene;
    Render mRender;
    AbstractSolver *mSolver;
    QTimer mTimer;

    explicit WindowPrivate(Window *p);
    void init();
};

WindowPrivate::WindowPrivate(Window *p) :
        q_ptr(p),
        mScene(50, 30)
{
    Q_Q(Window);
//    mSolver = new AStar();
    mSolver = new Dijkstra();
//    mSolver = new GreedyBestFirst();
    mRender.setScene(&mScene);
//    initWidget(mLayout, q);
//    initWidget(mView, q);
//    initWidget(mDFS, q);
//    mButtonLayout = new QVBoxLayout;
//    mLayout->addLayout(mButtonLayout);
//    mLayout->addWidget(mView);
//    mButtonLayout->addWidget(mDFS);
//    mButtonLayout->addStretch(1);
}

void WindowPrivate::init()
{
    // 设置边界
    for (int j = 0; j < mScene.size().width(); ++j) {
        mScene.block(0, j).blockType = BlockType::bt_boundary;
    }
    for (int j = 0; j < mScene.size().width(); ++j) {
        mScene.block(mScene.size().height() - 1, j).blockType = BlockType::bt_boundary;
    }
    for (int i = 0; i < mScene.size().height(); ++i) {
        mScene.block(i, 0).blockType = BlockType::bt_boundary;
    }
    for (int i = 0; i < mScene.size().height(); ++i) {
        mScene.block(i, mScene.size().width() - 1).blockType = BlockType::bt_boundary;
    }
    // 设置障碍
    for (int j = 10; j < 20; ++j) {
        mScene.block(15, j).blockType = BlockType::bt_obstacle;
    }
    for (int i = 1; i < 16; ++i) {
        mScene.block(i, 19).blockType = BlockType::bt_obstacle;
    }
    for (int i = 15; i < 29; ++i) {
        mScene.block(i, 30).blockType = BlockType::bt_obstacle;
    }
    for (int i = 1; i < 16; ++i) {
        mScene.block(i, 40).blockType = BlockType::bt_obstacle;
    }
    // 设置起始终止点
    mSolver->setScene(&mScene);
    mSolver->setStart(5, 5);
    mSolver->setDest(24, 44);
    mSolver->setCallback([this] {
        q_ptr->update();
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    });
    mTimer.setInterval(1000);
    mTimer.start();
}

Window::Window(QWidget *parent) :
        QWidget(parent),
        d_ptr(new WindowPrivate(this))
{
    Q_D(Window);
    d->init();
    resize(d->mScene.size() * d->mRender.blockWidth());
    QTimer::singleShot(4000, [this] {
        d_ptr->mSolver->run(10);
    });
}

QSize Window::sizeHint() const
{
    Q_D(const Window);
    return d->mScene.size() * d->mRender.blockWidth();
}

Window::~Window()
{
    Q_D(Window);
    delete d->mSolver;
}

void Window::paintEvent(QPaintEvent *event)
{
    Q_D(Window);
    d->mRender.paint(this);
}
