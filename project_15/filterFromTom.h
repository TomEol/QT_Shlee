#ifndef FILTERFROMTOM_H
#define FILTERFROMTOM_H

#include <QObject>
#include <QtWidgets>

class filterFromTom : public QObject{
public:
    filterFromTom(QObject *parent = nullptr);
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
public:

};

#endif // FILTERFROMTOM_H
