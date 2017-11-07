#ifndef MY_MOUSE_H
#define MY_MOUSE_H

#include <QtWidgets>

class my_Mouse : public QLabel{
public:
    my_Mouse(QWidget *parent = nullptr);
protected:
    virtual void mousePressEvent  (QMouseEvent *someEvent);
    virtual void mouseReleaseEvent(QMouseEvent *someEvent);
    virtual void mouseMoveEvent   (QMouseEvent *someEvent);
    virtual void wheelEvent       (QWheelEvent *someEvent);
    virtual void keyPressEvent    (QKeyEvent   *someEvent);

    void dumpEvent       (QMouseEvent *someEvent,const QString &msg );
    QString modifiersInfo(QMouseEvent *someEvent);
    QString buttonsInfo  (QMouseEvent *someEvent);
};

#endif // MY_MOUSE_H
