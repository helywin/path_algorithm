#include <iostream>
#include <QApplication>
#include "Window.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window win;
    win.show();
    return QApplication::exec();
}
