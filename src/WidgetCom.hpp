//
// Created by jiang on 2021/3/10.
//

#ifndef GARBAGE_UI_WIDGETCOM_HPP
#define GARBAGE_UI_WIDGETCOM_HPP

#include <utility>
#include <cstddef>
#include <QString>

class QWidget;

// 几个偷懒的公用函数, 用来初始化控件

template<typename W, typename WP>
inline void initWidget(W *&w, WP *wp)
{
    w = new W(wp);
}

template<typename WPP, size_t N, typename WP>
inline void initWidgets(WPP (&w)[N], WP *wp)
{
    using W = typename std::remove_pointer<WPP>::type;
    for (int i = 0; i < N; ++i) {
        w[i] = new W(wp);
    }
}

void drawPrimitive(QWidget *w);

void setWidgetStyleSheet(QWidget *w, const QString &fileName);

void offButtonFocuses(QWidget *w);


#endif //GARBAGE_UI_WIDGETCOM_HPP
