#ifndef KEYFILTER_H
#define KEYFILTER_H

#include <QWidget>
#include <QtWidgets>

class keyFilter : public QObject
{
    Q_OBJECT
public:
    explicit keyFilter(QObject *parent = nullptr):QObject(parent){}
protected:
    bool eventFilter(QObject *watched, QEvent *event){
        if(event->type() == QEvent::KeyPress){
            if(((QKeyEvent*)event)->key() == Qt::Key_Z){
                QKeyEvent keyEvent(QEvent::KeyPress,Qt::Key_A,Qt::NoModifier,"A");
                QApplication::sendEvent(watched,&keyEvent);
                return true;
            }
        }return false;
    }
};

#endif // KEYFILTER_H
