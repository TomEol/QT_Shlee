#include "filterFromTom.h"

filterFromTom::filterFromTom(QObject *parent):QObject(parent){}

bool filterFromTom::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        if(static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton){
            QString strClassName = watched->metaObject()->className();
            QMessageBox::information(0,"Class Name",strClassName);
            return true;
        }
    }
    if(event->type() == QEvent::KeyPress){
        if(static_cast<QKeyEvent*>(event)->key() == Qt::Key_A){
            QString strClassName = watched->metaObject()->className();
            QMessageBox::information(0,"Class Name",strClassName);
            return true;
        }
    }
    return false;
}
