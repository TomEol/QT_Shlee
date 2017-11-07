#include "counter.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel lbl("0");
    QPushButton pb("ADD");
    Counter counter;
    QSignalMapper

    lbl.show();
    pb.show();

    QObject::connect(&pb,SIGNAL(clicked()),&counter,SLOT(slotCounter()));
    QObject::connect(&counter,SIGNAL(CounterChanged(int)),&lbl,SLOT(setNum(int)));
    QObject::connect(&counter,SIGNAL(goodbye()),&app,SLOT(quit()));

    return app.exec();
}
