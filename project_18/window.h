#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class Window : public QWidget
{
    Q_OBJECT
public:
    Window();

signals:

public slots:
private slots:
    void shapeChanged();
    void penChanged();
    void brushChanged();
};

#endif // WINDOW_H
