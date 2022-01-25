/*********************************************************************************
 * FileName: Window.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/24
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_WINDOW_HPP
#define PATH_ALGORITHM_WINDOW_HPP

#include <QWidget>

class WindowPrivate;

class Window : public QWidget
{
Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window() override;
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DECLARE_PRIVATE(Window)
    Q_DISABLE_COPY(Window)
    QScopedPointer<WindowPrivate> d_ptr;
};



#endif //PATH_ALGORITHM_WINDOW_HPP
