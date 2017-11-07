#include <QCoreApplication>
#include "lab_one.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Lab_one lbOne;
    lbOne.setV();
    lbOne.getV();
    lbOne.main_process();
    return a.exec();
}

