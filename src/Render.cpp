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
}

int Render::blockWidth() const
{
    return 10;
}
