#include "counter.h"


Counter::Counter():QObject(), m_value(0){}

void Counter::slotCounter(){
    emit CounterChanged(++m_value);
    if(m_value == 5)
        emit goodbye();
}
