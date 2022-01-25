//
// Created by jiang on 2021/3/10.
//

#include "WidgetCom.hpp"
#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QFile>
#include <QAbstractButton>

void drawPrimitive(QWidget *w)
{
    QStyleOption opt;
    opt.init(w);
    QPainter p(w);
    w->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, w);
}

void setWidgetStyleSheet(QWidget *w, const QString &fileName)
{
    QFile qssFile(fileName);
    qssFile.open(QIODevice::ReadOnly | QIODevice::Text);
    w->setStyleSheet(qssFile.readAll());
}

void offButtonFocuses(QWidget *w)
{
    for (const auto child: w->children()) {
        if (child->inherits("QAbstractButton")) {
            dynamic_cast<QAbstractButton *>(child)->setFocusPolicy(Qt::NoFocus);
        }
    }
}
