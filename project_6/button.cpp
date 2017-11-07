#include "button.h"

Button::Button(const QString &name, QWidget *parent):QToolButton(parent){
    // if you dont write this , each button will have different size 
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    setText(name);
}
QSize Button::sizeHint()const{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(),size.height());
    return size;
}
