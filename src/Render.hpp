/*********************************************************************************
 * FileName: Render.hpp
 * Author: helywin(jiang770882022@hotmail.com)
 * Version: 0.1
 * Date: 2022/1/24
 * Description: 
 * Others:
*********************************************************************************/

#ifndef PATH_ALGORITHM_RENDER_HPP
#define PATH_ALGORITHM_RENDER_HPP

#include <QPaintDevice>
#include <QObject>

class Scene;

class Render : public QObject
{
Q_OBJECT
public:
    void setScene(Scene *scene);
    void paint(QPaintDevice *device);
    int blockWidth() const;
private:
    Scene *mScene = nullptr;
};


#endif //PATH_ALGORITHM_RENDER_HPP
