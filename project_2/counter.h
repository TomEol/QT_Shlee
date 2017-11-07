#ifndef COUNTER_H
#define COUNTER_H
#include <QObject>

class Counter : public QObject{
    Q_OBJECT
private:
    int m_value;
public:
    Counter();
public slots:
    void slotCounter();
signals:
    void goodbye();
    void CounterChanged(int);

};



#endif // COUNTER_H
