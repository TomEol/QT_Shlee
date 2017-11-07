#include <QtWidgets>
#include "my_Mouse.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    my_Mouse mouse_wgt;

    mouse_wgt.resize(400,400);
    mouse_wgt.show();


    return a.exec();
}
