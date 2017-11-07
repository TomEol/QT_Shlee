#ifndef SIMPLE_DELEGATE_H
#define SIMPLE_DELEGATE_H

#include <QtWidgets>

class SimpleDelegate : public QStyledItemDelegate{
public:
    SimpleDelegate(QObject *parent = nullptr):QStyledItemDelegate(parent){}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        if(option.state & QStyle::State_MouseOver){
            QRect rect = option.rect;
                       QLinearGradient gradient(0,0,rect.width(),rect.height());

                       gradient.setColorAt(0,Qt::white);
                       gradient.setColorAt(0.5,Qt::blue);

                       gradient.setColorAt(0.8,Qt::green);
                       gradient.setColorAt(1,Qt::yellow);


                       painter->setBrush(gradient);
                       painter->drawRect(rect);

        }
        QStyledItemDelegate::paint(painter,option,index);
    }
};
#endif // SIMPLE_DELEGATE_H
