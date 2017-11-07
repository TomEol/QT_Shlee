#include "my_mouse.h"

my_Mouse::my_Mouse(QWidget *parent):QLabel(parent){
    setAlignment(Qt::AlignCenter);
    setText("Mouse interactions\n(Press a mouse button)");
}

void my_Mouse::mousePressEvent(QMouseEvent *someEvent){
    dumpEvent(someEvent,"Mouse pressed");
}

void my_Mouse::mouseReleaseEvent(QMouseEvent *someEvent){
    dumpEvent(someEvent,"Mouse Released");
}

void my_Mouse::mouseMoveEvent(QMouseEvent *someEvent){
    dumpEvent(someEvent,"Mouse is moving");
}

void my_Mouse::dumpEvent(QMouseEvent *someEvent,const QString &msg ){
    setText(msg + "\n buttons()=" + buttonsInfo(someEvent)
                + "\n x()=" + QString::number(someEvent->x())
                + "\n y()=" + QString::number(someEvent->y())
                + "\n globalX()=" + QString::number(someEvent->globalX())
                + "\n globalY()=" + QString::number(someEvent->globalY())
                + "\n modifiers()=" + modifiersInfo(someEvent)
            );
}

QString my_Mouse::modifiersInfo(QMouseEvent *someEvent){
    QString str_modifiers;
    if(someEvent->modifiers() & Qt::ShiftModifier)
        str_modifiers += "Shift";
    if(someEvent->modifiers() & Qt::ControlModifier)
        str_modifiers += "Control";
    if(someEvent->modifiers() & Qt::AltModifier)
        str_modifiers += "Alt";
    return str_modifiers;
}

QString my_Mouse::buttonsInfo(QMouseEvent *someEvent){
    QString str_buttons;
    if(someEvent->buttons() & Qt::LeftButton)
        str_buttons += "left";
    if(someEvent->buttons() & Qt::RightButton)
        str_buttons += "right";
    if(someEvent->buttons() & Qt::MidButton)
        str_buttons += "middle";
    return str_buttons;
}

void my_Mouse::wheelEvent(QWheelEvent *someEvent){
    int numDegrees = someEvent->delta();

    if(numDegrees > 0){
        setText("from us");
    }
    else
        setText("to us");
}

void my_Mouse::keyPressEvent(QKeyEvent *someEvent){
    switch (someEvent->key()) {
    case Qt::Key_A :
        if(someEvent->modifiers() & Qt::AltModifier){
            setText("You press A and Alt");
        }break;
    case Qt::Key_R :
        if(someEvent->modifiers() & Qt::ControlModifier){
            setText("You press R and Ctrl");
        }break;
    case Qt::Key_T :
        if(someEvent->modifiers() & Qt::ShiftModifier){
            setText("You press T and Shift");
        }break;
    }
}



