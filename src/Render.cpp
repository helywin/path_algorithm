/*********************************************************************************
 * FileName: Render.cpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/24
 * Description: 
 * Others:
*********************************************************************************/

#include "Render.hpp"
#include <QPainter>
#include "Scene.hpp"
#include "Common.hpp"

QColor colorTable(BlockType type)
{
    switch (type) {
        case bt_empty:
            return Qt::white;
        case bt_boundary:
        case bt_obstacle:
            return Qt::black;
        case bt_startPos:
        case bt_destPos:
            return Qt::blue;
        case bt_traveled:
            return Qt::gray;
    }
}

void Render::setScene(Scene *scene)
{
    mScene = scene;
}

void Render::paint(QPaintDevice *device)
{
    QPainter painter(device);
    auto size = mScene->size();
    for (int i = 0; i < size.height(); ++i) {
        for (int j = 0; j < size.width(); ++j) {
            QRect r(j * blockWidth(), (size.height() - 1) * blockWidth() - i * blockWidth(),
                    blockWidth(), blockWidth());
            painter.setPen(QPen(Qt::black, 1));
            auto data = mScene->getData(i, j);
            painter.setBrush(colorTable(data.first));
            painter.drawRect(r);
        }
    }
    if (mScene->path().size() < 2) {
        return;
    }
    painter.setPen(QPen(Qt::red, 2));
    for (int i = 0; i < mScene->path().size() - 1; ++i) {
        auto &p1 = mScene->path()[i];
        auto &p2 = mScene->path()[i + 1];
        QPoint qp1 = {
                p1.second * blockWidth() + blockWidth() / 2,
                size.height() * blockWidth() - p1.first * blockWidth() - blockWidth() / 2
        };
        QPoint qp2 = {
                p2.second * blockWidth() + blockWidth() / 2,
                size.height() * blockWidth() - p2.first * blockWidth() - blockWidth() / 2
        };
        painter.drawLine(qp1, qp2);
    }
}

int Render::blockWidth() const
{
    return 10;
}
